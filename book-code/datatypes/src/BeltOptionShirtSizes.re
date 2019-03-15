type shirtSize =
  | Small
  | Medium
  | Large
  | XLarge(int);

let price = (size: shirtSize) : float => {
  switch (size) {
    | Small => 11.00
    | Medium => 12.50
    | Large => 14.00
    | XLarge(n) => 16.00 +. (float_of_int(n - 1) *. 0.50)
  }
};

let stringOfShirtSize = (size: shirtSize) : string => {
  switch (size) {
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => String.make(n, 'X') ++ "L"
  }
};

let shirtSizeOfString = (str: string) : option(shirtSize) => {
  switch (str) {
    | "S" => Some(Small)
    | "M" => Some(Medium)
    | "L" => Some(Large)
    | "XL" => Some(XLarge(1))
    | "XXL" => Some(XLarge(2))
    | "XXXL" => Some(XLarge(3))
    | "XXXXL" => Some(XLarge(4))
    | _ => None
  }
};

let round = x => int_of_float(x +. 0.5);

let toFixed = Js.Float.toFixedWithPrecision

let displayPrice = (input: string) : unit => {
  let size = shirtSizeOfString(input);
  let amount = Belt.Option.map(size, price);
  switch (amount) {
    | Some(cost) => {
        let costStr = toFixed(cost, ~digits=2);
        Js.log({j|Your $input shirt costs \$$costStr.|j});
      }
    | None => Js.log({j|Cannot determine price for $input|j})
  };
};

displayPrice("XXL"); /* output: Your XXL shirt costs $16.50. */
