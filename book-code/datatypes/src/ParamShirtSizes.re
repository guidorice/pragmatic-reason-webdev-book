type shirtSize =
  | Small
  | Medium
  | Large
  | XLarge(int);

let mySize: shirtSize = Medium;
let bigSize = XLarge(1);
let veryBigSize = XLarge(3);


let price = (size: shirtSize) : float => {
  switch (size) {
    | Small => 11.00
    | Medium => 12.50
    | Large => 14.00
    | XLarge(n) => 16.00 +. 
        (float_of_int(n - 1) *. 0.50) 
  }
};

Js.log(price(mySize)); /* output: 12.5 */
Js.log(price(bigSize)); /* output: 16 */
Js.log(price(veryBigSize)); /* output: 17 */

let stringOfShirtSize = (size: shirtSize) : string => {
  switch (size) {
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => String.make(n, 'X') ++ "L"
  };
};

Js.log(stringOfShirtSize(veryBigSize)); /* output: XXXL */

let shirtSizeOfString = (str: string) : shirtSize => {
  switch (str) {
    | "S" => Small
    | "M" => Medium
    | "L" => Large
    | "XL" => XLarge(1)
    | "XXL" => XLarge(2)
    | "XXXL" => XLarge(3)
    | "XXXXL" => XLarge(4)
    | _ => Medium
  }
};

