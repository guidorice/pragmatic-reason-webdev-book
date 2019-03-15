let recip1 = (x: float): option(float) => 
  switch (x) {
    | 0.0 => None
    | x => Some(1.0 /. x)
  };
  
let recip2 = fun
  | 0.0 => None
  | x => Some(1.0 /. x);

let toFloat = (s:string): option(float) => {
  switch (float_of_string(s)) {
    | result => Some(result)
    | exception(Failure("float_of_string")) => None
  }
};

let r1 = recip1(8.0);
let r2 = recip2(8.0);
Js.log(r1);
Js.log(r2);

let r1b = recip1(0.0);
let r2b = recip2(0.0);
Js.log(r1b);
Js.log(r2b);
