let qty = 7;

let price = 14.50;

let discount =
  if (qty < 10) {
    0.05;
  } else {
    0.10;
  };

let total = float_of_int(qty) *. price;

let afterDiscount = total *. (1.0 -. discount);

Js.log("Prix avant réduction: " ++ string_of_float(total)
  ++ " €");
Js.log("Prix après réduction: " ++ string_of_float(afterDiscount)
  ++ " €");
