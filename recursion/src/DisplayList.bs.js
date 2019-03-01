// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

function stringOfList(items, stringify) {
  var helper = function (_accumulator, _theList) {
    while(true) {
      var theList = _theList;
      var accumulator = _accumulator;
      if (theList) {
        var xs = theList[1];
        var x = theList[0];
        if (xs) {
          _theList = xs;
          _accumulator = accumulator + (Curry._1(stringify, x) + ", ");
          continue ;
        } else {
          return accumulator + Curry._1(stringify, x);
        }
      } else {
        return accumulator;
      }
    };
  };
  return helper("[", items) + "]";
}

var items = /* :: */[
  10,
  /* :: */[
    11,
    /* :: */[
      12,
      /* :: */[
        13,
        /* :: */[
          14,
          /* :: */[
            15,
            /* [] */0
          ]
        ]
      ]
    ]
  ]
];

var floatItems = /* :: */[
  3.6,
  /* :: */[
    7.9,
    /* :: */[
      8.25,
      /* :: */[
        41.0,
        /* [] */0
      ]
    ]
  ]
];

exports.items = items;
exports.floatItems = floatItems;
exports.stringOfList = stringOfList;
/* No side effect */
