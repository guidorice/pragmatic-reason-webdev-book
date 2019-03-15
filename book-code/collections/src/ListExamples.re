/* Cheat for outputting a list */
/* val reduce:  'a t -> 'b -> ('b -> 'a -> 'b) -> 'b */
/* val reduce: items, acc, (acc, item) => acc */
let conversion = (converter: ('a => string), acc: string, item: 'a) => {
  acc ++ converter(item) ++ ", "
};

let stringOfList = (items: list('a), stringify: (('a) => string)): string => {
  let reducerFcn = conversion(stringify);
  Belt.List.reduce(items, "[", reducerFcn) ++ "]";
};

let stringOfOpt = (items: option(list('a)), stringify: (('a) => string)): string => {
  switch (items) {
    | Some(items) => "Some(" ++ stringOfList(items, stringify) ++ ")"
    | None => "None"
  }
};

let items = [10, 11, 12, 13, 14, 15, 16];

Js.log(Belt.List.length(items)); /* 7 */
Js.log(Belt.List.size(items)); /* 7 */

let multiples = Belt.List.make(5, 7.0);
Js.log(multiples);

let sqrtPlusOne = (x) => { sqrt(float_of_int(x) +. 1.0) };
let roots = Belt.List.makeBy(5, sqrtPlusOne);
Js.log(stringOfList(roots, string_of_float));

let added1 = Belt.List.add(items, 9);
let added2 = [9, ...items];
Js.log(stringOfList(added2, string_of_int));

let more = [17, 18, 19];
let joined = Belt.List.concat(items, more);
Js.log(stringOfList(joined, string_of_int));

let taken3 = Belt.List.take(items, 3); /* Some([10, 11, 12]) */
let dropped3 = Belt.List.drop(items, 3); /* Some([13, 14, 15, 16]) */
let badTake = Belt.List.take(items, 10); /* None */
Js.log(stringOfOpt(taken3, string_of_int));
Js.log(stringOfOpt(dropped3, string_of_int));
Js.log(stringOfOpt(badTake, string_of_int));

let result = Belt.List.splitAt(items, 3);
switch (result) {
  | Some((firstPart, lastPart)) => {
      Js.log(firstPart); /* [10, 11, 12] */
      Js.log(lastPart); /* [13, 14, 15, 16] */
    }
  | None => Js.log("None")
};


let optElement = Belt.List.get(items, 3); /* Some(13) */
let badOptElement = Belt.List.get(items, 10); /* None */
let element = Belt.List.getExn(items, 3); /* 13 */
Js.log(optElement);
Js.log(badOptElement);
Js.log(element);
let badElement: int =
  try (Belt.List.getExn(items, 10)) {
  | Js.Exn.Error(e) =>
    switch (Js.Exn.message(e)) {
    | Some(message) => Js.log({j|Error: $message|j}) /* "Error: getExn"*/
    | None => Js.log("An unknown error occurred")
    };
    (-1);
  };
Js.log(badElement);


