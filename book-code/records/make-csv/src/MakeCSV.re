/*
  Given an array of percentages, return an array of
  cumulative percentages. Thus, [|50, 20, 25, 5|]
  becomes [|50, 70, 95, 100|]
*/
let cumulative = (pct: array(int)): array(int) => {
  let (_, result) = Belt.Array.reduce(pct, (0, [||]),
    ((accSum, accArr), item) => {
      (accSum + item, Belt.Array.concat(accArr, [| accSum + item |]))
  });
  result;
};

/*
  An analog to Belt.List.getBy, but for arrays;
*/
let getRandomElement = (arr: array((string, int))): string =>
{
  let r = Random.int(100);
  let rec helper = (idx:int): string => {
    switch (idx) {
      | n when n == Belt.Array.length(arr) => {
          fst(arr[0]);
        }
      | n => {
          let (str, pct) = arr[n];
          (r <= pct) ? str : helper(n + 1)
        }
    }
  };
  helper(0);
};

/*
  Make a distribution frequency for choosing randomly among items
  Creates tuples of a string and its cumulative percent frequency.
  (Make sure everything adds up to 100.)
*/

let sizeArr = Belt.Array.zip([|"XS", "S", "M", "L", "XL", "XXL", "XXXL"|],
  cumulative([|5, 15, 40, 15, 15, 5, 5|]));

let sleeveArr = Belt.Array.zip([|"short", "long", "xlong"|],
  cumulative([|30, 60, 10|]));

let colorArr = Belt.Array.zip([|"white", "blue", "red", "green", "brown"|],
  cumulative([|25, 25, 25, 15, 10|]));

let patternArr = Belt.Array.zip([|"solid", "pinstripe", "check"|],
  cumulative([|40, 40, 20|]));

/* For long sleeves, most are button or french cuff */
let longCuffArr = Belt.Array.zip([|"button", "french", "none"|],
  cumulative([|60, 25, 16|]));

/* But for short sleeves, most have no cuff */
let shortCuffArr = Belt.Array.zip([|"button", "french", "none"|],
  cumulative([|10, 5, 85|]));

let collarArr = Belt.Array.zip([|"button", "straight", "spread"|],
  cumulative([|40, 40, 20|]));

let createOrderString = () : string => {
  let sleeve = getRandomElement(sleeveArr);
  string_of_int(Random.int(5) + 2) ++ "," ++
    getRandomElement(sizeArr) ++ "," ++
    getRandomElement(colorArr) ++ "," ++
    getRandomElement(patternArr) ++ "," ++
    getRandomElement(collarArr) ++ "," ++
    sleeve ++ "," ++
    getRandomElement((sleeve == "short") ? shortCuffArr : longCuffArr)
}

let main = (): unit => {
  let _ = Random.self_init();
  let rec helper = (acc, n) => {
    switch (n) {
      | 0 => acc
      | n => helper(acc ++ createOrderString() ++ "\n", n - 1)
    }
  }
  let outputString = helper("Quantity,Size,Color,Pattern,Collar,Sleeve,Cuff\n",
    100);
  let _ = Node.Fs.writeFileAsUtf8Sync("orders.csv", outputString);

};

main();
