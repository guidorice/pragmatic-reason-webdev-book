/**
Write a function named discount() that calculates discount prices. It should
have two named parameters (choose any names you like):
• The original price, which is float
• The discount percent, which is also float
If the original price is, say, $30.00 and the discount percent is 5%, the amount
saved is $1.50 (5% of $30.00), making the result $28.50.
Then, use currying to create functions named halfOff() which uses 50 as the
value for the percent, and tenPercentOff(), which uses 10 as the value for the
percent. Write complete type annotations on all your functions. Make sure you
write code that uses these functions and displays the results so you can be
sure it works!
 */;

let discount = (~original: float, ~percent: float) =>
  original *. (1. -. percent /. 100.);

let halfOff = discount(~percent=50.);

let tenPercentOff = discount(~percent=10.);

let fmt = Js.Float.toFixedWithPrecision(~digits=2);

let result = fmt(discount(~original=100., ~percent=5.));
Js.log({j|discount of 5% off \$100 is \$$result|j});
let result = fmt(halfOff(~original=65.));
Js.log({j|half off \$65 is \$$result|j});
let result = fmt(tenPercentOff(~original=7.99));
Js.log({j|ten percent off \$7.99 is \$$result|j});