
let items = [|10, 11, 12, 13, 14, 15, 16|];

Js.log(Belt.Array.length(items)); /* 7 */
Js.log(Belt.Array.size(items)); /* 7 */

let multiples = Belt.Array.make(5, 7.0);
Js.log(multiples);

let sqrtPlusOne = (x) => { sqrt(float_of_int(x) +. 1.0) };
let roots = Belt.Array.makeBy(5, sqrtPlusOne);
Js.log(roots);

let more = [|17, 18, 19|];
let joined = Belt.Array.concat(items, more);
Js.log(joined);

let part1 = [|"the", "array", "has"|];
let part2 = Belt.Array.concat(part1, [|"more"|]);
Js.log(part2); /* [|"the", "array", "has", "more"|] */
 
/* items contains [|10, 11, 12, 13, 14, 15, 16|]; */
Js.log(Belt.Array.slice(items, ~offset=1, ~len=3)); /* [|11, 12, 13|] */
Js.log(Belt.Array.slice(items, ~offset=5, ~len=9)); /* [|15, 16|] */
Js.log(Belt.Array.slice(items, ~offset=-3, ~len=2)); /* [|14, 15|] */
Js.log(Belt.Array.slice(items, ~offset=3, ~len=-2)); /* [| |] */

let optElement = Belt.Array.get(items, 3); /* Some(13) */
let badOptElement = Belt.Array.get(items, 10); /* None */
let badOptElement2 = Belt.Array.getUnsafe(items, 10); /* undefined */
let element = Belt.Array.getExn(items, 3); /* 13 */
let bracketElement = items[3]; /* 13 */
Js.log(optElement);
Js.log(badOptElement);
Js.log(badOptElement2);
Js.log(element);
let badElement = Belt.Array.getExn(items, 10); /* throws error */


