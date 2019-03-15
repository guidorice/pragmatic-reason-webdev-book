/* Interface */
module type Time {
  type t;
  
  let make: (int, int) => t;
  let add: (t, t) => t;
};

/* Implementation */
module Time: Time = {
  type t = {
    hour: int,
    minute:int
  };
  
  let make = (h:int, m:int): t => {
    {hour: abs(h) mod 24,
     minute: abs(m) mod 60}
  };

  let add = (t1: t, t2: t): t => {
    let total = (t1.hour * 60 + t1.minute) +
      (t2.hour * 60 + t2.minute);
    make(total / 60, total mod 60)
  };
};

let time1: Time.t = Time.make(15, 30);
Js.log(time1); /* [15, 30] */

let time2: Time.t = Time.make(20, 45);
Js.log(time2); /* [20, 45] */

let time3 = Time.add(time1, time2);
Js.log(time3); /* [12, 15] */

let wrong = Time.make(-30, 170);
Js.log(wrong); /* [6, 50] */
