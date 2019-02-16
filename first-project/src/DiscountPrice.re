let qty = 10;
let price = 14.50;
let discount = qty < 10 ? 0.05 : 0.10;

let total = float_of_int(qty) *. price;
let afterDiscount = total *. (1.0 -. discount);
Js.log2("Price before discount: $", total);
Js.log2("Price after discount: $", afterDiscount);