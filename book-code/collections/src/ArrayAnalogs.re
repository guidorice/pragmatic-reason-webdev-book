/* Write functions analogous to take, drop, and splitAt in the Belt.List library */

let arrayTake = (arr: array('a), n: int) : array('a) => {
  Belt.Array.slice(arr, ~offset=0, ~len=n)
};

let arrayDrop = (arr: array('a), n: int) : array('a) => {
  Belt.Array.slice(arr, ~offset=n, ~len=Belt.Array.length(arr) - n)
};

let arraySplitAt = (arr: array('a), n: int) : (array('a), array('a)) => {
  (arrayTake(arr, n), arrayDrop(arr, n));
};

/* now test the functions */
let items = [|10, 11, 12, 13, 14, 15, 16|];
Js.log(arrayTake(items, 3));
Js.log(arrayDrop(items, 3));
Js.log(arraySplitAt(items, 3));
