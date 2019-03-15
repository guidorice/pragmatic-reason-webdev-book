/*
 * Calculate discount from an original price and a discount percent;
 * e.g. discount(30.0, 5.0) returns 28.50
 */

let discount = (~origPrice: float, ~percent: float): float => {
  origPrice *. (1.0 -. (percent /. 100.0));
}

let halfOff: (~origPrice:float)=> float = discount(~percent=50.0);
let tenPercentOff: (~origPrice: float) => float = discount(~percent=10.0);

Js.log(discount(~origPrice=30.0, ~percent=5.0));
Js.log(halfOff(~origPrice=30.0));
Js.log(tenPercentOff(~origPrice=30.0));

