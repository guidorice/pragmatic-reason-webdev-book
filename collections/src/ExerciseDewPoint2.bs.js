// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ArrayLabels = require("bs-platform/lib/js/arrayLabels.js");

function dewpoint(param) {
  return param[0] - (100 - param[1] | 0) / 5.0;
}

var readings = /* :: */[
  /* tuple */[
    12.5,
    30
  ],
  /* :: */[
    /* tuple */[
      13.7,
      35
    ],
    /* :: */[
      /* tuple */[
        13.2,
        32
      ],
      /* :: */[
        /* tuple */[
          13.7,
          39
        ],
        /* [] */0
      ]
    ]
  ]
];

console.log("readings:", Belt_List.toArray(readings));

function maxOfArray(arr) {
  return ArrayLabels.fold_left(Caml_obj.caml_max, Number.MIN_VALUE, arr);
}

function minOfArray(arr) {
  return ArrayLabels.fold_left(Caml_obj.caml_min, Number.MAX_VALUE, arr);
}

var temps = Belt_List.map(readings, (function (param) {
        return param[0];
      }));

var dewpoints = Belt_List.map(readings, dewpoint);

var maxTemp = maxOfArray(Belt_List.toArray(temps));

var minTemp = minOfArray(Belt_List.toArray(temps));

var maxDp = maxOfArray(Belt_List.toArray(dewpoints));

var minDp = minOfArray(Belt_List.toArray(dewpoints));

console.log("max temp: " + Pervasives.string_of_float(maxTemp));

console.log("min temp: " + Pervasives.string_of_float(minTemp));

console.log("max dewpoint: " + Pervasives.string_of_float(maxDp));

console.log("min dewpoint: " + Pervasives.string_of_float(minDp));

function avg(list) {
  var n = Belt_List.length(list);
  var sum = Belt_List.reduce(list, 0, (function (t, acc) {
          return acc + t;
        }));
  return sum / n;
}

var avgTemp = avg(temps);

console.log("average temp: " + Pervasives.string_of_float(avgTemp));

var avgDewpoint = avg(dewpoints);

console.log("average dewpoint: " + Pervasives.string_of_float(avgDewpoint));

var maxTemps = Belt_List.reduceWithIndex(temps, /* [] */0, (function (acc, t, i) {
        if (t === maxTemp) {
          return /* :: */[
                  i + 1 | 0,
                  acc
                ];
        } else {
          return acc;
        }
      }));

console.log("max temperatures occurred: ", Belt_List.toArray(maxTemps));

var minTemps = Belt_List.reduceWithIndex(temps, /* [] */0, (function (acc, t, i) {
        if (t === minTemp) {
          return /* :: */[
                  i + 1 | 0,
                  acc
                ];
        } else {
          return acc;
        }
      }));

console.log("min temperatures occurred: ", Belt_List.toArray(minTemps));

exports.dewpoint = dewpoint;
exports.readings = readings;
exports.maxOfArray = maxOfArray;
exports.minOfArray = minOfArray;
exports.temps = temps;
exports.dewpoints = dewpoints;
exports.maxTemp = maxTemp;
exports.minTemp = minTemp;
exports.maxDp = maxDp;
exports.minDp = minDp;
exports.avg = avg;
exports.avgTemp = avgTemp;
exports.avgDewpoint = avgDewpoint;
exports.maxTemps = maxTemps;
exports.minTemps = minTemps;
/*  Not a pure module */
