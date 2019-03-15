module Size:
  {
    type t = XSmall(int) | Small | Medium | Large | XLarge(int);
    let toString: t => string;
    let fromString: string => option(t);
  };
module Sleeve:
  {
    type t = Short | Long | XLong;
    let toString: t => string;
    let fromString: string => option(t);
  };
module Color:
  {
    type t = White | Blue | Red | Green | Brown;
    let toString: t => string;
    let fromString: string => option(t);
  };
module Pattern:
  {
    type t = Solid | Pinstripe | Check;
    let toString: t => string;
    let fromString: string => option(t);
  };
module Cuff:
  {
    type t = Button | French | NoCuff;
    let toString: t => string;
    let fromString: string => option(t);
  };
module Collar:
  {
    type t = Button | Straight | Spread;
    let toString: t => string;
    let fromString: string => option(t);
  };
type order = {
  quantity: int,
  size: Size.t,
  sleeve: Sleeve.t,
  color: Color.t,
  pattern: Pattern.t,
  cuff: Cuff.t,
  collar: Collar.t,
};
let myOrder: order;
let otherOrder: order;
