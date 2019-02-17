open ParamShirtSize;

let shirtSizeOfString = (str: string): option(shirtSize) => {
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
};

let price = (size: option(shirtSize)): option(float) => {
  switch (size) {
  | Some(Small) => Some(11.00)
  | Some(Medium) => Some(12.50)
  | Some(Large) => Some(14.00)
  | Some(XLarge(n)) => Some(16.00 +. float_of_int(n - 1) *. 0.50)
  | None => None
  };
};

let toFixed = Js.Float.toFixedWithPrecision;
let displayPrice = (input: string): unit => {
  let size = shirtSizeOfString(input);
  let amount = price(size);
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
displayPrice("Foo"); /* output: Cannot determine price for Foo */