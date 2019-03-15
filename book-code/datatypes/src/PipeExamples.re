let f = (a: int, b: int): int => {
  3 * a + b
};

Js.log(5 -> f(7));    /* f(5, 7); result is 22 */
Js.log(5 -> f(7, _)); /* f(7, 5); result is 26 */
Js.log(5 |> f(7));    /* f(7, 5); result is 26 */

