// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';


function parse(s) {
  var result = Date.parse(s);
  if (isNaN(result)) {
    return undefined;
  } else {
    return result;
  }
}

function createDate(prim) {
  return new Date();
}

function now(prim) {
  return Date.now();
}

function toString(prim) {
  return prim.toString();
}

function getFullYear(prim) {
  return prim.getFullYear();
}

exports.createDate = createDate;
exports.now = now;
exports.toString = toString;
exports.getFullYear = getFullYear;
exports.parse = parse;
/* No side effect */
