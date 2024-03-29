// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_Id = require("bs-platform/lib/js/belt_Id.js");
var Process = require("process");
var Belt_Map = require("bs-platform/lib/js/belt_Map.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

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

function compareSize(a, b) {
  if (typeof a === "number") {
    switch (a) {
      case 0 : 
          if (typeof b === "number") {
            if (b === 0) {
              return 0;
            } else {
              return -1;
            }
          } else if (b.tag) {
            return -1;
          } else {
            return 1;
          }
      case 1 : 
          if (typeof b === "number") {
            switch (b) {
              case 0 : 
                  return 1;
              case 1 : 
                  return 0;
              case 2 : 
                  return -1;
              
            }
          } else if (b.tag) {
            return -1;
          } else {
            return 1;
          }
      case 2 : 
          if (typeof b === "number") {
            if (b === 2) {
              return 0;
            } else {
              return 1;
            }
          } else if (b.tag === 1) {
            return -1;
          } else {
            return 1;
          }
      
    }
  } else if (a.tag) {
    if (typeof b === "number" || b.tag !== 1) {
      return 1;
    } else {
      return Caml_primitive.caml_int_compare(a[0], b[0]);
    }
  } else if (typeof b === "number" || b.tag) {
    return -1;
  } else {
    return Caml_primitive.caml_int_compare(a[0], b[0]);
  }
}

var Size = /* module */[
  /* toString */toString,
  /* fromString */fromString,
  /* compareSize */compareSize
];

var SizeComparator = Belt_Id.MakeComparable(/* module */[/* cmp */compareSize]);

function toString$1(sleeve) {
  switch (sleeve) {
    case 0 : 
        return "short sleeve";
    case 1 : 
        return "long sleeve";
    case 2 : 
        return "extra-long sleeve";
    
  }
}

function fromString$1(str) {
  var match = str.toLowerCase();
  switch (match) {
    case "long" : 
        return /* Long */1;
    case "short" : 
        return /* Short */0;
    case "xlong" : 
        return /* XLong */2;
    default:
      return undefined;
  }
}

var Sleeve = /* module */[
  /* toString */toString$1,
  /* fromString */fromString$1
];

var cmp = Caml_obj.caml_compare;

var SleeveComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp]);

function toString$2(color) {
  switch (color) {
    case 0 : 
        return "white";
    case 1 : 
        return "blue";
    case 2 : 
        return "red";
    case 3 : 
        return "green";
    case 4 : 
        return "brown";
    
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

var cmp$1 = Caml_obj.caml_compare;

var ColorComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp$1]);

function toString$3(pattern) {
  switch (pattern) {
    case 0 : 
        return "solid";
    case 1 : 
        return "pinstripe";
    case 2 : 
        return "check";
    
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

var cmp$2 = Caml_obj.caml_compare;

var PatternComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp$2]);

function toString$4(cuff) {
  switch (cuff) {
    case 0 : 
        return "button";
    case 1 : 
        return "french";
    case 2 : 
        return "none";
    
  }
}

function fromString$4(s) {
  var match = s.toLowerCase();
  switch (match) {
    case "button" : 
        return /* Button */0;
    case "french" : 
        return /* French */1;
    case "" : 
    case "nocuff" : 
    case "none" : 
        return /* NoCuff */2;
    default:
      return undefined;
  }
}

var Cuff = /* module */[
  /* toString */toString$4,
  /* fromString */fromString$4
];

var cmp$3 = Caml_obj.caml_compare;

var CuffComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp$3]);

function toString$5(collar) {
  switch (collar) {
    case 0 : 
        return "button";
    case 1 : 
        return "straight";
    case 2 : 
        return "spread";
    
  }
}

function fromString$5(s) {
  var match = s.toLowerCase();
  switch (match) {
    case "button" : 
        return /* Button */0;
    case "spread" : 
        return /* Spread */2;
    case "straight" : 
        return /* Straight */1;
    default:
      return undefined;
  }
}

var Collar = /* module */[
  /* toString */toString$5,
  /* fromString */fromString$5
];

var cmp$4 = Caml_obj.caml_compare;

var CollarComparator = Belt_Id.MakeComparable(/* module */[/* cmp */cmp$4]);

function optFloat(str) {
  var exit = 0;
  var fNum;
  try {
    fNum = Caml_format.caml_float_of_string(str);
    exit = 1;
  }
  catch (raw_exn){
    var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
    if (exn[0] === Caml_builtin_exceptions.failure) {
      if (exn[1] === "float_of_string") {
        return undefined;
      } else {
        throw exn;
      }
    } else {
      throw exn;
    }
  }
  if (exit === 1) {
    return fNum;
  }
  
}

function optInt(str) {
  var exit = 0;
  var anInt;
  try {
    anInt = Caml_format.caml_int_of_string(str);
    exit = 1;
  }
  catch (raw_exn){
    var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
    if (exn[0] === Caml_builtin_exceptions.failure) {
      if (exn[1] === "int_of_string") {
        return undefined;
      } else {
        throw exn;
      }
    } else {
      throw exn;
    }
  }
  if (exit === 1) {
    return anInt;
  }
  
}

function map2(optX, optY, f) {
  if (optX !== undefined && optY !== undefined) {
    return Caml_option.some(Curry._2(f, Caml_option.valFromOption(optX), Caml_option.valFromOption(optY)));
  }
  
}

function lineReducer(acc, line) {
  var items = line.split(",");
  if (items.length !== 7) {
    return acc;
  } else {
    var orderRecord = map2(map2(map2(map2(map2(map2(map2(/* record */[
                                  /* quantity */0,
                                  /* size : Small */0,
                                  /* sleeve : Short */0,
                                  /* color : White */0,
                                  /* pattern : Solid */0,
                                  /* cuff : Button */0,
                                  /* collar : Straight */1
                                ], optInt(Caml_array.caml_array_get(items, 0)), (function (result, n) {
                                    return /* record */[
                                            /* quantity */n,
                                            /* size */result[/* size */1],
                                            /* sleeve */result[/* sleeve */2],
                                            /* color */result[/* color */3],
                                            /* pattern */result[/* pattern */4],
                                            /* cuff */result[/* cuff */5],
                                            /* collar */result[/* collar */6]
                                          ];
                                  })), fromString(Caml_array.caml_array_get(items, 1)), (function (result, sz) {
                                return /* record */[
                                        /* quantity */result[/* quantity */0],
                                        /* size */sz,
                                        /* sleeve */result[/* sleeve */2],
                                        /* color */result[/* color */3],
                                        /* pattern */result[/* pattern */4],
                                        /* cuff */result[/* cuff */5],
                                        /* collar */result[/* collar */6]
                                      ];
                              })), fromString$2(Caml_array.caml_array_get(items, 2)), (function (result, c) {
                            return /* record */[
                                    /* quantity */result[/* quantity */0],
                                    /* size */result[/* size */1],
                                    /* sleeve */result[/* sleeve */2],
                                    /* color */c,
                                    /* pattern */result[/* pattern */4],
                                    /* cuff */result[/* cuff */5],
                                    /* collar */result[/* collar */6]
                                  ];
                          })), fromString$3(Caml_array.caml_array_get(items, 3)), (function (result, pat) {
                        return /* record */[
                                /* quantity */result[/* quantity */0],
                                /* size */result[/* size */1],
                                /* sleeve */result[/* sleeve */2],
                                /* color */result[/* color */3],
                                /* pattern */pat,
                                /* cuff */result[/* cuff */5],
                                /* collar */result[/* collar */6]
                              ];
                      })), fromString$5(Caml_array.caml_array_get(items, 4)), (function (result, coll) {
                    return /* record */[
                            /* quantity */result[/* quantity */0],
                            /* size */result[/* size */1],
                            /* sleeve */result[/* sleeve */2],
                            /* color */result[/* color */3],
                            /* pattern */result[/* pattern */4],
                            /* cuff */result[/* cuff */5],
                            /* collar */coll
                          ];
                  })), fromString$1(Caml_array.caml_array_get(items, 5)), (function (result, sleeve) {
                return /* record */[
                        /* quantity */result[/* quantity */0],
                        /* size */result[/* size */1],
                        /* sleeve */sleeve,
                        /* color */result[/* color */3],
                        /* pattern */result[/* pattern */4],
                        /* cuff */result[/* cuff */5],
                        /* collar */result[/* collar */6]
                      ];
              })), fromString$4(Caml_array.caml_array_get(items, 6)), (function (result, cuff) {
            return /* record */[
                    /* quantity */result[/* quantity */0],
                    /* size */result[/* size */1],
                    /* sleeve */result[/* sleeve */2],
                    /* color */result[/* color */3],
                    /* pattern */result[/* pattern */4],
                    /* cuff */cuff,
                    /* collar */result[/* collar */6]
                  ];
          }));
    if (orderRecord !== undefined) {
      return /* :: */[
              orderRecord,
              acc
            ];
    } else {
      return acc;
    }
  }
}

function printMap(title, distribution, toString) {
  console.log(title, "Quantity");
  Belt_Map.forEach(distribution, (function (key, value) {
          console.log(Curry._1(toString, key), value);
          return /* () */0;
        }));
  console.log("");
  return /* () */0;
}

function printStatistics(orders) {
  var makeDistro = function (comparator, getter) {
    return Belt_List.reduce(orders, Belt_Map.make(comparator), (function (acc, item) {
                  var n = Belt_Map.getWithDefault(acc, Curry._1(getter, item), 0);
                  return Belt_Map.set(acc, Curry._1(getter, item), n + item[/* quantity */0] | 0);
                }));
  };
  var colorDistribution = makeDistro(ColorComparator, (function (ord) {
          return ord[/* color */3];
        }));
  printMap("Color", colorDistribution, toString$2);
  var sizeDistribution = makeDistro(SizeComparator, (function (ord) {
          return ord[/* size */1];
        }));
  printMap("Size", sizeDistribution, toString);
  var patternDistribution = makeDistro(PatternComparator, (function (ord) {
          return ord[/* pattern */4];
        }));
  printMap("Pattern", patternDistribution, toString$3);
  var collarDistribution = makeDistro(CollarComparator, (function (ord) {
          return ord[/* collar */6];
        }));
  printMap("Collar", collarDistribution, toString$5);
  var sleeveDistribution = makeDistro(SleeveComparator, (function (ord) {
          return ord[/* sleeve */2];
        }));
  printMap("Sleeve", sleeveDistribution, toString$1);
  var cuffDistribution = makeDistro(CuffComparator, (function (ord) {
          return ord[/* cuff */5];
        }));
  return printMap("Cuff", cuffDistribution, toString$4);
}

function processFile(inFileName) {
  var fileContents = Fs.readFileSync(inFileName, "utf8");
  var lines = fileContents.split("\n").slice(1);
  return printStatistics(Belt_Array.reduce(lines, /* [] */0, lineReducer));
}

var nodeArg = Belt_Array.get(Process.argv, 0);

var progArg = Belt_Array.get(Process.argv, 1);

var fileArg = Belt_Array.get(Process.argv, 2);

if (fileArg !== undefined) {
  processFile(fileArg);
} else if (nodeArg !== undefined && progArg !== undefined) {
  console.log("Usage: " + (nodeArg + (" " + (progArg + " inputfile.csv"))));
} else {
  console.log("How did you get here without NodeJS or a program to run?");
}

exports.Size = Size;
exports.SizeComparator = SizeComparator;
exports.Sleeve = Sleeve;
exports.SleeveComparator = SleeveComparator;
exports.Color = Color;
exports.ColorComparator = ColorComparator;
exports.Pattern = Pattern;
exports.PatternComparator = PatternComparator;
exports.Cuff = Cuff;
exports.CuffComparator = CuffComparator;
exports.Collar = Collar;
exports.CollarComparator = CollarComparator;
exports.optFloat = optFloat;
exports.optInt = optInt;
exports.map2 = map2;
exports.lineReducer = lineReducer;
exports.printMap = printMap;
exports.printStatistics = printStatistics;
exports.processFile = processFile;
exports.nodeArg = nodeArg;
exports.progArg = progArg;
exports.fileArg = fileArg;
/* SizeComparator Not a pure module */
