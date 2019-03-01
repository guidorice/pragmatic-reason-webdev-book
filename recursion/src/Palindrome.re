let rec isPalindrome = (s: string) : bool => { 
  let len = Js.String.length(s); 
  if (len <= 1) { 
    true;
  } else if (Js.String.get(s, 0) != Js.String.get(s, len - 1)) { 
    false;
  } else {
    isPalindrome(Js.String.slice(~from= 1, ~to_=len - 1, s)); 
  } 
};

Js.log(isPalindrome("civic")); /* output: true */
Js.log(isPalindrome("deed")); /* output: true */
Js.log(isPalindrome("runner")); /* output: false */

let rec isPalindromeLogged = (s: string) : bool => {
  let len = Js.String.length(s);
  Js.log("Seeing if '" ++ s ++ "' is a palindrome");
  if (len <= 1) {
    Js.log("Length is " ++ string_of_int(len) ++ " - we have a palindrome");
    true;
  } else if (Js.String.get(s, 0) != Js.String.get(s, len - 1)) {
    Js.log("Mismatch between " ++ Js.String.get(s, 0) ++ " and "
      ++ Js.String.get(s, len - 1) ++ " - not a palindrome");
    false;
  } else {
    isPalindromeLogged(Js.String.slice(~from= 1, ~to_=len - 1, s));
  }
};

Js.log(isPalindromeLogged("civic"));
Js.log(isPalindromeLogged("cynic"));

let repeatWithReduce = (s: string, n: int) : string => {
  Belt.Array.reduce(Belt.Array.range(0, n - 1), "",
    (accumulator: string, _item: int) => { accumulator ++ s });
};

Js.log(repeatWithReduce("abc", 4));

let rec repeatRec = (s: string, accumulator: string, n: int) : string => {
  switch (n) {
    | 0 => accumulator /* base case; weâ€™re finished */
    | _ => repeatRec(s, accumulator ++ s, n - 1)
  };
};
Js.log(repeatRec("ha", "", 4)); /* output: hahahaha */

let repeat = (s: string, n: int) => {
  let rec repeatHelper = (accumulator: string, counter: int) : string => {
    switch (counter) {
      | 0 => accumulator /* base case; weâ€™re finished */
      | _ => repeatHelper(accumulator ++ s, counter - 1)
    };
  };
  repeatHelper("", n);
};
Js.log(repeat("ha", 4)); /* output: hahahaha */

let testString = repeat("a", 50000);
let rec repeatTest = (n: int, accumulatedTime: float) : float => {
  switch (n) {
    | 0 => accumulatedTime
    | _ => {
      let startTime = Js.Date.now();
      let _ = isPalindrome(testString);
      let endTime = Js.Date.now();
      repeatTest(n - 1, accumulatedTime +. (endTime -. startTime))
    }
  }
};
let totalTime = repeatTest(1000, 0.0);

Js.log2("isPalindrome (string slicing): Average time in msec:", totalTime /. 1000.0);

let isPalindrome2 = (s: string) : bool => {
  let rec helper = (start: int, finish: int) => {
    if (finish - start <= 1) {
        true;
    } else {
      if (Js.String.get(s, start) != Js.String.get(s, finish)) {
        false;
      } else {
        helper(start + 1, finish - 1);
      }
    }
  };
  helper(0, Js.String.length(s) - 1);
};

Js.log2("civic:", isPalindrome2("civic"));
Js.log2("deed", isPalindrome2("deed"));
Js.log2("runner", isPalindrome2("runner"));

/*
  Timing test for isPalindrome2; uses the same
  test string as repeatTest
*/
let rec repeatTest2 = (n: int, accumulatedTime: float) : float => {
  switch (n) {
    | 0 => accumulatedTime
    | _ => {
      let startTime = Js.Date.now();
      let _ = isPalindrome2(testString);
      let endTime = Js.Date.now();
      repeatTest2(n - 1, accumulatedTime +. (endTime -. startTime))
    }
  }
};
let totalTime2 = repeatTest2(1000, 0.0);

Js.log2("isPalindrome2 (string from closure): Average time in msec:", totalTime2 /. 1000.0);
