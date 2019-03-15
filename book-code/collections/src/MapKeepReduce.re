let conversion = (converter: ('a => string), acc: string, item: 'a) => {
  acc ++ converter(item) ++ ", "
};

let stringOfList = (items: list('a), stringify: (('a) => string)): string => {
  let reducerFcn = conversion(stringify);
  Belt.List.reduce(items, "[", reducerFcn) ++ "]";
}

let orderList = [(7, ShirtSize.Medium), (5, ShirtSize.XLarge(3)),
  (4, ShirtSize.Small), (6, ShirtSize.Large), (8, ShirtSize.Small),
  (2, ShirtSize.Large), (9, ShirtSize.Medium), (3, ShirtSize.XLarge(2))];

let onePrice = ((qty: int, size: ShirtSize.t)) : float => {
  float_of_int(qty) *. ShirtSize.price(size);
};

let priceList = Belt.List.map(orderList, onePrice);
Js.log(stringOfList(priceList, string_of_float));

let isMedium = ((_, size)): bool => {
  size === ShirtSize.Medium;
};

let mediums = Belt.List.keep(orderList, isMedium);

/* Using an anonymous function with keep() */
let mediums2 = Belt.List.keep(orderList,
  ((_, size)) => size === ShirtSize.Medium);

Js.log(stringOfList(mediums, Order.toString));
Js.log(stringOfList(mediums2, Order.toString));  

let addPriceLogged = (runningTotal, orderItem) => {
  let price = onePrice(orderItem);
  Js.log({j|$runningTotal, $price|j});
  runningTotal +. price;
};

Js.log("Running total / Price")
let totalPrice = Belt.List.reduce(orderList, 0.0, addPriceLogged);
Js.log2("Total price:", totalPrice); /* Total price: 578.5 */

let addPrice = (runningTotal, orderItem) => {
  runningTotal +. onePrice(orderItem);
};

let totalPrice = Belt.List.reduce(orderList, 0.0, addPrice);

let addPriceToTotal = (runningTotal, price) => runningTotal +. price;

let totalPrice2 =
  Belt.List.map(orderList, onePrice) ->
  Belt.List.reduce(_, 0.0, addPriceToTotal);
Js.log2("Total price:", totalPrice2); /* Total price: 578.5 */

let totalPrice3 =
  Belt.List.map(orderList, onePrice) ->
  Belt.List.reduce(_, 0.0, (+.));
Js.log2("Total price:", totalPrice3); /* Total price: 578.5 */

let mediumTotal =
  Belt.List.keep(orderList, isMedium) ->
  Belt.List.map(_, onePrice) ->
  Belt.List.reduce(_, 0.0, addPriceToTotal);
Js.log2("Medium total:", mediumTotal); /* Medium total: 200*/
