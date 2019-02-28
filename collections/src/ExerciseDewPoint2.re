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

type temperature = float;
type humidity = int;
type reading = (temperature, humidity);

let dewpoint = ((t, h): reading): float =>
  t -. float_of_int(100 - h) /. 5.0;

let readings = [(12.5, 30), (13.7, 35), (13.2, 32), (13.7, 39)];
Js.log2("readings:", Belt.List.toArray(readings));

let maxOfArray = arr => ArrayLabels.fold_left(~f=max, ~init=min_float, arr);
let minOfArray = arr => ArrayLabels.fold_left(~f=min, ~init=max_float, arr);

/* Belt.List.forEach(
     readings,
     reading => {
       let dp = dewpoint(reading);
       Js.log(dp);
     },
   ); */

let temps = Belt.List.map(readings, ((t, _)) => t);
let dewpoints = Belt.List.map(readings, reading => dewpoint(reading));

let maxTemp = maxOfArray(Belt.List.toArray(temps));
let minTemp = minOfArray(Belt.List.toArray(temps));

let maxDp = maxOfArray(Belt.List.toArray(dewpoints));
let minDp = minOfArray(Belt.List.toArray(dewpoints));

Js.log("max temp: " ++ string_of_float(maxTemp));
Js.log("min temp: " ++ string_of_float(minTemp));
Js.log("max dewpoint: " ++ string_of_float(maxDp));
Js.log("min dewpoint: " ++ string_of_float(minDp));

let avg = list => {
  let n = float_of_int(Belt.List.length(list));
  let sum = Belt.List.reduce(list, 0., (t, acc) => acc +. t);
  sum /. n;
};

let avgTemp = avg(temps);
Js.log("average temp: " ++ string_of_float(avgTemp));

let avgDewpoint = avg(dewpoints);
Js.log("average dewpoint: " ++ string_of_float(avgDewpoint));

let maxTemps =
  Belt.List.mapWithIndex(temps, (i, t) => (i, t))
  |> Belt.List.keep(_, ((_, t)) => t == maxTemp)
  |> Belt.List.map(_, ((i, _)) => i + 1);
let maxTempsArray = Belt.List.toArray(maxTemps);
Js.log({j|maximum temperature observed: $maxTemp entry ($maxTempsArray)|j});

let minTemps =
  Belt.List.mapWithIndex(temps, (i, t) => (i, t))
  |> Belt.List.keep(_, ((_, t)) => t == minTemp)
  |> Belt.List.map(_, ((i, _)) => i + 1);
let minTempsArray = Belt.List.toArray(minTemps);
Js.log({j|minimum temperature observed: $minTemp entry ($minTempsArray)|j});