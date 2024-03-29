// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Fetch = require("bs-fetch/src/Fetch.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function getValue(element) {
  var __x = Belt_Option.map(element, (function (prim) {
          return prim;
        }));
  return Belt_Option.map(__x, (function (prim) {
                return prim.value;
              }));
}

var theChart = /* record */[/* contents */undefined];

function capitalize(s) {
  return s[0].toUpperCase() + s.substr(1).toLowerCase();
}

function processResponse(json) {
  var optResult = document.getElementById("resultGraph");
  if (optResult == null) {
    return /* () */0;
  } else {
    var title = Json_decode.field("title", Json_decode.string, json);
    var choices = Json_decode.field("choices", (function (param) {
            return Json_decode.array(Json_decode.string, param);
          }), json);
    var totals = Json_decode.field("totals", (function (param) {
            return Json_decode.array(Json_decode.$$int, param);
          }), json);
    var dataSet = {
      label: title,
      data: Belt_Array.map(totals, (function (prim) {
              return prim;
            })),
      backgroundColor: /* array */[],
      borderColor: Belt_Array.make(choices.length, "#000"),
      borderWidth: 1
    };
    var chartData = {
      labels: choices,
      datasets: /* array */[dataSet]
    };
    var xAxis = {
      ticks: {
        beginAtZero: true
      }
    };
    var scale = {
      xAxes: /* array */[xAxis],
      yAxes: /* array */[]
    };
    var chartOptions = {
      legend: {
        display: false
      },
      responsive: false,
      scales: scale
    };
    var chartParams = {
      type: "horizontalBar",
      data: chartData,
      options: chartOptions
    };
    var match = theChart[0];
    if (match !== undefined) {
      Caml_option.valFromOption(match).destroy();
    }
    theChart[0] = Caml_option.some(new Chart(optResult, chartParams));
    return /* () */0;
  }
}

function sendRequest(param) {
  var choice = getValue(Caml_option.nullable_to_opt(document.getElementById("category")));
  if (choice !== undefined) {
    var choiceString = choice;
    if (choiceString !== "") {
      fetch("http://localhost:3000/json?choice=" + choiceString, Fetch.RequestInit[/* make */0](/* Get */0, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                return prim.json();
              })).then((function (json) {
              return Promise.resolve(processResponse(json));
            }));
      return /* () */0;
    } else {
      return /* () */0;
    }
  } else {
    return /* () */0;
  }
}

var category = document.getElementById("category");

if (!(category == null)) {
  category.addEventListener("change", sendRequest);
}

var JD = 0;

var D = 0;

var Doc = 0;

var Elem = 0;

var category$1 = (category == null) ? undefined : Caml_option.some(category);

exports.JD = JD;
exports.D = D;
exports.Doc = Doc;
exports.Elem = Elem;
exports.getValue = getValue;
exports.theChart = theChart;
exports.capitalize = capitalize;
exports.processResponse = processResponse;
exports.sendRequest = sendRequest;
exports.category = category$1;
/* category Not a pure module */
