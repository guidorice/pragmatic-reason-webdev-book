// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Pervasives = require("bs-platform/lib/js/pervasives.js");

var discount = 0.05;

var total = 7 * 14.50;

var afterDiscount = total * (1.0 - discount);

console.log("Prix avant re\xcc\x81duction: " + (Pervasives.string_of_float(total) + " \xe2\x82\xac"));

console.log("Prix apre\xcc\x80s re\xcc\x81duction: " + (Pervasives.string_of_float(afterDiscount) + " \xe2\x82\xac"));

var qty = 7;

var price = 14.50;

exports.qty = qty;
exports.price = price;
exports.discount = discount;
exports.total = total;
exports.afterDiscount = afterDiscount;
/*  Not a pure module */
