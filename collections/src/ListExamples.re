let items = [10, 11, 12, 13, 14, 15, 16];

let sqrtPlusOne = x => sqrt(float_of_int(x) +. 1.0);
let roots = Belt.List.makeBy(5, sqrtPlusOne);
Js.log(roots);

let added1 = Belt.List.add(items, 9);
let added2 = [9, ...items];

let more = [17, 18, 19];
let joined = Belt.List.concat(items, more);

let taken3 = Belt.List.take(items, 3); /* Some([10, 11, 12]) */
let dropped3 = Belt.List.drop(items, 3); /* Some([13, 14, 15, 16]) */
let badTake = Belt.List.take(items, 10); /* None */

let result = Belt.List.splitAt(items, 3);
switch (result) {
| Some((firstPart, lastPart)) =>
  Js.log(firstPart); /* [10, 11, 12] */
  Js.log(lastPart); /* [13, 14, 15, 16] */
| None => Js.log("None")
};

let optElement = Belt.List.get(items, 3); /* Some(13) */
let badOptElement = Belt.List.get(items, 10); /* None */
let element = Belt.List.getExn(items, 3); /* 13 */
let badElement: int =
  try (Belt.List.getExn(items, 50)) {
  | Js.Exn.Error(e) =>
    switch (Js.Exn.message(e)) {
    | Some(message) => Js.log({j|Error: $message|j}) /* "Error: getExn"*/
    | None => Js.log("An unknown error occurred")
    };
    (-1);
  };
Js.log(badElement);