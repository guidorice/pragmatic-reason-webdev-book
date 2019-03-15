type colorSpec = 
  | White
  | Black
  | Gray(float)
  | RGB(int, int, int);


let stringOfColorSpec = (cspec: colorSpec): string => {
  switch (cspec) {
    | White => "rgb(255, 255, 255)"
    | Black => "rgb(0, 0, 0)"
    | Gray(percent) => {
        let strValue = string_of_int(int_of_float(percent *. 255.0));
        "rgb(" ++ strValue ++ ", " ++ strValue ++ ", " ++ strValue ++ ")"
       }
    | RGB(r, g, b) => {
        "rgb(" ++ string_of_int(r) ++ ", " ++ string_of_int(g) ++ ", " ++
          string_of_int(b) ++ ")"
      }
  }
};

Js.log(stringOfColorSpec(White)); /* rgb(255,255,255) */
Js.log(stringOfColorSpec(Black)); /* rgb(0,0,0) */
Js.log(stringOfColorSpec(Gray(0.5))); /* rgb(127,127,127) */
Js.log(stringOfColorSpec(Gray(0.2)));
Js.log(stringOfColorSpec(RGB(64, 128, 192))); /* rgb(64,128,192) */

