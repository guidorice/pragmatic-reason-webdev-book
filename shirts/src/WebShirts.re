module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

type shirtSize =
  | Small
  | Medium
  | Large
  | XLarge(int);

let price = size =>
  switch (size) {
  | Small => 11.00
  | Medium => 12.50
  | Large => 14.00
  | XLarge(n) => 16.00 +. float_of_int(n - 1) *. 0.5
  };

let shirtSizeOfString = (str: string): option(shirtSize) =>
  switch (str) {
  | "S" => Some(Small)
  | "M" => Some(Medium)
  | "L" => Some(Large)
  | "XL" => Some(XLarge(1))
  | "XXL" => Some(XLarge(2))
  | "XXXL" => Some(XLarge(3))
  | "XXXXL" => Some(XLarge(4))
  | _ => None
  };

let getValue = (element: option(Elem.t)): option(string) =>
  element
  ->Belt.Option.map(_, Elem.unsafeAsHtmlElement)
  ->Belt.Option.map(_, D.HtmlElement.value);

let toInt = (s: string): option(int) =>
  switch (int_of_string(s)) {
  | result => Some(result)
  | exception (Failure("int_of_string")) => None
  };
let handleCalculate = (_: Dom.event) => {
  let quantity =
    getValue(Doc.getElementById("quantity", D.document))
    ->Belt.Option.flatMap(_, toInt);

  let unitPrice =
    getValue(Doc.getElementById("size", D.document))
    ->Belt.Option.flatMap(_, shirtSizeOfString)
    ->Belt.Option.map(_, price);

  let totalPrice =
    switch (quantity, unitPrice) {
    | (Some(quantity), Some(unitPrice)) =>
      Some(unitPrice *. float_of_int(quantity))
    | (_, _) => None
    };

  let priceFormatter = (price: option(float)) =>
    switch (price) {
    | Some(total) => Js.Float.toFixedWithPrecision(total, ~digits=2)
    | None => ""
    };

  let _ =
    Doc.getElementById("totalPrice", D.document)
    ->Belt.Option.map(_, Elem.setInnerText(_, priceFormatter(totalPrice)));

  let _ =
    Doc.getElementById("unitPrice", D.document)
    ->Belt.Option.map(_, Elem.setInnerText(_, priceFormatter(unitPrice)));
  ();
};

let calcButton = Doc.getElementById("calculate", D.document);
let quantityInput = Doc.getElementById("quantity", D.document);
let sizeSelect = Doc.getElementById("size", D.document);

switch (calcButton) {
| Some(element) =>
  D.EventTarget.addEventListener(
    "click",
    handleCalculate,
    Elem.asEventTarget(element),
  )
| None => ()
};

switch (quantityInput) {
| Some(element) =>
  D.EventTarget.addEventListener(
    "change",
    handleCalculate,
    Elem.asEventTarget(element),
  );
  D.EventTarget.addEventListener(
    "input",
    handleCalculate,
    Elem.asEventTarget(element),
  );
| None => ()
};

switch (sizeSelect) {
| Some(element) =>
  D.EventTarget.addEventListener(
    "change",
    handleCalculate,
    Elem.asEventTarget(element),
  )
| None => ()
};