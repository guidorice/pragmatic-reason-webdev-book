/** repeatRec is tail recursive and gets compiled to an optimized while loop */
let rec repeatRec = (s: string, accumulator: string, n: int) : string => {
  switch (n) {
    | 0 => accumulator /* base case; weâ€™re finished */
    | _ => repeatRec(s, accumulator ++ s, n - 1)
  };
};

/** repeatRec2 is just recursive, cannot be optimized to while loop */
let rec repeatRec2 = (s:string, n:int) : string => {
  switch (n) {
    | 0 => ""
    | n => s ++ repeatRec2(s, n - 1)
  }
};
Js.log(repeatRec("go", "", 3)); /* output: gogogo */
Js.log(repeatRec2("go", 3));
