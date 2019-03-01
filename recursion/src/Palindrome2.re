/** Write a new function isPalindrome2() that has three parameters: the string
being tested and two integers (call them start and finish) that are indices into
the string. If the characters at the indices are the same, then recursively call
with start + 1 and finish - 1. This avoids doing a Js.String.slice() for every
recursive call. I’ll leave it to you to figure out the base case. You might want
to use a nested “helper” function so users of your function can call it as
isPalindrome2(stringValue). */

let isPalindrome2(word) {
 let rec helper = (~s: string, ~start: int, ~finish: int) : bool => {
   switch (start, finish) {
     | (start, finish) when finish - start <= 1 => true
     | (start, finish) when Js.String.get(s, start) == Js.String.get(s, finish) =>
      helper(~s, ~start=start + 1, ~finish=finish - 1)
      | (_, _) => false
   }
 }
 helper(~s=word, ~start=0, ~finish=Js.String.length(word) - 1)
}

Js.log(isPalindrome2("civic")); /* output: true */
Js.log(isPalindrome2("deed")); /* output: true */
Js.log(isPalindrome2("runner")); /* output: false */
Js.log(isPalindrome2("fnord")); /* output: false */

let repeat = (s: string, n: int) => {
  let rec repeatHelper = (accumulator: string, counter: int) : string => {
    switch (counter) {
      | 0 => accumulator /* base case; we're finished */
      | _ => repeatHelper(accumulator ++ s, counter - 1)
    };
  };
  repeatHelper("", n);
};

let testString = repeat("a", 50000);
let rec repeatTest = (n: int, accumulatedTime: float) : float => {
  switch (n) {
    | 0 => accumulatedTime
    | _ => {
      let startTime = Js.Date.now();
      let _ = isPalindrome2(testString);
      let endTime = Js.Date.now();
      repeatTest(n - 1, accumulatedTime +. (endTime -. startTime))
    }
  }
};
let totalTime = repeatTest(1000, 0.0);

Js.log2("My version of isPalindrome2 (string from parameter): Average time in msec:", totalTime /. 1000.0);