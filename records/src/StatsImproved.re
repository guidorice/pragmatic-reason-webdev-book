module Size = {
  type t =
    | XSmall(int)
    | Small
    | Medium
    | Large
    | XLarge(int);

  let toString = (size: t): string =>
    switch (size) {
    | XSmall(n) => String.make(n, 'X') ++ "S"
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => String.make(n, 'X') ++ "L"
    };

  let fromString = (str: string): option(t) =>
    switch (Js.String.toUpperCase(str)) {
    | "S" => Some(Small)
    | "M" => Some(Medium)
    | "L" => Some(Large)
    | s when Js.Re.test(s, [%re "/^X+S$/"]) =>
      Some(XSmall(String.length(s) - 1))
    | s when Js.Re.test(s, [%re "/^X+L$/"]) =>
      Some(XLarge(String.length(s) - 1))
    | _ => None
    };

  let compareSize = (a: t, b: t): int =>
    switch (a, b) {
    | (XSmall(i), XSmall(j)) => compare(i, j)
    | (XSmall(_), _) => (-1)
    | (XLarge(i), XLarge(j)) => compare(i, j)
    | (XLarge(_), _) => 1
    | (Small, Small)
    | (Medium, Medium)
    | (Large, Large) => 0
    | (Small, XSmall(_)) => 1
    | (Small, _) => (-1)
    | (Medium, XSmall(_))
    | (Medium, Small) => 1
    | (Medium, _) => (-1)
    | (Large, XSmall(_))
    | (Large, Small)
    | (Large, Medium) => 1
    | (Large, _) => (-1)
    };
};

module SizeComparator =
  Belt.Id.MakeComparable({
    type t = Size.t;
    let cmp = Size.compareSize;
  });

module Sleeve = {
  type t =
    | Short
    | Long
    | XLong; /* for tall people */

  let toString = (sleeve: t): string =>
    switch (sleeve) {
    | Short => "short sleeve"
    | Long => "long sleeve"
    | XLong => "extra-long sleeve"
    };

  let fromString = (str: string): option(t) =>
    switch (Js.String.toLowerCase(str)) {
    | "short" => Some(Short)
    | "long" => Some(Long)
    | "xlong" => Some(XLong)
    | _ => None
    };
};

module SleeveComparator =
  Belt.Id.MakeComparable({
    type t = Sleeve.t;
    let cmp = compare;
  });

module Color = {
  type t =
    | White
    | Blue
    | Red
    | Green
    | Brown;

  let toString = (color: t): string =>
    switch (color) {
    | White => "white"
    | Blue => "blue"
    | Red => "red"
    | Green => "green"
    | Brown => "brown"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "white" => Some(White)
    | "blue" => Some(Blue)
    | "red" => Some(Red)
    | "green" => Some(Green)
    | "brown" => Some(Brown)
    | _ => None
    };
};

module ColorComparator =
  Belt.Id.MakeComparable({
    type t = Color.t;
    let cmp = compare;
  });

module Pattern = {
  type t =
    | Solid
    | Pinstripe
    | Check;

  let toString = (pattern: t): string =>
    switch (pattern) {
    | Solid => "solid"
    | Pinstripe => "pinstripe"
    | Check => "check"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "solid" => Some(Solid)
    | "pinstripe" => Some(Pinstripe)
    | "check"
    | "checked" => Some(Check)
    | _ => None
    };
};

module PatternComparator =
  Belt.Id.MakeComparable({
    type t = Pattern.t;
    let cmp = compare;
  });

module Cuff = {
  type t =
    | Button
    | French
    | NoCuff;

  let toString = (cuff: t): string =>
    switch (cuff) {
    | Button => "button"
    | French => "french"
    | NoCuff => "none"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "button" => Some(Button)
    | "french" => Some(French)
    | ""
    | "none"
    | "nocuff" => Some(NoCuff)
    | _ => None
    };
};

module CuffComparator =
  Belt.Id.MakeComparable({
    type t = Cuff.t;
    let cmp = compare;
  });

module Collar = {
  type t =
    | Button
    | Straight
    | Spread;

  let toString = (collar: t): string =>
    switch (collar) {
    | Button => "button"
    | Straight => "straight"
    | Spread => "spread"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "button" => Some(Button)
    | "straight" => Some(Straight)
    | "spread" => Some(Spread)
    | _ => None
    };
};

module CollarComparator =
  Belt.Id.MakeComparable({
    type t = Collar.t;
    let cmp = compare;
  });

type order = {
  quantity: int,
  size: Size.t,
  sleeve: Sleeve.t,
  color: Color.t,
  pattern: Pattern.t,
  cuff: Cuff.t,
  collar: Collar.t,
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

let lineReducer = (acc: list(order), line: string): list(order) => {
  let items = Js.String.split(",", line);
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
      -> map2(Size.fromString(items[1]),
        (result, sz) => {...result, size: sz})
      -> map2(Color.fromString(items[2]),
          (result, c) => {...result, color: c})
      -> map2(Pattern.fromString(items[3]),
          (result, pat) => {...result, pattern: pat})
      -> map2(Collar.fromString(items[4]),
          (result, coll) => {...result, collar: coll})
      -> map2(Sleeve.fromString(items[5]),
          (result, sleeve) => {...result, sleeve})
      -> map2(Cuff.fromString(items[6]),
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

  let colorDistribution = makeDistro((module ColorComparator),
    (ord) => ord.color);
  printMap("Color", colorDistribution, Color.toString);

  let sizeDistribution =  makeDistro((module SizeComparator),
    (ord) => ord.size);
  printMap("Size", sizeDistribution, Size.toString);
    
  let patternDistribution = makeDistro((module PatternComparator),
    (ord) => ord.pattern);
  printMap("Pattern", patternDistribution, Pattern.toString);
  
  let collarDistribution = makeDistro((module CollarComparator),
    (ord) => ord.collar);
  printMap("Collar", collarDistribution, Collar.toString);
  
  let sleeveDistribution = makeDistro((module SleeveComparator),
    (ord) => ord.sleeve);
  printMap("Sleeve", sleeveDistribution, Sleeve.toString);
    
  let cuffDistribution = makeDistro((module CuffComparator),
    (ord) => ord.cuff);
  printMap("Cuff", cuffDistribution, Cuff.toString);
};

let processFile = (inFileName: string): unit => {
  let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
  let lines = Js.String.split("\n", fileContents) |> Js.Array.sliceFrom(1); /* get rid of header line */

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
