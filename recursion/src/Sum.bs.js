// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';


function sumUntilNegative(_items, _total) {
  while(true) {
    var total = _total;
    var items = _items;
    if (items) {
      var x = items[0];
      if (x < 0) {
        return total;
      } else {
        _total = total + x | 0;
        _items = items[1];
        continue ;
      }
    } else {
      return total;
    }
  };
}

exports.sumUntilNegative = sumUntilNegative;
/* No side effect */
