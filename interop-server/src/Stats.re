module E = Json.Encode;

module Error = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "type"]
    type_: string,
    code: string,
    message: string,
    row: int,
  };
};

module Meta = {
  [@bs.deriving abstract]
  type t = {
    delimiter: string,
    linebreak: string,
    aborted: bool,
    fields: array(string),
    truncated: bool,
  };
};

module Results = {
  [@bs.deriving abstract]
  type t = {
    data: array(array(string)),
    error: array(Error.t),
    meta: Meta.t,
  };
};

[@bs.val] [@bs.module "papaparse"]
external parseString: string => Results.t = "parse";

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

let lineReducer = (acc: list(order), items: array(string)): list(order) =>
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
      map2(initial, optInt(items[0]), (result, n) =>
        {...result, quantity: n}
      )
      ->map2(Shirt.Size.fromString(items[1]), (result, sz) =>
          {...result, size: sz}
        )
      ->map2(Shirt.Color.fromString(items[2]), (result, c) =>
          {...result, color: c}
        )
      ->map2(Shirt.Pattern.fromString(items[3]), (result, pat) =>
          {...result, pattern: pat}
        )
      ->map2(Shirt.Collar.fromString(items[4]), (result, coll) =>
          {...result, collar: coll}
        )
      ->map2(Shirt.Sleeve.fromString(items[5]), (result, sleeve) =>
          {...result, sleeve}
        )
      ->map2(Shirt.Cuff.fromString(items[6]), (result, cuff) =>
          {...result, cuff}
        );

    switch (orderRecord) {
    | Some(result) => [result, ...acc]
    | None => acc
    };
  };

let makeObject =
    (
      title: string,
      distribution: Belt.Map.t('k, 'v, 'id),
      toString: 'a => string,
    )
    : Js.Json.t => {
  /* Create an array of pairs (key, value) from the distribution map */
  let pairs =
    Belt.Map.reduce(distribution, [||], (acc, key, value) =>
      Belt.Array.concat(acc, [|(toString(key), value)|])
    );

  /* Separate into two arrays */
  let (names, totals) = Belt.Array.unzip(pairs);

  /* And return a JSON object */
  E.object_([
    ("title", E.string(title)),
    ("choices", E.stringArray(names)),
    ("totals", E.array(E.int, totals)),
  ]);
};

let statisticsToJson = (orders: list(order), column: string): Js.Json.t => {
  let makeDistro = (comparator, getter) =>
    Belt.List.reduce(
      orders,
      Belt.Map.make(~id=comparator),
      (acc, item) => {
        let n = Belt.Map.getWithDefault(acc, getter(item), 0);
        Belt.Map.set(acc, getter(item), n + item.quantity);
      },
    );

  switch (column) {
  | "color" =>
    makeObject(
      "Color",
      makeDistro((module Shirt.ColorComparator), anOrder => anOrder.color),
      Shirt.Color.toString,
    )
  | "size" =>
    makeObject(
      "Size",
      makeDistro((module Shirt.SizeComparator), anOrder => anOrder.size),
      Shirt.Size.toString,
    )
  | "pattern" =>
    makeObject(
      "Pattern",
      makeDistro((module Shirt.PatternComparator), anOrder => anOrder.pattern),
      Shirt.Pattern.toString,
    )
  | "collar" =>
    makeObject(
      "Collar",
      makeDistro((module Shirt.CollarComparator), anOrder => anOrder.collar),
      Shirt.Collar.toString,
    )
  | "sleeve" =>
    makeObject(
      "Sleeve",
      makeDistro((module Shirt.SleeveComparator), anOrder => anOrder.sleeve),
      Shirt.Sleeve.toString,
    )
  | "cuff" =>
    makeObject(
      "Cuff",
      makeDistro((module Shirt.CuffComparator), anOrder => anOrder.cuff),
      Shirt.Cuff.toString,
    )
  | _ =>
    E.object_([
      ("title", E.string("Error")),
      ("choices", E.stringArray([||])),
      ("totals", E.array(E.int, [||])),
    ])
  };
};

let processFile = (inFileName: string, column: string): Js.Json.t => {
  let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
  let parseData = Results.dataGet(parseString(fileContents));
  let lines =
    Belt.Array.slice(
      parseData,
      ~offset=1,
      ~len=Belt.Array.length(parseData) - 1,
    );

  let orders = Belt.Array.reduce(lines, [], lineReducer);

  statisticsToJson(orders, column);
};