module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let principalInput = Doc.getElementById("principal", D.document);
let aprInput = Doc.getElementById("apr", D.document);
let yearsInput = Doc.getElementById("years", D.document);
let paymentElement = Doc.getElementById("payment", D.document);

let payment = (~principal, ~apr, ~years) => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
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

let toFloat = (s: string): option(float) =>
  switch (float_of_string(s)) {
  | result => Some(result)
  | exception (Failure("float_of_string")) => None
  };

let currencyFmt = (price: option(float)) =>
  switch (price) {
  | Some(total) => Js.Float.toFixedWithPrecision(total, ~digits=2)
  | None => "..."
  };

let handleCalculate = (_: Dom.event) => {
  let principal = getValue(principalInput)->Belt.Option.flatMap(_, toFloat);
  let apr = getValue(aprInput)->Belt.Option.flatMap(_, toFloat);
  let years = getValue(yearsInput)->Belt.Option.flatMap(_, toInt);
  let monthlyPayment =
    switch (principal, apr, years) {
    | (Some(principal), Some(apr), Some(years)) =>
      Some(payment(~principal, ~apr, ~years))
    | (_, _, _) => None
    };
  let _ =
    paymentElement
    ->Belt.Option.map(_, Elem.setInnerText(_, currencyFmt(monthlyPayment)));
  ();
};

switch (principalInput) {
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

switch (aprInput) {
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

switch (yearsInput) {
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