// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';


var random1 = Math.random();

console.log(random1);

function random2(prim) {
  return Math.random();
}

console.log(random2);

function debugInt(varName, value) {
  console.log(varName + (" is: " + String(value)));
  return /* () */0;
}

function separator(param) {
  console.log("---------------");
  return /* () */0;
}

function doNothing(param) {
  return /* () */0;
}

exports.random1 = random1;
exports.random2 = random2;
exports.debugInt = debugInt;
exports.separator = separator;
exports.doNothing = doNothing;
/* random1 Not a pure module */