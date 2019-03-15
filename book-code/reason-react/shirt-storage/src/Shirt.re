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
  exception InvalidSize;

  let decodeJson = (str: string): t =>
    switch (fromString(str)) {
      | Some(size) => size
      | None => raise(InvalidSize)
    };
};

module Sleeve = {
  type t =
    | Short
    | Long
    | XLong; /* for tall people */

  let toString = (sleeve: t): string =>
    switch (sleeve) {
    | Short => "Short sleeve"
    | Long => "Long sleeve"
    | XLong => "Extra-long sleeve"
    };

  let fromString = (str: string): option(t) =>
    switch (Js.String.toLowerCase(str)) {
    | "short"
    | "short sleeve" => Some(Short)
    | "long"
    | "long sleeve" => Some(Long)
    | "extra"
    | "extra-long sleeve"
    | "xlong"
    | "xlong sleeve" => Some(XLong)
    | _ => None
    };
    
  exception InvalidSleeve;

  let decodeJson = (str: string): t =>
    switch (fromString(str)) {
      | Some(sleeve) => sleeve
      | None => raise(InvalidSleeve)
    };
};

module Color = {
  type t =
    | White
    | Blue
    | Red
    | Green
    | Brown;

  let toString = (color: t): string =>
    switch (color) {
    | White => "White"
    | Blue => "Blue"
    | Red => "Red"
    | Green => "Green"
    | Brown => "Brown"
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

  exception InvalidColor;
  
  let decodeJson = (str: string): t =>
    switch (fromString(str)) {
      | Some(color) => color
      | None => raise(InvalidColor)
    };
};

module Pattern = {
  type t =
    | Solid
    | Pinstripe
    | Check;

  let toString = (pattern: t): string =>
    switch (pattern) {
    | Solid => "Solid"
    | Pinstripe => "Pinstripe"
    | Check => "Checked"
    };

  let fromString = (s: string): option(t) =>
    switch (Js.String.toLowerCase(s)) {
    | "solid" => Some(Solid)
    | "pinstripe" => Some(Pinstripe)
    | "check"
    | "checked" => Some(Check)
    | _ => None
    };

  exception InvalidPattern;
  
  let decodeJson = (str: string): t =>
    switch (fromString(str)) {
      | Some(pattern) => pattern
      | None => raise(InvalidPattern)
    };
};

module E = Json.Encode;
module D = Json.Decode;

module Order = {
  type t = {
    orderNumber: int,
    quantity: int,
    size: Size.t,
    sleeve: Sleeve.t,
    color: Color.t,
    pattern: Pattern.t,
  };

  let encodeJson = (order: t): Js.Json.t => {
   E.object_([
   ("orderNumber", E.int(order.orderNumber)),
   ("quantity", E.int(order.quantity)),
   ("size", E.string(Size.toString(order.size))),
   ("sleeve", E.string(Sleeve.toString(order.sleeve))),
   ("color", E.string(Color.toString(order.color))),
   ("pattern", E.string(Pattern.toString(order.pattern)))
   ])
  };
    
  let decodeJson = (json: Js.Json.t): t => {
    {
      orderNumber: D.field("orderNumber", D.int, json),
      quantity: D.field("quantity", D.int, json),
      size: Size.decodeJson(D.field("size", D.string, json)),
      sleeve: Sleeve.decodeJson(D.field("sleeve", D.string, json)),
      color: Color.decodeJson(D.field("color", D.string, json)),
      pattern: Pattern.decodeJson(D.field("pattern", D.string, json))
    }
  }
};
