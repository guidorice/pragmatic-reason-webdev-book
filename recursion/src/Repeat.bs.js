// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';


function repeatRec(s, _accumulator, _n) {
  while(true) {
    var n = _n;
    var accumulator = _accumulator;
    if (n !== 0) {
      _n = n - 1 | 0;
      _accumulator = accumulator + s;
      continue ;
    } else {
      return accumulator;
    }
  };
}

function repeatRec2(s, n) {
  if (n !== 0) {
    return s + repeatRec2(s, n - 1 | 0);
  } else {
    return "";
  }
}

console.log(repeatRec("go", "", 3));

console.log(repeatRec2("go", 3));

exports.repeatRec = repeatRec;
exports.repeatRec2 = repeatRec2;
/*  Not a pure module */
