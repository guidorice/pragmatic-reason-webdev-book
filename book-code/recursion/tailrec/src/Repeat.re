let rec repeatRec = (s: string, accumulator: string, n: int) : string => {
  switch (n) {
    | 0 => accumulator /* base case; we’re finished */
    | _ => repeatRec(s, accumulator ++ s, n - 1)
  };
};

let rec repeatRec2 = (s:string, n:int) : string => {
  switch (n) {
    | 0 => ""
    | n => s ++ repeatRec2(s, n - 1)
  }
};
Js.log(repeatRec("go", "", 3)); /* output: gogogo */
Js.log(repeatRec2("go", 3));
