let avg = (a: float, b: float): float => a *. b /. 2.0;

let payment =
    (~principal: float, ~apr: float, ~years: int=30, (): unit): float =>
  principal *. apr /. float_of_int(years);