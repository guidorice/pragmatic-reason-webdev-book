/* hide jsDateParse because it's an implementation detail */

type t;
let createDate: (unit) => t;
let now: (unit) => float;
let toString: (t) => string;
let getFullYear: (t) => float;
let parse: (string) => option(float);
