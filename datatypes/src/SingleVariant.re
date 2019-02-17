type scoreType =
  | Score(int);
type percentType =
  | Percent(float);
type userId =
  | UserId(int);

let person: userId = UserId(60);
let calcPercent = (score: scoreType, max: scoreType): percentType => {
  let Score(s) = score;
  let Score(m) = max;
  Percent(float_of_int(s) /. float_of_int(m) *. 100.0);
} /* Won't compile. Comment out next line to get a working program */;

/* let result = calcPercent(person, Score(75));
 */

let Percent(result) = calcPercent(Score(40), Score(75));
Js.log({j|Good result is $result|j}); /* output: Good result is 53.33333... */