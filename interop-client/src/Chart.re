type t;

module Dataset = {
  [@bs.deriving abstract]
  type t = {
    label: string,
    data: array(float),
    backgroundColor: array(string),
    borderColor: array(string),
    borderWidth: int,
  };
};

module Data = {
  [@bs.deriving abstract]
  type t = {
    labels: array(string),
    datasets: array(Dataset.t),
  };
};

module Legend = {
  [@bs.deriving abstract]
  type t = {display: bool};
};

module Axis = {
  module Tickmark = {
    [@bs.deriving abstract]
    type t = {beginAtZero: bool};
  };
  [@bs.deriving abstract]
  type t = {ticks: Tickmark.t};
};

module Scale = {
  [@bs.deriving abstract]
  type t = {
    xAxes: array(Axis.t),
    yAxes: array(Axis.t),
  };
};

module Option = {
  [@bs.deriving abstract]
  type t = {
    legend: Legend.t,
    responsive: bool,
    scales: Scale.t,
  };
};

module Params = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "type"]
    type_: string,
    data: Data.t,
    options: Option.t,
  };
};

[@bs.new]
external createChart: (Webapi.Dom.Element.t, Params.t) => t = "Chart";
[@bs.send] external destroy: t => unit = "";