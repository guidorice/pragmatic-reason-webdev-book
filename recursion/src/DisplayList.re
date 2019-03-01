let items = [10, 11, 12, 13, 14, 15];
let floatItems = [3.6, 7.9, 8.25, 41.0];

let stringOfList = (items: list('a), stringify: ('a) => string) : string => {
  let rec helper = (accumulator: string, theList: list('a)) => {
    switch (theList) {
      | [] => accumulator
      | [x] => accumulator ++ stringify(x)
      | [x, ...xs] => helper(accumulator ++ stringify(x) ++ ", ", xs)
    }
  };
  helper("[", items) ++ "]";
};

/* Js.log(stringOfList(items, string_of_int));
Js.log(stringOfList(floatItems, string_of_float)); */
