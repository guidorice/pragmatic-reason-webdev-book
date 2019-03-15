
type size =
  | XSmall(int)
  | Small
  | Medium
  | Large
  | XLarge(int);

type sleeve =
  | Short
  | Long
  | XLong; /* for tall people */

type color =
  | White
  | Blue
  | Red
  | Green
  | Brown;

type pattern =
  | Solid
  | Pinstripe
  | Check;

type cuff = 
  | Button
  | French
  | NoCuff;
 
type collar =
  | Button
  | Straight
  | Spread;

type order = {
  quantity: int,
  size: size,
  sleeve: sleeve,
  color: color,
  pattern: pattern,
  cuff: cuff,
  collar: collar
};

let myOrder = {
  quantity: 1,
  size: XLarge(1),
  sleeve: Long,
  color: Blue,
  pattern: Solid,
  cuff: Button,
  collar: Button
};

Js.log2("Size:", myOrder.size); /* Size: [1, tag: 1] */

let otherOrder = {
  ...myOrder,
  
  color: White,
  cuff: French
};

Js.log2("Cuff:", otherOrder.cuff); /* Cuff: 1 */

