/*
 * Given air temperature T in degrees celsius and wind velocity
 * V in km/hr, calculate wind chill
 */

let t = 5.0;
let v = 20.0;
let vPower = v ** 0.16;
let result = 13.12 +. (0.6215 *. t) -. (11.37 *. vPower) +.
  (0.3965 *. t *. vPower);

Js.log({j|At temperature $t° Celsius and wind speed $v km/hr,
the wind chill temperature is $result° Celsius.|j});
