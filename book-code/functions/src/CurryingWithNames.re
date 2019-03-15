let payment = (~principal: float, ~apr: float, ~years:int) : float => {
  let r = apr /. 12.0 /. 100.0;
  let n = float_of_int(years * 12);
  let powerTerm = (1.0 +. r) ** n;
  principal *. (r *. powerTerm) /. (powerTerm -. 1.0);
};


let usPayment = payment(~years=30);
let ukPayment = payment(~years=25);
let dePayment = payment(~years=20);

let toFixed = Js.Float.toFixedWithPrecision;

Js.log("Loan of 10000 at 5%");
Js.log2({js|US: $|js},
        toFixed(usPayment(~principal=10000.0, ~apr=5.0), ~digits=2));
Js.log2({js|UK: £|js},
        toFixed(ukPayment(~principal=10000.0, ~apr=5.0), ~digits=2));
Js.log2({js|DE: €|js},
        toFixed(dePayment(~principal=10000.0, ~apr=5.0), ~digits=2));
