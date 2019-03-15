let rec keepIndices = (arr: array('a), position: int, accumulator: array(int),
  f : ('a => bool)) : array(int) => {
    if (position < Belt.Array.length(arr)) {
      f(Belt.Array.getUnsafe(arr, position))
        ? keepIndices(arr, position + 1,
            Belt.Array.concat(accumulator, [|position|]), f)
        : keepIndices(arr, position + 1, accumulator, f)
    } else  {
      accumulator
    }
};

let words = [|"cow", "aardvark", "squirrel", "fish", "snake", "capybara"|];
let isShortWord = (s: string) : bool => {Js.String.length(s) < 6};
let result = keepIndices(words, 0, [||], isShortWord);
Js.log(result); /* result array: [|0, 3, 4|] */

