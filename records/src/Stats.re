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

  let compareSize = (a: t, b: t) : int => {
      switch (a, b) {
        /* xsmall(n) special cases */
        | (XSmall(s1), XSmall(s2)) when s1 == s2 => 0
        | (XSmall(s1), XSmall(s2)) => s1 < s2 ? -1 : 1
        | (XSmall(_), Small|Medium|Large|XLarge(_)) => -1
        | (Small|Medium|Large|XLarge(_), XSmall(_)) => 1
        /* xlarge(n) special cases */
        | (XLarge(s1), XLarge(s2)) when s1 == s2 => 0
        | (XLarge(s1), XLarge(s2)) => s1 < s2 ? -1 : 1
        | (XLarge(_), Small|Medium|Large) => 1
        | (Small|Medium|Large, XLarge(_)) => -1
        /* all other cases, use builtin compare */
        | (s1, s2) => compare(s1, s2)
      }
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

let myOrder = {
  quantity: 2,
  size: Medium,
  sleeve: Long,
  color: Blue,
  pattern: Solid,
  cuff: Button,
  collar: Button,
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

    let orderRecord = map2(initial, optInt(items[0]),
        (result, n) => {...result, quantity: n}) 
      -> map2(Size.fromString(items[1]),
        (result, sz) => {...result, size: sz}) 
      -> map2(Color.fromString(items[2]),
        (result, c) => {... result, color: c})
      -> map2(Pattern.fromString(items[3]),
        (result, pat) => {...result, pattern: pat})
      -> map2(Collar.fromString(items[4]),
        (result, coll) => {...result, collar: coll})
      -> map2(Sleeve.fromString(items[5]),
        (result, sleeve) => {...result, sleeve: sleeve})
      -> map2(Cuff.fromString(items[6]),
        (result, cuff) => {...result, cuff: cuff});

    switch (orderRecord) { 
      | Some(result) => [result, ...acc]
      | None => acc
    };
  };
};

type sizeMapType = Belt.Map.t(Size.t, int, SizeComparator.identity);
let sizeReducer = (accumulatedMap: sizeMapType, item: order): sizeMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.size, 0); 
  Belt.Map.set(accumulatedMap, item.size, n + item.quantity);
}

type sleeveMapType = Belt.Map.t(Sleeve.t, int, SleeveComparator.identity);
let sleeveReducer = (accumulatedMap: sleeveMapType, item: order): sleeveMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.sleeve, 0); 
  Belt.Map.set(accumulatedMap, item.sleeve, n + item.quantity);
}

type colorMapType = Belt.Map.t(Color.t, int, ColorComparator.identity);
let colorReducer = (accumulatedMap: colorMapType, item: order): colorMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.color, 0); 
  Belt.Map.set(accumulatedMap, item.color, n + item.quantity);
}

type collarMapType = Belt.Map.t(Collar.t, int, CollarComparator.identity);
let collarReducer = (accumulatedMap: collarMapType, item: order): collarMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.collar, 0); 
  Belt.Map.set(accumulatedMap, item.collar, n + item.quantity);
}

type patternMapType = Belt.Map.t(Pattern.t, int, PatternComparator.identity);
let patternReducer = (accumulatedMap: patternMapType, item: order): patternMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.pattern, 0); 
  Belt.Map.set(accumulatedMap, item.pattern, n + item.quantity);
}

type cuffMapType = Belt.Map.t(Cuff.t, int, CuffComparator.identity);
let cuffReducer = (accumulatedMap: cuffMapType, item: order): cuffMapType
 => {
  let n = Belt.Map.getWithDefault(accumulatedMap, item.cuff, 0); 
  Belt.Map.set(accumulatedMap, item.cuff, n + item.quantity);
}

let printStatistics = (orders: list(order)): unit => {
  let colorDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module ColorComparator)), 
      colorReducer);
  Js.log2("Color","Quantity");
  Belt.Map.forEach(colorDistribution,
    (key, value) => Js.log2(Color.toString(key), value) 
  );
  let sizeDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module SizeComparator)),
      sizeReducer
    );
  Js.log2("Size","Quantity");
  Belt.Map.forEach(sizeDistribution,
    (key, value) => Js.log2(Size.toString(key), value) 
  );

 let sleeveDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module SleeveComparator)),
      sleeveReducer
    );
  Js.log2("Sleeve","Quantity");
  Belt.Map.forEach(sleeveDistribution,
    (key, value) => Js.log2(Sleeve.toString(key), value) 
  );
  
 let collarDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module CollarComparator)),
      collarReducer
    );
  Js.log2("Collar","Quantity");
  Belt.Map.forEach(collarDistribution,
    (key, value) => Js.log2(Collar.toString(key), value) 
  );

  let cuffDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module CuffComparator)),
      cuffReducer
    );
  Js.log2("Cuff","Quantity");
  Belt.Map.forEach(cuffDistribution,
    (key, value) => Js.log2(Cuff.toString(key), value) 
  );

  let patternDistribution = 
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=(module PatternComparator)),
      patternReducer
    );
  Js.log2("Pattern","Quantity");
  Belt.Map.forEach(patternDistribution,
    (key, value) => Js.log2(Pattern.toString(key), value) 
  );


};

let processFile = (inFileName: string): unit => {
  let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
  let lines = Js.String.split("\n", fileContents) ->
    Belt.Array.sliceToEnd(1); /* get rid of header line */

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
