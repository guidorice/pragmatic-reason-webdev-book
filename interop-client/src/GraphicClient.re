module JD = Json.Decode;
module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let getValue = (element: option(Elem.t)): option(string) =>
  element
  ->Belt.Option.map(_, Elem.unsafeAsHtmlElement)
  ->Belt.Option.map(_, D.HtmlElement.value);

let theChart: ref(option(Chart.t)) = ref(None);
/* ... */

let capitalize = (s: string): string =>
  Js.String.toUpperCase(Js.String.get(s, 0))
  ++ Js.String.toLowerCase(Js.String.substr(s, ~from=1));

let processResponse = (json: Js.Json.t): unit => {
  let optResult = Doc.getElementById("resultGraph", D.document);

  switch (optResult) {
  | Some(resultElement) =>
    let title = JD.field("title", JD.string, json);
    let choices = JD.field("choices", JD.array(JD.string), json);
    let totals = JD.field("totals", JD.array(JD.int), json);

    let dataSet: Chart.Dataset.t =
      Chart.Dataset.t(
        ~label=title,
        ~data=Belt.Array.map(totals, float_of_int),
        ~backgroundColor=[||],
        ~borderColor=Belt.Array.make(Belt.Array.length(choices), "#000"),
        ~borderWidth=1,
      );

    let chartData: Chart.Data.t =
      Chart.Data.t(~labels=choices, ~datasets=[|dataSet|]);

    let xAxis: Chart.Axis.t =
      Chart.Axis.t(~ticks=Chart.Axis.Tickmark.t(~beginAtZero=true));
    let scale: Chart.Scale.t = Chart.Scale.t(~xAxes=[|xAxis|], ~yAxes=[||]);
    let chartOptions =
      Chart.Option.t(
        ~legend=Chart.Legend.t(~display=false),
        ~responsive=false,
        ~scales=scale,
      );
    let chartParams: Chart.Params.t =
      Chart.Params.t(
        ~type_="horizontalBar",
        ~data=chartData,
        ~options=chartOptions,
      );

    /* Destroy previous chart if it exists */
    switch (theChart^) {
    | Some(aChart) => Chart.destroy(aChart)
    | None => ()
    };
    theChart := Some(Chart.createChart(resultElement, chartParams));
    ();
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