// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function keepIndices(arr, _position, _accumulator, f) {
  while(true) {
    var accumulator = _accumulator;
    var position = _position;
    if (position < arr.length) {
      var match = Curry._1(f, arr[position]);
      if (match) {
        _accumulator = Belt_Array.concat(accumulator, /* array */[position]);
        _position = position + 1 | 0;
        continue ;
      } else {
        _position = position + 1 | 0;
        continue ;
      }
    } else {
      return accumulator;
    }
  };
}

var words = /* array */[
  "cow",
  "aardvark",
  "squirrel",
  "fish",
  "snake",
  "capybara"
];

function isShortWord(s) {
  return s.length < 6;
}

var result = keepIndices(words, 0, /* array */[], isShortWord);

console.log(result);

exports.keepIndices = keepIndices;
exports.words = words;
exports.isShortWord = isShortWord;
exports.result = result;
/* result Not a pure module */
