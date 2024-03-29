// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

require("../notice_icons/warning.svg");

require("../notice_icons/error.svg");

require("../notice_icons/information.svg");

var component = ReasonReact.statelessComponent("Notice");

function noticeStyle(color) {
  return {
          border: "1px solid black",
          clear: "left",
          color: color,
          display: "flex",
          marginBottom: "0.5em",
          minHeight: "64px",
          width: "30%",
          alignItems: "center"
        };
}

function make(message, color, icon, _children) {
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
          /* render */(function (_self) {
              return React.createElement("div", {
                          style: noticeStyle(color)
                        }, React.createElement("img", {
                              style: {
                                float: "left",
                                width: "48px"
                              },
                              src: "notice_icons/" + (icon + ".svg")
                            }), message);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.noticeStyle = noticeStyle;
exports.make = make;
/*  Not a pure module */
