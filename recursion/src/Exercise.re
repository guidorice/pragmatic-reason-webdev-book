/**
The Belt.List module has two functions: take(), which gives you the first n elements
of a list, and drop(), which gives you everything except the first n elements
of a list.
Your task is to use recursion to write two new functions, takeWhile() and drop-
While(). Instead of taking a parameter n, the parameter is a predicate function
returning true or false when given an item from the list. takeWhile() gives the first
elements of the list that satisfy the predicate, stopping when it encounters
an element that doesn’t fit. dropWhile() returns everything except the first elements
of the list that satisfy the predicate. Here is an example:
let data = [2, 6, 42, 5, 7, 20, 3];
let isEven = (n) = { (n mod 2) == 0 };
let taken = takeWhile(data, isEven); /* [2, 6, 42] */
let dropped = dropWhile(data, isEven); /* [5, 7, 20, 3] */
Both functions stop taking (or dropping) as soon as they encounter an item
that doesn’t fulfill the predicate. Even though 20 is an even number, it isn’t
included in the result of the takeWhile().
Hint: You’ll probably end up writing nested helper functions for both of these.
The Belt.List.reverse() may come in handy for takeWhile().
 */

let data = [2, 6, 42, 5, 7, 20, 3];
let isEven = n => (n mod 2) == 0;

let takeWhile = (l: list('a), f: 'a => bool) : list('a) => {
  let rec helper = (acc: list('a), processList: list('a)) : list('a) => {
    switch (processList)  {
      | [] => Belt.List.reverse(acc) /* base case */
      | [a, ..._] when !f(a) => helper(acc, []) /* stop while */
      | [a, ...rest] => helper([a, ...acc], rest) /* keep */ 
    }
  }
  helper([], l);
}
let dropWhile = (l: list('a), f: 'a => bool) : list('a) => {
  let rec helper = (li: list('a)) : list('a) => {
    switch (li)  {
      | [a, ...rest] when f(a) => helper(rest) /* drop while true */
      | li => li /* stop & keep rest */
    }
  }
  helper(l);
}

let taken = takeWhile(data, isEven);
 /* [2, 6, 42] */
Js.log2("taken: ", DisplayList.stringOfList(taken, string_of_int));

let dropped = dropWhile(data, isEven); 
/* [5, 7, 20, 3] */
Js.log2("dropped: ", DisplayList.stringOfList(dropped, string_of_int));

