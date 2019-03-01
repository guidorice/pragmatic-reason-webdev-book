let rec sumUntilNegative = (items: list(int), total: int) : int => {
  switch (items) {
    | [] => total
    | [x, ..._] when x < 0 => total
    | [x, ...xs] => sumUntilNegative(xs, total + x)
  }
};
