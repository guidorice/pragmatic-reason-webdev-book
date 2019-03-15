
let orderArray = [| (7, ShirtSize.Medium), (5, ShirtSize.XLarge(3)),
  (4, ShirtSize.Small), (6, ShirtSize.Large), (8, ShirtSize.Small),
  (2, ShirtSize.Large), (9, ShirtSize.Medium), (3, ShirtSize.XLarge(2))|];

/* This function calculates the price for a single order */
let onePrice = ((qty: int, size: ShirtSize.shirtSize)) : float => {
  float_of_int(qty) *. ShirtSize.price(size);
};

let priceArray = Belt.Array.map(orderArray, onePrice);
Js.log(priceArray);

/* ================================= */

/* Example of keep() */
let isMedium = ((_, size)): bool => {
  size === ShirtSize.Medium;
};
let mediums = Belt.Array.keep(orderArray, isMedium);

/* Using an anonymous function with keep() */
let mediums2 = Belt.Array.keep(orderArray,
  ((_, size)) => size === ShirtSize.Medium);

/* ================================= */

/* reduce() with a named reducer function */
let addPrice = (runningTotal, orderItem) => {
  runningTotal +. onePrice(orderItem);
};

let totalPrice = Belt.Array.reduce(orderArray, 0.0, addPrice);
Js.log2("Total price:", totalPrice); /* Total price: 578.5 */

/* reduce() with an anonymous reducer function */
let totalPrice2 =
  Belt.Array.map(orderArray, onePrice) ->
  Belt.Array.reduce(_, 0.0, (runningTotal, item) => runningTotal +. item);
Js.log2("Total price:", totalPrice2); /* Total price: 578.5 */

/* ================================= */

/* combining keep(), map(), and reduce() */
let mediumTotal =
  Belt.Array.keep(orderArray, isMedium) ->
  Belt.Array.map(_, onePrice) ->
  Belt.Array.reduce(_, 0.0, (runningTotal, item) => runningTotal +. item);
Js.log2("Medium total:", mediumTotal); /* Medium total: 200*/
