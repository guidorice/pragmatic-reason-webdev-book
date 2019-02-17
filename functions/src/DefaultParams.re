let payment = (~principal, ~apr, ~years=30, ()) => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
};

let amount = payment(~principal=10000.0, ~apr=5.0, ());
Js.log2(
  "Amount per month for loan 1: $",
  Js.Float.toFixedWithPrecision(amount, ~digits=2),
);
let amount2 = payment(~apr=7.5, ~years=15, ~principal=25000.0, ());
Js.log2(
  "Amount per month for loan 2: $",
  Js.Float.toFixedWithPrecision(amount2, ~digits=2),
);