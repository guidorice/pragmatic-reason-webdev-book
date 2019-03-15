module Performance = {
  type t; /* DOMHighResTimeStamp - a double, milliseconds since startup */

  [@bs.scope "performance"] [@bs.module "perf_hooks"] 
  external now: unit => t = "";

  external toFloat: t => float = "%identity"; 
  external fromFloat: float => t = "%identity"; 
  
  let zero: t = fromFloat(0.0);

  let addInterval: (t, t, t) => t =
    (current, start, finish) =>
      (toFloat(finish) -. toFloat(start) +. toFloat(current))->fromFloat;
};

