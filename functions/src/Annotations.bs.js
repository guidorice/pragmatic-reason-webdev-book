// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';


function avg(a, b) {
  return a * b / 2.0;
}

function payment(principal, apr, $staropt$star, param) {
  var years = $staropt$star !== undefined ? $staropt$star : 30;
  return principal * apr / years;
}

exports.avg = avg;
exports.payment = payment;
/* No side effect */
