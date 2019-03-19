// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var Shirt$ReactTemplate = require("./Shirt.bs.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var OrderItem$ReactTemplate = require("./OrderItem.bs.js");

function convertWithDefault(str, defaultValue, convert) {
  return Belt_Option.getWithDefault(Curry._1(convert, str), defaultValue);
}

function toIntWithDefault(s, defaultValue) {
  try {
    return Caml_format.caml_int_of_string(s);
  }
  catch (raw_exn){
    var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
    if (exn[0] === Caml_builtin_exceptions.failure) {
      if (exn[1] === "int_of_string") {
        return defaultValue;
      } else {
        throw exn;
      }
    } else {
      throw exn;
    }
  }
}

function makeSelect(label, choices, value, changeFcn) {
  var makeOptionElement = function (value) {
    return React.createElement("option", {
                key: value,
                value: value
              }, value);
  };
  var menuOptionElements = Belt_Array.map(choices, makeOptionElement);
  return React.createElement("span", {
              className: "item"
            }, React.createElement("label", undefined, " " + (label + ": ")), React.createElement("select", {
                  value: value,
                  onChange: changeFcn
                }, menuOptionElements));
}

function createOrder(state) {
  return /* record */[
          /* orderNumber */state[/* nextOrderNumber */5],
          /* quantity */toIntWithDefault(state[/* qtyStr */0], 0),
          /* size */Belt_Option.getWithDefault(Shirt$ReactTemplate.Size[/* fromString */1](state[/* sizeStr */1]), /* Medium */1),
          /* sleeve */Belt_Option.getWithDefault(Shirt$ReactTemplate.Sleeve[/* fromString */1](state[/* sleeveStr */2]), /* Long */1),
          /* color */Belt_Option.getWithDefault(Shirt$ReactTemplate.Color[/* fromString */1](state[/* colorStr */3]), /* White */0),
          /* pattern */Belt_Option.getWithDefault(Shirt$ReactTemplate.Pattern[/* fromString */1](state[/* patternStr */4]), /* Solid */0)
        ];
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
                      return ReasonReact.element(String(order[/* orderNumber */0]), undefined, OrderItem$ReactTemplate.make(order, (function (_event) {
                                        return Curry._1(self[/* send */3], /* Delete */Block.__(6, [order]));
                                      }), /* array */[]));
                    }));
              var orderTable = self[/* state */1][/* orders */6].length !== 0 ? React.createElement("table", undefined, React.createElement("thead", undefined, React.createElement("tr", undefined, React.createElement("th", undefined, "Qty"), React.createElement("th", undefined, "Size"), React.createElement("th", undefined, "Sleeve"), React.createElement("th", undefined, "Color"), React.createElement("th", undefined, "Pattern"), React.createElement("th", undefined, "Action"))), React.createElement("tbody", undefined, orderItems)) : React.createElement("p", undefined, "No orders entered yet.");
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
                                          var order = createOrder(self[/* state */1]);
                                          return Curry._1(self[/* send */3], /* Enter */Block.__(0, [order]));
                                        })
                                    }, "Add"))), React.createElement("p", {
                              id: "errorText"
                            }, self[/* state */1][/* errorText */7]), orderTable);
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* qtyStr */"1",
                      /* sizeStr */Shirt$ReactTemplate.Size[/* toString */0](/* Medium */1),
                      /* sleeveStr */Shirt$ReactTemplate.Sleeve[/* toString */0](/* Long */1),
                      /* colorStr */Shirt$ReactTemplate.Color[/* toString */0](/* White */0),
                      /* patternStr */Shirt$ReactTemplate.Pattern[/* toString */0](/* Solid */0),
                      /* nextOrderNumber */1,
                      /* orders : array */[],
                      /* errorText */""
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action.tag | 0) {
                case 0 : 
                    var n = toIntWithDefault(state[/* qtyStr */0], 0);
                    if (n > 0 && n <= 100) {
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5] + 1 | 0,
                                  /* orders */Belt_Array.concat(state[/* orders */6], /* array */[action[0]]),
                                  /* errorText */""
                                ]]);
                    } else {
                      return /* Update */Block.__(0, [/* record */[
                                  /* qtyStr */state[/* qtyStr */0],
                                  /* sizeStr */state[/* sizeStr */1],
                                  /* sleeveStr */state[/* sleeveStr */2],
                                  /* colorStr */state[/* colorStr */3],
                                  /* patternStr */state[/* patternStr */4],
                                  /* nextOrderNumber */state[/* nextOrderNumber */5],
                                  /* orders */state[/* orders */6],
                                  /* errorText */"Quantity must be between 1 and 100."
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
                                /* errorText */state[/* errorText */7]
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
                                /* errorText */state[/* errorText */7]
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
                                /* errorText */state[/* errorText */7]
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
                                /* errorText */state[/* errorText */7]
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
                                /* errorText */state[/* errorText */7]
                              ]]);
                case 6 : 
                    var order = action[0];
                    return /* Update */Block.__(0, [/* record */[
                                /* qtyStr */state[/* qtyStr */0],
                                /* sizeStr */state[/* sizeStr */1],
                                /* sleeveStr */state[/* sleeveStr */2],
                                /* colorStr */state[/* colorStr */3],
                                /* patternStr */state[/* patternStr */4],
                                /* nextOrderNumber */state[/* nextOrderNumber */5],
                                /* orders */Belt_Array.keep(state[/* orders */6], (function (item) {
                                        return item[/* orderNumber */0] !== order[/* orderNumber */0];
                                      })),
                                /* errorText */state[/* errorText */7]
                              ]]);
                
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.convertWithDefault = convertWithDefault;
exports.toIntWithDefault = toIntWithDefault;
exports.makeSelect = makeSelect;
exports.createOrder = createOrder;
exports.component = component;
exports.make = make;
/* component Not a pure module */