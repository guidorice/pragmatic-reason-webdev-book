// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var $$String = require("bs-platform/lib/js/string.js");

function toString(size) {
  if (typeof size === "number") {
    switch (size) {
      case 0 : 
          return "S";
      case 1 : 
          return "M";
      case 2 : 
          return "L";
      
    }
  } else if (size.tag) {
    return $$String.make(size[0], /* "X" */88) + "L";
  } else {
    return $$String.make(size[0], /* "X" */88) + "S";
  }
}

function fromString(str) {
  var s = str.toUpperCase();
  switch (s) {
    case "L" : 
        return /* Large */2;
    case "M" : 
        return /* Medium */1;
    case "S" : 
        return /* Small */0;
    default:
      if ((/^X+S$/).test(s)) {
        return /* XSmall */Block.__(0, [s.length - 1 | 0]);
      } else if ((/^X+L$/).test(s)) {
        return /* XLarge */Block.__(1, [s.length - 1 | 0]);
      } else {
        return undefined;
      }
  }
}

var Size = /* module */[
  /* toString */toString,
  /* fromString */fromString
];

function toString$1(sleeve) {
  switch (sleeve) {
    case 0 : 
        return "Short sleeve";
    case 1 : 
        return "Long sleeve";
    case 2 : 
        return "Extra-long sleeve";
    
  }
}

function fromString$1(str) {
  var match = str.toLowerCase();
  switch (match) {
    case "long" : 
    case "long sleeve" : 
        return /* Long */1;
    case "short" : 
    case "short sleeve" : 
        return /* Short */0;
    case "extra-long" : 
    case "extra-long sleeve" : 
    case "xlong" : 
    case "xlong sleeve" : 
        return /* XLong */2;
    default:
      return undefined;
  }
}

var Sleeve = /* module */[
  /* toString */toString$1,
  /* fromString */fromString$1
];

function toString$2(color) {
  switch (color) {
    case 0 : 
        return "White";
    case 1 : 
        return "Blue";
    case 2 : 
        return "Red";
    case 3 : 
        return "Green";
    case 4 : 
        return "Brown";
    
  }
}

function fromString$2(s) {
  var match = s.toLowerCase();
  switch (match) {
    case "blue" : 
        return /* Blue */1;
    case "brown" : 
        return /* Brown */4;
    case "green" : 
        return /* Green */3;
    case "red" : 
        return /* Red */2;
    case "white" : 
        return /* White */0;
    default:
      return undefined;
  }
}

var Color = /* module */[
  /* toString */toString$2,
  /* fromString */fromString$2
];

function toString$3(pattern) {
  switch (pattern) {
    case 0 : 
        return "Solid";
    case 1 : 
        return "Pinstripe";
    case 2 : 
        return "Checked";
    
  }
}

function fromString$3(s) {
  var match = s.toLowerCase();
  switch (match) {
    case "check" : 
    case "checked" : 
        return /* Check */2;
    case "pinstripe" : 
        return /* Pinstripe */1;
    case "solid" : 
        return /* Solid */0;
    default:
      return undefined;
  }
}

var Pattern = /* module */[
  /* toString */toString$3,
  /* fromString */fromString$3
];

var Order = /* module */[];

exports.Size = Size;
exports.Sleeve = Sleeve;
exports.Color = Color;
exports.Pattern = Pattern;
exports.Order = Order;
/* No side effect */
