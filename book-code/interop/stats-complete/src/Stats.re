/*
This is the format for an error object that Papa Parse
returns to you along with the results of the parse.

{
  type: "",     // A generalization of the error
  code: "",     // Standardized error code
  message: "",  // Human-readable details
  row: 0,       // Row index of parsed data where error is
}
*/
module Error = {
   [@bs.deriving abstract] type t = {
    [@bs.as "type"]  type_: string,
    code: string,
    message: string,
    row: int
  }
};

/*
TODO: This is the format of the metadata object
that Papa Parse returns along with the data
from your CSV file.

{
  delimiter: // Delimiter used
  linebreak: // Line break sequence used
  aborted:   // Whether process was aborted
  fields:    // Array of field names
  truncated: // Whether preview consumed all input
}
*/
module Meta = {
  [@bs.deriving abstract] type t = {
    delimiter: string,
    linebreak: string,
    aborted: bool,
    fields: array(string),
    truncated: bool
  }
};

/*
TODO:  This is an object that Papa Parse returns
  as a result of parsing a CSV file.
  
  If you do not have a header, row, data is
  an array of array of string (one sub-array per CSV line)
  
  If you do have a header row, data is an array of
  objects with field names as the keys.

{
  data:   // array of parsed data
  errors: // array of errors
  meta:   // object with extra info
}
*/
module Results = {
 [@bs.deriving abstract] type t = {
      data: array(array(string)),
      error: array(Error.t),
      meta: Meta.t
  };
};

/*
 TODO: Create a binding named parseString that calls the parse()
 function in PapaParse (module "papaparse").
 
 Your parseString() function takes a string of file contents
 as its parameter. In JavaScript, you might do this:
 
    var str = "1,2,3\n4,5,6\n7,8,9\n";
    var result = Papa.parse(str);
    
 In annotated ReasonML, that would become:

    let str: string = "1,2,3\n4,5,6\n7,8,9\n";
    let result: Results.t = parseString(str);

*/
[@bs.val] [@bs.module "papaparse"] external parseString :
  (string) => Results.t = "parse";

type order = {
  quantity: int,
  size: Shirt.Size.t,
  sleeve: Shirt.Sleeve.t,
  color: Shirt.Color.t,
  pattern: Shirt.Pattern.t,
  cuff: Shirt.Cuff.t,
  collar: Shirt.Collar.t,
};

let optFloat = (str: string): option(float) =>
  switch (float_of_string(str)) {
  | fNum => Some(fNum)
  | exception (Failure("float_of_string")) => None
  };

let optInt = (str: string): option(int) =>
  switch (int_of_string(str)) {
  | anInt => Some(anInt)
  | exception (Failure("int_of_string")) => None
  };

let map2 = (optX, optY, f) =>
  switch (optX, optY) {
  | (Some(x), Some(y)) => Some(f(x, y))
  | (_, _) => None
  };

/*
 *  In this function, the items array consists of the data on a line
 *  from the CSV file. The reducer will create an order record and
 *  add it to the accumulator
 */ 
let lineReducer = (acc: list(order), items: array(string)): list(order) => {
  if (Belt.Array.length(items) != 7) {
    acc;
  } else {
    let initial =
      Some({
        quantity: 0,
        size: Small,
        sleeve: Short,
        color: White,
        pattern: Solid,
        cuff: Button,
        collar: Straight,
      });

    let orderRecord =
      map2(initial, optInt(items[0]),
        (result, n) => {...result, quantity: n})
      -> map2(Shirt.Size.fromString(items[1]),
        (result, sz) => {...result, size: sz})
      -> map2(Shirt.Color.fromString(items[2]),
          (result, c) => {...result, color: c})
      -> map2(Shirt.Pattern.fromString(items[3]),
          (result, pat) => {...result, pattern: pat})
      -> map2(Shirt.Collar.fromString(items[4]),
          (result, coll) => {...result, collar: coll})
      -> map2(Shirt.Sleeve.fromString(items[5]),
          (result, sleeve) => {...result, sleeve})
      -> map2(Shirt.Cuff.fromString(items[6]),
          (result, cuff) => {...result, cuff});

    switch (orderRecord) {
    | Some(result) => [result, ...acc]
    | None => acc
    };
  };
};

let printMap = (title: string, distribution: Belt.Map.t('k, 'v, 'id),
  toString: ('a) => string) => {
    Js.log2(title, "Quantity");
    Belt.Map.forEach(distribution, (key, value) =>
      Js.log2(toString(key), value));
    Js.log("");
  };

let printStatistics = (orders: list(order)): unit => {

  let makeDistro = (comparator, getter) =>
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=comparator),
      (acc, item) => {
        let n = Belt.Map.getWithDefault(acc, getter(item), 0);
        Belt.Map.set(acc, getter(item), n + item.quantity);
      },
    );

  let colorDistribution = makeDistro((module Shirt.ColorComparator),
    (ord) => ord.color);
  printMap("Color", colorDistribution, Shirt.Color.toString);

  let sizeDistribution =  makeDistro((module Shirt.SizeComparator),
    (ord) => ord.size);
  printMap("Size", sizeDistribution, Shirt.Size.toString);
    
  let patternDistribution = makeDistro((module Shirt.PatternComparator),
    (ord) => ord.pattern);
  printMap("Pattern", patternDistribution, Shirt.Pattern.toString);
  
  let collarDistribution = makeDistro((module Shirt.CollarComparator),
    (ord) => ord.collar);
  printMap("Collar", collarDistribution, Shirt.Collar.toString);
  
  let sleeveDistribution = makeDistro((module Shirt.SleeveComparator),
    (ord) => ord.sleeve);
  printMap("Sleeve", sleeveDistribution, Shirt.Sleeve.toString);
    
  let cuffDistribution = makeDistro((module Shirt.CuffComparator),
    (ord) => ord.cuff);
  printMap("Cuff", cuffDistribution, Shirt.Cuff.toString);
};

let processFile = (inFileName: string): unit => {
  let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
  /*
   * TODO: call the parseString function on the fileContents
   * to have PapaParse parse the CSV string. This will produce
   * a Results.t object. Get its data field, which is an
   * array of arrays, one sub-array per line in the CSV.
   *
   * The first sub-array is the header line, which we don't want.
   * Set a variable named lines to be elements 1..n of
   * the data field (hint: use Belt.Array.slice)
   * 
   */
  let parseData = Results.dataGet(parseString(fileContents));
  let lines = Belt.Array.slice(parseData, ~offset=1,
    ~len=Belt.Array.length(parseData) - 1)

  let orders = Belt.Array.reduce(lines, [], lineReducer);

  printStatistics(orders);
};

let nodeArg = Belt.Array.get(Node.Process.argv, 0);
let progArg = Belt.Array.get(Node.Process.argv, 1);
let fileArg = Belt.Array.get(Node.Process.argv, 2);

switch (nodeArg, progArg, fileArg) {
| (_, _, Some(inFileName)) => processFile(inFileName)
| (Some(node), Some(prog), _) =>
  Js.log("Usage: " ++ node ++ " " ++ prog ++ " inputfile.csv")
| (_, _, _) =>
  Js.log("How did you get here without NodeJS or a program to run?")
};
