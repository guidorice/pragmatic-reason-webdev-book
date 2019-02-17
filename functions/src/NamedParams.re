let payment = (~principal, ~apr, ~years) => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
};

/* warning re: labels omitted,
 * let amount = payment(10000.0, 5.0, 30);
 * Js.log(amount);
 */

let amount = payment(~principal=10000.0, ~apr=5.0, ~years=30);
Js.log2(
  "Amount per month for loan 1: $",
  Js_float.toFixedWithPrecision(amount, ~digits=2),
);
let amount2 = payment(~apr=7.5, ~years=15, ~principal=25000.0);
Js.log2(
  "Amount per month for loan 2: $",
  Js_float.toFixedWithPrecision(amount2, ~digits=2),
);

let payment = (~principal as p, ~apr, ~years) => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  p *. (r *. powerTerm) /. (powerTerm -. 1.0); /* using p here */
};