let avg = (a: float, b: float) : float => {
  (a +. b) /. 2.0;
};

let payment = (~principal: float, ~apr: float,
               ~years: int=30, ():unit) : float=> {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
};

let toFixed = Js.Float.toFixedWithPrecision;

let amount = payment(~principal=10000.0, ~apr=5.0, ~years=30, ());
Js.log2("Amount per month for loan 1: $", toFixed(amount, ~digits=2));

let amount2 = payment(~apr=7.5, ~years=15, ~principal=25000.0, ());
Js.log2("Amount per month for loan 2: $", toFixed(amount2, ~digits=2));
