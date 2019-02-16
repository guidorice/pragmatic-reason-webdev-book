open DiscountPrice;

let total = float_of_int(qty) *. price;
let afterDiscount = total *. (1.0 -. discount);
Js.log("Price before discount: $" ++ string_of_float(total) ++ ".");
Js.log("Price after discount: $" ++ string_of_float(afterDiscount) ++ ".");