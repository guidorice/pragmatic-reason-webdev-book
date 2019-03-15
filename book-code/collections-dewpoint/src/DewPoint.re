module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

type optOpt = option(array(option(float)));

type stringPair = (string, string);

/* This type is used for reducing the input array
 * of strings to pairs of strings
 */
type pairAccType = (int, string, array(stringPair));
  

/*
 * First element of tuple is temperature in degrees Celsius.
 * Second element is relative humidity as a percent (not a decimal)
 */
type weatherDatum = (float, float);

/*
 * Convenience types for readability 
 */
type weatherResult = Belt.Result.t(weatherDatum, string);
type resultFloat = Belt.Result.t(float, string);


let toFixed = Js.Float.toFixedWithPrecision;

let stringOfWeatherDatum = ((temperature, humidity): weatherDatum) : string => {
  toFixed(temperature, ~digits=1) ++ {js|°|js} ++ ", " ++
  toFixed(humidity, ~digits=1) ++ "%"
};

let toFloat = (s:string): resultFloat => {
  switch (float_of_string(s)) {
    | result => Belt.Result.Ok(result)
    | exception(Failure("float_of_string")) => Belt.Result.Error("Invalid number " ++ s)
  }
};

/*
 * Convert string in form "number, number%" to a tuple of
 * temperature and humidity. Keep percent in percent format (58.0)
 * rather than converting to decimal (0.58).
 */
let weatherDataOfPair = ((temperatureStr, humStr): stringPair) : weatherResult => {
  let humidityStr = Js.String.replace("%", "", humStr);
  switch (toFloat(temperatureStr), toFloat(humidityStr)) {
    | (Belt.Result.Ok(temp), Belt.Result.Ok(hum)) => Belt.Result.Ok((temp, hum))
    | (_,_) => Belt.Result.Error("Invalid weather datum " ++ temperatureStr ++ ", " ++ humStr)
  }
};


let getValue = (element: option(Elem.t)) : option(string) => {
  element
    -> Belt.Option.map(_, Elem.unsafeAsHtmlElement)
    -> Belt.Option.map(_, D.HtmlElement.value);
};

/*
 * Get the string
 * Split on commas
 * If even #, split into pairs of strings, else Error("not enough items")
 * Convert pairs of strings into weatherDatum points
 */
let commaSplit = (str: string): array(string) => {
  Js.String.splitByRe([%re "/\\s*,\\s*/"], str) ->
    Belt.Array.map(_, (item) => {
      Belt.Option.getWithDefault(item, "")
    })
};


/*
 * Convert an array of strings in temperature/humidity pairs to
 * an array of (temperature, humidity) floats.
 *
 * We need to keep track of the current position in the array and the
 * previous item.
 * Here’s the logic:
 *    If we're at an even position:
 *      convert string to temperature; whatever its result is now our "previous" item
 *    otherwise
 *      If the previous item didn’t error on us:
 *        convert this one (the humidity) to a float
 *        If OK, add (temperature, humidity) to the array
 *        otherwise, add the error to the array
 *      else previous item did error:
 *        add that error to the array
 *
 *  I am sure there is a better way to do this, but this is the first way that
 *  occurred to me that is understandable.
 */
type reductionType = (int, resultFloat, array(weatherResult))
let weatherReducer = (accum: reductionType, s:string): reductionType => {
  let (position, previous, acc) = accum;
  let s2 = Js.String.replace("%", "", s); /* always get rid of % */
  /* Even position - disregard previous */
  if (position mod 2 == 0) {
    let temperature = toFloat(s2); /* attempt conversion */
    (position + 1, temperature, acc) /* and pass it on */
  } else {
    switch (previous) {
      | Belt.Result.Ok(temperature) => {
          let humidity = toFloat(s2);
          switch (humidity) {
            | Belt.Result.Ok(hValue) => (position + 1, Ok(0.0),
                Belt.Array.concat(acc, [|Belt.Result.Ok((temperature, hValue))|]))
            | Belt.Result.Error(e) => (position + 1, Belt.Result.Ok(0.0),
              Belt.Array.concat(acc, [| Belt.Result.Error(e) |]))
          }
        }
      | Belt.Result.Error(e) =>
          (position + 1, Belt.Result.Ok(0.0),
            Belt.Array.concat(acc, [|Belt.Result.Error(e)|]))
    }
  }
};

/*
 * Convert an array of strings in temperature/humitidy pairs to an array of
 * Result((float, float)) tuples. After processing all the elements, if
 * there’s an odd number of elements in the original array, add
 * an Error() message
 */
let convertToWeather = (itemArray: array(string)): array(weatherResult) => {
  let (_pos, _prev, result) = Belt.Array.reduce(itemArray,
    (0, Belt.Result.Ok(0.0), [| |]), weatherReducer);
  if ((Belt.Array.length(itemArray) mod 2) == 1) {
    Belt.Array.concat(result, [| Error("Odd number of entries in list") |])
  } else {
    result
  }
};

/*
 * Calculate the dew point of one (temperature, humidity) tuple
 */
let calculateOnePoint = ((temperature: float, humidity:float)): float => {
  temperature -. ((100.0 -. humidity) /. 5.0)
};

/*
 * Calculate the dew points for an array of Belt.Result((temperature, humidity))
 * tuples. The use of Belt.Result.map makes sure that Error() entries get passed
 * along, and Ok(tuple)s get unwrapped and processed.
 */
let calculateDewPoints = (weatherData: array(weatherResult)): array(resultFloat) => {
  Belt.Array.map(weatherData, (datum) => {
    Belt.Result.map(datum, calculateOnePoint)
  })
};


let findIndexWithFcn = (data: array(resultFloat), f: (float, float) => bool): (int, float) => {

  /*
   * As we reduce the array, we need to keep track of three things:
   *  the current position
   *  the position where we found a value for which the function returns true
   *  the value we found
   *
   * If we were finding minima and maxima of a plain array of floats, no problem;
   * we’d use the first item in the array as the initial min or max. But we can’t
   * do that here, as the first item might be a Belt.Result.Error(). In fact,
   * they might _all_ be! So, when we find a value that works, we have to check to
   * see if it’s the first one (foundAt will be -1), in which case, it becomes the
   * “current value”. Otherwise, we already have a candidate, and we call the function.
   */
  let helper: ((int, int, float), resultFloat) => (int, int, float) =
    ((pos, foundAt, value), item) => {
    switch (item) {
      | Belt.Result.Ok(dPoint) => {
          if (foundAt == -1) {
            (pos + 1, pos, dPoint)
          } else {
            f(dPoint,value) ? (pos + 1, pos, dPoint) : (pos + 1, foundAt, value)
          }
        }
      | Belt.Result.Error(_) => (pos + 1, foundAt, value)
    }
  };

  let (_pos, foundAt, value) = Belt.Array.reduce(data, (0, -1, 0.0), helper);
  if (foundAt >= 0) {
    (foundAt, value)
  } else {
    (-1, 0.0)
  }
};


let makeListItem = (acc: string, item: resultFloat): string => {
  acc ++ "<li>" ++
  switch (item) {
    | Ok(x) => toFixed(x, ~digits=1)
    | Error(s) => s
  }
  ++ "</li>\n"
};

/* Reducer to count number of valid dew points */
let countPoints = (acc: int, item: resultFloat) => {
  switch (item) {
    | Ok(_x) => acc + 1
    | _ => acc
  }
};

/* Reducer to get sum of valid dew points */
let sumPoints = (acc: float, item: resultFloat) => {
  switch (item) {
    | Ok(x) => acc +. x
    | _ => acc
  }
};

let calculate = (_: Dom.event) : unit => {
  let inputStr = getValue(Doc.getElementById("inputString", D.document))
  let outputStr = switch (inputStr) {
    | Some(inputStr) => {
        if (Js.String.trim(inputStr) != "") {
          let dewPoints = inputStr
          -> commaSplit
          -> convertToWeather
          -> calculateDewPoints;
         
          let nValid = Belt.Array.reduce(dewPoints, 0, countPoints);
          if (nValid > 0) {
            let (minPos, minData) = findIndexWithFcn(dewPoints, (a, b) => a < b);
            let (maxPos, maxData) = findIndexWithFcn(dewPoints, (a, b) => a > b);
            let avg = Belt.Array.reduce(dewPoints, 0.0, sumPoints) /. float_of_int(nValid);

            "<p>Dew Points</p>" ++
            "<ul>" ++ Belt.Array.reduce(dewPoints, "", makeListItem) ++ "</ul>" ++
            "<div>Minimum value: " ++ string_of_float(minData) ++ " (at position " ++ 
               string_of_int(minPos + 1) ++ ")</div>" ++
            "<div>Maximum value: " ++ string_of_float(maxData) ++ " (at position " ++
               string_of_int(maxPos + 1) ++ ")</div>" ++
            "<div>Average value: " ++ string_of_float(avg) ++ "</div>"
          } else {
            ""
          }
        } else {
          ""
        }
      }
    | None => ""
  }
  
  
  let _ = Doc.getElementById("results", D.document)
    -> Belt.Option.map(_, Elem.setInnerHTML(_, outputStr));
  (); 
};

let calcButton = Doc.getElementById("calculate", D.document);
switch (calcButton) {
  | Some(element) =>
      D.EventTarget.addEventListener(
        "click", calculate, D.Element.asEventTarget(element))
  | None => ()
};

