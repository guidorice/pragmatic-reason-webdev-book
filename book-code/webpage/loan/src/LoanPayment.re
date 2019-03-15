module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;
module Node = Webapi.Dom.Node;

let toInt = (s:string): option(int) => {
  switch (int_of_string(s)) {
    | result => Some(result)
    | exception(Failure("int_of_string")) => None
  }
};

let toFloat = (s:string): option(float) => {
  switch (float_of_string(s)) {
    | result => Some(result)
    | exception(Failure("float_of_string")) => None
  }
};

let getStringValue = (elementId: string) : option(string) => {
  Doc.getElementById(elementId, D.document)
  -> Belt.Option.map(Elem.unsafeAsHtmlElement)
  -> Belt.Option.map(D.HtmlElement.value);
};

let getIntValue = (elementId: string) : option(int) => {
  getStringValue(elementId) -> Belt.Option.flatMap(toInt)
};

let getFloatValue = (elementId: string) : option(float) => {
  getStringValue(elementId) -> Belt.Option.flatMap(toFloat)
};

let payment = (~principal, ~apr, ~years) => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
};

let calculate = (_) : unit => {
  let principal = getFloatValue("principal");
  let apr = getFloatValue("apr");
  let years = getIntValue("years");
    
  let payment = switch (principal, apr, years) {
    | (Some(principal), Some(apr), Some(years)) => 
        Some(payment(~principal=principal, ~apr=apr, ~years=years))
    | (_, _, _) => None
  };
  
  let paymentString = switch (payment) {
    | Some(p) => Js.Float.toFixedWithPrecision(p, ~digits=2)
    | None => ""
  };

  let _ = Doc.getElementById("payment", D.document) ->
    Belt.Option.map(Elem.setInnerText(_, paymentString));
  
  (); /* return unit */
};

let setOnChange = (elementId: string, f: (Dom.event) => unit) : unit => {
  let el = Doc.getElementById(elementId, D.document);
  switch (el) {
    | Some(element) => D.EventTarget.addEventListener(
      "change", f, D.Element.asEventTarget(element))
    | None => ()
  };
};

setOnChange("principal", calculate);
setOnChange("apr", calculate);
setOnChange("years", calculate);
