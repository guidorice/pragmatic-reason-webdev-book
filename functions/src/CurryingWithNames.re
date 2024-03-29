open DefaultParams;

let usPayment = payment(~years=30);
let ukPayment = payment(~years=25);
let dePayment = payment(~years=20);
let toFixed = Js.Float.toFixedWithPrecision;
Js.log("Loan of 10000 at 5%");
Js.log2(
  {js|US: $|js},
  toFixed(usPayment(~principal=10000.0, ~apr=5.0, ()), ~digits=2),
);
Js.log2(
  {js|UK: £|js},
  toFixed(ukPayment(~principal=10000.0, ~apr=5.0, ()), ~digits=2),
);
Js.log2(
  {js|DE: €|js},
  toFixed(dePayment(~principal=10000.0, ~apr=5.0, ()), ~digits=2),
);