let avg = (a, b) => (a +. b) /. 2.0;

let amount = 42.99;
Js.log2(
  "Amount per month: $",
  Js.Float.toFixedWithPrecision(amount, ~digits=2),
);