/**
Back in the code on page 40 we had to rewrite the price() function to accept
and return option values.
Change it back to an ordinary function and rewrite the code for displayPrice() (
see the code on page 41) using Belt.Option.map() to handle the option manipulation.
 */

type shirtSize =
  | Small
  | Medium
  | Large
  | XLarge(int);

let price = size =>
  switch (size) {
  | Small => 11.00
  | Medium => 12.50
  | Large => 14.00
  | XLarge(n) => 16.00 +. float_of_int(n - 1) *. 0.5
  };

let shirtSizeOfString = (str: string): option(shirtSize) =>
  switch (str) {
  | "S" => Some(Small)
  | "M" => Some(Medium)
  | "L" => Some(Large)
  | "XL" => Some(XLarge(1))
  | "XXL" => Some(XLarge(2))
  | "XXXL" => Some(XLarge(3))
  | "XXXXL" => Some(XLarge(4))
  | _ => None
  };

let toFixed = Js.Float.toFixedWithPrecision;
let displayPrice = (input: string): unit => {
  let size = shirtSizeOfString(input);
  let amount = Belt.Option.map(size, price);
  let text =
    switch (amount) {
    | Some(cost) =>
      let costStr = toFixed(cost, ~digits=2);
      {j|Your $input shirt costs \$$costStr.|j};
    | None => {j|Cannot determine price for $input|j}
    };
  Js.log(text);
};

displayPrice("XXL"); /* output: Your XXL shirt costs $16.50. */
displayPrice("foobar"); /* output: Your XXL shirt costs $16.50. */