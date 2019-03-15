let data = [2, 6, 42, 5, 7, 20, 3];

let isEven = (n) => { n mod 2 == 0 };

let takeWhile = (items: list('a), f: ('a) => bool) : list('a) => {
  let rec takeHelper = (items: list('a), acc: list('a)) : list('a) => {
    switch (items) {
      | [] => Belt.List.reverse(acc)
      | [x, ...xs] => {
          f(x) ? takeHelper(xs, [x, ...acc]) : Belt.List.reverse(acc);
        }
    };
  };
  takeHelper(items, []);
};

let dropWhile = (items: list('a), f: ('a) => bool) : list('a) => {
  let rec dropHelper = (items: list('a)) : list('a) => {
    switch (items) {
      | [] => []
      | [x, ...xs] => 
          f(x) ? dropHelper(xs) : items;
    };
  };
  dropHelper(items);
};


let takeResult = takeWhile(data, isEven);
let dropResult = dropWhile(data, isEven);
Js.log(takeResult);
Js.log(dropResult);

