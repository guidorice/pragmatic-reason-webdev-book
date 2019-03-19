// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

require("../images/bird.png");

require("../images/cat.png");

require("../images/dog.png");

require("../images/fish.png");

require("../images/unknown.png");

var component = ReasonReact.statelessComponent("Animal");

var animalSectionStyle = {
  display: "inline-block",
  textAlign: "center"
};

function picture(species) {
  switch (species) {
    case "bird" : 
        return "bird.png";
    case "cat" : 
        return "cat.png";
    case "dog" : 
        return "dog.png";
    case "fish" : 
        return "fish.png";
    default:
      return "unknown.png";
  }
}

function make(species, name, _children) {
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
                          style: animalSectionStyle
                        }, React.createElement("img", {
                              src: "images/" + picture(species)
                            }), React.createElement("span", undefined, React.createElement("br", undefined)), name);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.animalSectionStyle = animalSectionStyle;
exports.picture = picture;
exports.make = make;
/*  Not a pure module */