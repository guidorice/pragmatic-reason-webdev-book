/*
 Write a program that calculates wind chill. Given an air temperature T in
 degrees Celsius and a wind velocity V in kilometers per hour,
 the formula is: 13.12+(0.6215·T)−(11.37·V^0.16)+(0.3965·T·V^0.16). Make sure you
 label your output properly. For example:
 At temperature 5 degrees C and wind speed 20 km/hr,
 the wind chill temperature is 1.0669572525115663.
 */

type temperature = float; // degrees celcius
type velocity = float; // km/h

let pow = Js.Math.pow_float;

let windchill = (~temperature as t, ~velocity as v) => {
  13.12
  +. 0.6215
  *. t
  -. 11.37
  *. pow(~base=v, ~exp=0.16)
  +. 0.3965
  *. t
  *. pow(~base=v, ~exp=0.16);
};

/** bs compiles exponent operator ** to Math.pow in either case! */
let windchill2 = (~temperature as t, ~velocity as v) => {
  13.12 +. 0.6215 *. t -. 11.37 *. v ** 0.16 +. 0.3965 *. t *. v ** 0.16;
};

let result = windchill(~temperature=5.0, ~velocity=20.0);
Js.log("the windchill temperature is " ++ string_of_float(result));
let result = windchill2(~temperature=5.0, ~velocity=20.0);
Js.log("the windchill(2) temperature is " ++ string_of_float(result));