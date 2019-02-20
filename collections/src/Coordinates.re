type coord = (float, float);
let distance = (p0: coord, p1: coord): float => {
  let (x0, y0) = p0;
  let (x1, y1) = p1;
  sqrt((x0 -. x1) ** 2.0 +. (y0 -. y1) ** 2.0);
};
let startPoint = (3.5, 4.6);
let endPoint = (0.5, 9.6);
let result = distance(startPoint, endPoint);
Js.log(result); /* output: 5.830951894845301 */

/* not recommended: fst, snd only work with 2-tuples */
let distance2 = (p0: coord, p1: coord): float => {
  let x0 = fst(p0);
  let y0 = snd(p0);
  let x1 = fst(p1);
  let y1 = snd(p1);
  sqrt((x0 -. x1) ** 2.0 +. (y0 -. y1) ** 2.0);
};