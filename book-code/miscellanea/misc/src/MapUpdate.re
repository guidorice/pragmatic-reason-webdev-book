let sickDays = Belt.Map.String.fromArray([| 
  ("David", 4),
  ("Cathy", 2), ("Felipe", 1)|]);

let outSick = fun 
  | Some(n) => Some(n + 1)
  | None => Some(1);
  
let remove = (_days: option(int)): option(int) =>  None; 

let result1 = Belt.Map.String.update(sickDays, "Cathy", outSick); 
/* ("David", 4) ("Cathy", 3) ("Felipe", 1) */

let result2 = Belt.Map.String.update(sickDays, "Joe", outSick);
/* ("David", 4) ("Cathy", 2) ("Felipe", 1) ("Joe", 1) */

let result3 = Belt.Map.String.update(sickDays, "David", remove);
/* ("Cathy", 2) ("Felipe", 1) */

let result4 = Belt.Map.String.update(sickDays, "Paracelsus", remove);
/* ("David", 4) ("Cathy", 2) ("Felipe", 1) */

Js.log2("r1: ", result1);
Js.log2("r2: ", result2);
Js.log2("r3: ", result3);
Js.log2("r4: ", result4);
