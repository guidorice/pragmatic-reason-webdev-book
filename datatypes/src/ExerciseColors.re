/**
Create a variant data type called colorSpec that lets you specify a color in one
of these ways:

let color1 = White;
let color2 = Black;
let color3 = Gray(0.50); /* Percentage gray as a float */
let color4 = RGB(255, 255, 255); /* Integers for Red, Green, and Blue */

Write a function that converts a colorSpec to a string in the form rgb(r,g,b).
Here’s the starting point for your function:

let stringOfColorSpec = (cspec: colorSpec) : string => { /* your code here */
};
Here are examples of what it produces:
Js.log(stringOfColorSpec(White)); /* rgb(255,255,255) */
 Js.log(stringOfColorSpec(Black)); /* rgb(0,0,0) */
 Js.log(stringOfColorSpec(Gray(0.5))); /* rgb(127,127,127) */
 Js.log(stringOfColorSpec(RGB(64, 128, 192))); /* rgb(64,128,192) */
Writing a colorSpecOfString() is tricky because you need to handle a much larger
range of possible inputs than you’d need for the shirt sizes, so let’s not go
for that one right now.
*/

type colorSpec =
  | White
  | Black
  | Gray(float)
  | RGB(int, int, int);

let stringOfColorSpec = (cspec: colorSpec): string => {
  switch (cspec) {
  | White => "rgb(255,255,255)"
  | Black => "rgb(0,0,0)"
  | Gray(n) =>
    let bytes = 255. *. n;
    {j|rgb($bytes,$bytes,$bytes)|j};
  | RGB(r, g, b) => {j|rgb($r,$g,$b)|j}
  };
};

Js.log(stringOfColorSpec(White)); /* rgb(255,255,255) */
Js.log(stringOfColorSpec(Black)); /* rgb(0,0,0) */
Js.log(stringOfColorSpec(Gray(0.5))); /* rgb(127,127,127) */
Js.log(stringOfColorSpec(RGB(64, 128, 192))); /* rgb(64,128,192) */
