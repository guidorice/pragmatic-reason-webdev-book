let toFloat = (s:string): option(float) => {
  switch (float_of_string(s)) {
    | result => Some(result)
    | exception(Failure("float_of_string")) => None
  }
};

let reciprocal = fun
  | 0.0 => None
  | x => Some(1.0 /. x);

let cube = (x) => x *. x *. x;

let makeDisplayText = fun
    | Some(value) => "The result is " ++ value
    | None => "Could not calculate result.";

let calculation = (input: string): string => {
  toFloat(input)
  -> Belt.Option.flatMap(reciprocal)
  -> Belt.Option.map(cube)
  -> Belt.Option.map(Js.Float.toFixedWithPrecision(~digits=3))
  -> makeDisplayText
};

let cubeArray = (data: array(float)): array(float) => {
  Belt.Array.map(data, cube);
}

Js.log(calculation("0.125"));
Js.log(cubeArray([|3.0, 4.0, 5.0|]));
