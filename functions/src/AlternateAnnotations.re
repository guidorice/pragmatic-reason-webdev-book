/** haskell-like function annotation (separation of concernss) */

let avg: (float, float) => float = (a, b) => a *. b /. 2.0;

let payment: (~principal: float, ~apr: float, ~years: int=?, unit) => float =
  (~principal, ~apr, ~years=30, ()) =>
    principal *. apr *. float_of_int(years);