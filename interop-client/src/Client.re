module JD = Json.Decode;
module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let getValue = (element: option(Elem.t)): option(string) =>
  element
  ->Belt.Option.map(_, Elem.unsafeAsHtmlElement)
  ->Belt.Option.map(_, D.HtmlElement.value);

/* ... */

/* utility routines for creating HTML string */
let capitalize = (s: string): string =>
  Js.String.toUpperCase(Js.String.get(s, 0))
  ++ Js.String.toLowerCase(Js.String.substr(s, ~from=1));

let makeTableRow = (choice: string, total: int): string =>
  "<tr><td>"
  ++ choice
  ++ "</td><td>"
  ++ string_of_int(total)
  ++ "</td></tr>\n";

let processResponse = (json: Js.Json.t): unit => {
  let optResult = Doc.getElementById("resultTable", D.document);

  switch (optResult) {
  | Some(resultElement) =>
    let title = JD.field("title", JD.string, json);
    let choices = JD.field("choices", JD.array(JD.string), json);
    let totals = JD.field("totals", JD.array(JD.int), json);
    let htmlStr =
      "<table><thead><tr><th>"
      ++ capitalize(title)
      ++ "</th><th>Total</th></tr>\n"
      ++ Belt.Array.reduce(
           Belt.Array.zip(choices, totals), "", (acc, (choice, total)) =>
           acc ++ makeTableRow(choice, total)
         )
      ++ "</table>\n";
    Elem.setInnerHTML(resultElement, htmlStr);
  | None => ()
  };
};

let sendRequest = (_: Dom.event): unit => {
  let choice = getValue(Doc.getElementById("category", D.document));
  switch (choice) {
  | Some(choiceString) =>
    if (choiceString != "") {
      Fetch.fetchWithInit(
        "http://localhost:3000/json" ++ "?choice=" ++ choiceString,
        Fetch.RequestInit.make(~method_=Get, ()),
      )
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json =>
           processResponse(json) |> Js.Promise.resolve
         )
      |> ignore;
    } else {
      ();
    }
  | None => ()
  };
};

let category = Doc.getElementById("category", D.document);
switch (category) {
| Some(element) =>
  D.EventTarget.addEventListener(
    "change",
    sendRequest,
    D.Element.asEventTarget(element),
  )
| None => ()
};