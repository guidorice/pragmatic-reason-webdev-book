// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var Shirt$ReactTemplate = require("./Shirt.bs.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var OrderItem$ReactTemplate = require("./OrderItem.bs.js");

function toInt(s) {
  var exit = 0;
  var result;
  try {
    result = Caml_format.caml_int_of_string(s);
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
    return result;
  }
  
}

function encodeState(s) {
  var match = s[/* editingNumber */8];
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "qtyStr",
                s[/* qtyStr */0]
              ],
              /* :: */[
                /* tuple */[
                  "sizeStr",
                  s[/* sizeStr */1]
                ],
                /* :: */[
                  /* tuple */[
                    "sleeveStr",
                    s[/* sleeveStr */2]
                  ],
                  /* :: */[
                    /* tuple */[
                      "colorStr",
                      s[/* colorStr */3]
                    ],
                    /* :: */[
                      /* tuple */[
                        "patternStr",
                        s[/* patternStr */4]
                      ],
                      /* :: */[
                        /* tuple */[
                          "nextOrderNumber",
                          s[/* nextOrderNumber */5]
                        ],
                        /* :: */[
                          /* tuple */[
                            "orders",
                            Json_encode.array(Shirt$ReactTemplate.Order[/* encodeJson */0], s[/* orders */6])
                          ],
                          /* :: */[
                            /* tuple */[
                              "errorText",
                              s[/* errorText */7]
                            ],
                            /* :: */[
                              /* tuple */[
                                "editingNumber",
                                match !== undefined ? match : -1
                              ],
                              /* [] */0
                            ]
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

function decodeState(json) {
  var partial_arg = Shirt$ReactTemplate.Order[/* decodeJson */1];
  var optN = Json_decode.field("editingNumber", Json_decode.$$int, json);
  return /* record */[
          /* qtyStr */Json_decode.field("qtyStr", Json_decode.string, json),
          /* sizeStr */Json_decode.field("sizeStr", Json_decode.string, json),
          /* sleeveStr */Json_decode.field("sleeveStr", Json_decode.string, json),
          /* colorStr */Json_decode.field("colorStr", Json_decode.string, json),
          /* patternStr */Json_decode.field("patternStr", Json_decode.string, json),
          /* nextOrderNumber */Json_decode.field("nextOrderNumber", Json_decode.$$int, json),
          /* orders */Json_decode.field("orders", (function (param) {
                  return Json_decode.array(partial_arg, param);
                }), json),
          /* errorText */Json_decode.field("errorText", Json_decode.string, json),
          /* editingNumber */optN !== -1 ? optN : undefined
        ];
}

var localStorageKey = "shirt-orders";

function storeStateLocally(theState) {
  var jsState = encodeState(theState);
  localStorage.setItem(localStorageKey, JSON.stringify(jsState));
  return /* () */0;
}

function getStoredState(param) {
  var neutralState_006 = /* orders : array */[];
  var neutralState = /* record */[
    /* qtyStr */"",
    /* sizeStr */"",
    /* sleeveStr */"",
    /* colorStr */"",
    /* patternStr */"",
    /* nextOrderNumber */1,
    neutralState_006,
    /* errorText */"",
    /* editingNumber */undefined
  ];
  var optItem = localStorage.getItem(localStorageKey);
  if (optItem !== null) {
    var exit = 0;
    var result;
    try {
      result = JSON.parse(optItem);
      exit = 1;
    }
    catch (exn){
      return neutralState;
    }
    if (exit === 1) {
      return decodeState(result);
    }
    
  } else {
    return neutralState;
  }
}

function makeSelect(label, choices, value, changeFcn) {
  var makeOptionElement = function (value) {
    return React.createElement("option", {
                key: value,
                value: value
              }, value);
  };
  var menuOptionElements = Belt_Array.concat(/* array */[React.createElement("option", {
              key: "",
              value: ""
            }, label)], Belt_Array.map(choices, makeOptionElement));
  return React.createElement("span", {
              className: "item"
            }, React.createElement("select", {
                  value: value,
                  onChange: changeFcn
                }, menuOptionElements));
}

function setQty(order, qty) {
  return /* record */[
          /* orderNumber */order[/* orderNumber */0],
          /* quantity */qty,
          /* size */order[/* size */2],
          /* sleeve */order[/* sleeve */3],
          /* color */order[/* color */4],
          /* pattern */order[/* pattern */5]
        ];
}

function setSize(order, newSize) {
  return /* record */[
          /* orderNumber */order[/* orderNumber */0],
          /* quantity */order[/* quantity */1],
          /* size */newSize,
          /* sleeve */order[/* sleeve */3],
          /* color */order[/* color */4],
          /* pattern */order[/* pattern */5]
        ];
}

function setSleeve(order, newSleeve) {
  return /* record */[
          /* orderNumber */order[/* orderNumber */0],
          /* quantity */order[/* quantity */1],
          /* size */order[/* size */2],
          /* sleeve */newSleeve,
          /* color */order[/* color */4],
          /* pattern */order[/* pattern */5]
        ];
}

function setColor(order, newColor) {
  return /* record */[
          /* orderNumber */order[/* orderNumber */0],
          /* quantity */order[/* quantity */1],
          /* size */order[/* size */2],
          /* sleeve */order[/* sleeve */3],
          /* color */newColor,
          /* pattern */order[/* pattern */5]
        ];
}

function setPattern(order, newPattern) {
  return /* record */[
          /* orderNumber */order[/* orderNumber */0],
          /* quantity */order[/* quantity */1],
          /* size */order[/* size */2],
          /* sleeve */order[/* sleeve */3],
          /* color */order[/* color */4],
          /* pattern */newPattern
        ];
}

function map2(optA, optB, f) {
  if (optA !== undefined && optB !== undefined) {
    return Caml_option.some(Curry._2(f, Caml_option.valFromOption(optA), Caml_option.valFromOption(optB)));
  }
  
}

function createOrder(state) {
  var result = /* record */[
    /* orderNumber */state[/* nextOrderNumber */5],
    /* quantity */0,
    /* size : Medium */1,
    /* sleeve : Long */1,
    /* color : White */0,
    /* pattern : Solid */0
  ];
  var __x = map2(result, toInt(state[/* qtyStr */0]), setQty);
  var __x$1 = map2(__x, Shirt$ReactTemplate.Size[/* fromString */1](state[/* sizeStr */1]), setSize);
  var __x$2 = map2(__x$1, Shirt$ReactTemplate.Sleeve[/* fromString */1](state[/* sleeveStr */2]), setSleeve);
  var __x$3 = map2(__x$2, Shirt$ReactTemplate.Color[/* fromString */1](state[/* colorStr */3]), setColor);
  return map2(__x$3, Shirt$ReactTemplate.Pattern[/* fromString */1](state[/* patternStr */4]), setPattern);
}

var component = ReasonReact.reducerComponent("OrderForm");

function make(_children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var orderItems = Belt_Array.map(self[/* state */1][/* orders */6], (function (order) {
                      var match = self[/* state */1][/* editingNumber */8];
                      var beingEdited = match !== undefined ? match === order[/* orderNumber */0] : false;
                      return ReasonReact.element(String(order[/* orderNumber */0]), undefined, OrderItem$ReactTemplate.make(order, (function (_event) {
                                        return Curry._1(self[/* send */3], /* Delete */Block.__(6, [order]));
                                      }), (function (_event) {
                                        return Curry._1(self[/* send */3], /* Edit */Block.__(7, [order]));
                                      }), beingEdited, /* array */[]));
                    }));
              var orderTable = self[/* state */1][/* orders */6].length !== 0 ? React.createElement("table", undefined, React.createElement("thead", undefined, React.createElement("tr", undefined, React.createElement("th", undefined, "Qty"), React.createElement("th", undefined, "Size"), React.createElement("th", undefined, "Sleeve"), React.createElement("th", undefined, "Color"), React.createElement("th", undefined, "Pattern"), React.createElement("th", undefined, "Action"))), React.createElement("tbody", undefined, orderItems)) : React.createElement("p", undefined, "No orders entered yet.");
              var match = self[/* state */1][/* editingNumber */8] === undefined;
              return React.createElement("div", undefined, React.createElement("p", {
                              className: "flex"
                            }, React.createElement("span", {
                                  className: "item"
                                }, "Qty: ", React.createElement("input", {
                                      size: 4,
                                      type: "text",
                                      value: self[/* state */1][/* qtyStr */0],
                                      onChange: (function ($$event) {
                                          return Curry._1(self[/* send */3], /* ChangeQty */Block.__(1, [$$event.target.value]));
                                        })
                                    })), makeSelect("Size", /* array */[
                                  "XS",
                                  "S",
                                  "M",
                                  "L",
                                  "XL",
                                  "XXL",
                                  "XXXL"
                                ], self[/* state */1][/* sizeStr */1], (function ($$event) {
                                    return Curry._1(self[/* send */3], /* ChangeSize */Block.__(2, [$$event.target.value]));
                                  })), makeSelect("Sleeve", /* array */[
                                  "Short sleeve",
                                  "Long sleeve",
                                  "Extra-long sleeve"
                                ], self[/* state */1][/* sleeveStr */2], (function ($$event) {
                                    return Curry._1(self[/* send */3], /* ChangeSleeve */Block.__(3, [$$event.target.value]));
                                  })), makeSelect("Color", /* array */[
                                  "White",
                                  "Blue",
                                  "Red",
                                  "Green",
                                  "Brown"
                                ], self[/* state */1][/* colorStr */3], (function ($$event) {
                                    return Curry._1(self[/* send */3], /* ChangeColor */Block.__(4, [$$event.target.value]));
                                  })), makeSelect("Pattern", /* array */[
                                  "Solid",
                                  "Pinstripe",
                                  "Checked"
                                ], self[/* state */1][/* patternStr */4], (function ($$event) {
                                    return Curry._1(self[/* send */3], /* ChangePattern */Block.__(5, [$$event.target.value]));
                                  })), React.createElement("span", {
                                  className: "item"
                                }, React.createElement("button", {
                                      onClick: (function (_event) {
                                          var optOrder = createOrder(self[/* state */1]);
                                          if (optOrder !== undefined) {
                                            return Curry._1(self[/* send */3], /* Enter */Block.__(0, [optOrder]));
                                          } else {
                                            return Curry._1(self[/* send */3], /* MissingData */0);
                                          }
                                        })
                                    }, match ? "Add" : "Update"))), React.createElement("p", {
                              id: "errorText"
                            }, self[/* state */1][/* errorText */7]), orderTable);
            }),
          /* initialState */getStoredState,
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                return /* Update */Block.__(0, [/* record */[
                            /* qtyStr */state[/* qtyStr */0],
                            /* sizeStr */state[/* sizeStr */1],
                            /* sleeveStr */state[/* sleeveStr */2],
                            /* colorStr */state[/* colorStr */3],
                            /* patternStr */state[/* patternStr */4],
                            /* nextOrderNumber */state[/* nextOrderNumber */5],
                            /* orders */state[/* orders */6],
                            /* errorText */"Please fill in all fields.",
                            /* editingNumber */state[/* editingNumber */8]
                          ]]);
              } else {
                switch (action.tag | 0) {
                  case 0 : 
                      var order = action[0];
                      var n = Belt_Option.getWithDefault(toInt(state[/* qtyStr */0]), 0);
                      if (n > 0 && n <= 100) {
                        var match = state[/* editingNumber */8];
                        var tmp;
                        if (match !== undefined) {
                          var n$1 = match;
                          tmp = Belt_Array.map(state[/* orders */6], (function (item) {
                                  var match = item[/* orderNumber */0] === n$1;
                                  if (match) {
                                    return order;
                                  } else {
                                    return item;
                                  }
                                }));
                        } else {
                          tmp = Belt_Array.concat(state[/* orders */6], /* array */[order]);
                        }
                        return /* UpdateWithSideEffects */Block.__(2, [
                                  /* record */[
                                    /* qtyStr */"",
                                    /* sizeStr */"",
                                    /* sleeveStr */"",
                                    /* colorStr */"",
                                    /* patternStr */"",
                                    /* nextOrderNumber */state[/* nextOrderNumber */5] + 1 | 0,
                                    /* orders */tmp,
                                    /* errorText */"",
                                    /* editingNumber */undefined
                                  ],
                                  (function (self) {
                                      return storeStateLocally(self[/* state */1]);
                                    })
                                ]);
                      } else {
                        return /* Update */Block.__(0, [/* record */[
                                    /* qtyStr */state[/* qtyStr */0],
                                    /* sizeStr */state[/* sizeStr */1],
                                    /* sleeveStr */state[/* sleeveStr */2],
                                    /* colorStr */state[/* colorStr */3],
                                    /* patternStr */state[/* patternStr */4],
                                    /* nextOrderNumber */state[/* nextOrderNumber */5],
                                    /* orders */state[/* orders */6],
                                    /* errorText */"Quantity must be between 1 and 100.",
                                    /* editingNumber */state[/* editingNumber */8]
                                  ]]);
                      }
                  case 1 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */action[0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ]]);
                  case 2 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */action[0],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ]]);
                  case 3 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */action[0],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ]]);
                  case 4 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */action[0],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ]]);
                  case 5 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */action[0],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ]]);
                  case 6 : 
                      var order$1 = action[0];
                      return /* UpdateWithSideEffects */Block.__(2, [
                                /* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */Belt_Array.keep(state[/* orders */6], (function (item) {
                                          return item[/* orderNumber */0] !== order$1[/* orderNumber */0];
                                        })),
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */state[/* editingNumber */8]
                                ],
                                (function (self) {
                                    return storeStateLocally(self[/* state */1]);
                                  })
                              ]);
                  case 7 : 
                      var order$2 = action[0];
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */String(order$2[/* quantity */1]),
                                  /* sizeStr */Shirt$ReactTemplate.Size[/* toString */0](order$2[/* size */2]),
                                  /* sleeveStr */Shirt$ReactTemplate.Sleeve[/* toString */0](order$2[/* sleeve */3]),
                                  /* colorStr */Shirt$ReactTemplate.Color[/* toString */0](order$2[/* color */4]),
                                  /* patternStr */Shirt$ReactTemplate.Pattern[/* toString */0](order$2[/* pattern */5]),
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */state[/* errorText */7],
                                  /* editingNumber */order$2[/* orderNumber */0]
                                ]]);
                  
                }
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.toInt = toInt;
exports.encodeState = encodeState;
exports.decodeState = decodeState;
exports.localStorageKey = localStorageKey;
exports.storeStateLocally = storeStateLocally;
exports.getStoredState = getStoredState;
exports.makeSelect = makeSelect;
exports.setQty = setQty;
exports.setSize = setSize;
exports.setSleeve = setSleeve;
exports.setColor = setColor;
exports.setPattern = setPattern;
exports.map2 = map2;
exports.createOrder = createOrder;
exports.component = component;
exports.make = make;
/* component Not a pure module */
