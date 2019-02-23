/**
Consider a two-tuple of data that gives temperature in degrees Celsius and
relative humidity as a percent. Write a program that takes a list (or array—
whichever you prefer) of these tuples and calculates:
• The dew point for each tuple, using the formula
Td = T − ((100 − RH) / 5)
This formula is the simplest one available; it is fairly accurate for relative
humidity over 50%. There are more accurate formulas—if you want to
research them and implement one of those instead, be my guest.
• The maximum, minimum, and average temperatures
• The maximum, minimum, and average dew points
Bonus challenge: for the maximums and minimums, give the element indices
where they occur. Display the indices starting with one for the benefit of
humans, as opposed to zero, which is for the benefit of programmers. For
example, in this data: [(12.5, 30), (13.7, 35), (13.2, 32), (13.7, 35)], you might display:
Minimum temperature: 12.5 (entry 1)
Maximum temperature: 13.7 (entries 2, 4)
*/;

type temperature =
  | Celcius(float);
type humidity =
  | Percent(float);
type reading = (temperature, humidity);

let dewpoint: reading => float =
  ((t, h)) => {
    let d =
      switch (t, h) {
      | (Celcius(t), Percent(h)) => t -. (100.0 -. h) /. 5.0
      };
    d;
  };

let got = dewpoint((Celcius(12.5), Percent(30.)));
Js.log(got);

let dewpoint: reading => float =
  fun
  | (Celcius(t), Percent(h)) => t -. (100.0 -. h) /. 5.0;

let got = dewpoint((Celcius(5.), Percent(49.)));
Js.log(got);