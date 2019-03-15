type scoreType = int;
type percentType = float;

type userId = int;

/* Explicitly annotate this type to make a point */
let person: userId = 60; 

let calcPercent = (score: scoreType, max: scoreType) : percentType =>
  float_of_int(score) /. float_of_int(max) *. 100.0;
  
let result = calcPercent(person, 75);
Js.log({j|Bogus result is $result|j}); /* output: Bogus result is 80 */


