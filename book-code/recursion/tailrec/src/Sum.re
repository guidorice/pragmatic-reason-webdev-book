let sum1 = (items: list(int)) : int => {
  let rec helper = (items: list(int), total:int) : int => {
    switch (items) {
      | [] => total
      | [x, ...xs] => helper(xs, total + x)
    }
  };
  helper(items, 0);
};

let rec sum2 = (items: list(int)) : int => {
  switch (items) {
    | [] => 0
    | [x, ...xs] => x + sum2(xs)
  }
};
let items = [1, 3, 7, 20];
let s1 = sum1(items);
let s2 = sum2(items);
Js.log2("Sum 1=", s1);
Js.log2("Sum 2=", s2);
