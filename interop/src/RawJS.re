let rightNow = [%raw {|
 function () {
  var d = new Date();
  return d.toString();
 }()
|}];

let message = "It is now " ++ rightNow;
Js.log(message);
