let convertWithDefault = (str: string, defaultValue: 'a,
                          convert: (string) => option('a)): 'a => {
   Belt.Option.getWithDefault(convert(str), defaultValue);
};

let toIntWithDefault = (s:string, defaultValue:int): int => {
  switch (int_of_string(s)) {
    | result => result
    | exception(Failure("int_of_string")) => defaultValue
  }
};

type state = {
  qtyStr: string,
  sizeStr: string,
  sleeveStr: string,
  colorStr: string,
  patternStr: string,
  nextOrderNumber: int,
  orders: array(Shirt.Order.t),
  errorText: string,
};

type action =
  | Enter(Shirt.Order.t)
  | ChangeQty(string)
  | ChangeSize(string)
  | ChangeSleeve(string)
  | ChangeColor(string)
  | ChangePattern(string)
  | Delete(Shirt.Order.t);

let makeSelect = (label: string, choices: array(string),
                  value: string, changeFcn) => {

  let makeOptionElement = (value: string) => {
    <option key={value} value={value}>{ReasonReact.string(value)}</option> 
  };
  
  let menuOptionElements = Belt.Array.map(choices, makeOptionElement); 

    <span className="item"> 
      <label>{ReasonReact.string(" " ++ label ++ ": ")}</label>
      <select value={value} onChange={changeFcn}>
        {ReasonReact.array(menuOptionElements)} 
      </select>
    </span>
};

let createOrder = (state) : Shirt.Order.t => {
  {
    orderNumber: state.nextOrderNumber,
    quantity: toIntWithDefault(state.qtyStr, 0),
    size: convertWithDefault(state.sizeStr, Shirt.Size.Medium,
                             Shirt.Size.fromString),
    sleeve: convertWithDefault(state.sleeveStr, Shirt.Sleeve.Long,
                               Shirt.Sleeve.fromString),
    color: convertWithDefault(state.colorStr, Shirt.Color.White,
                              Shirt.Color.fromString),
    pattern: convertWithDefault(state.patternStr, Shirt.Pattern.Solid,
                                Shirt.Pattern.fromString),
  }
};

let component = ReasonReact.reducerComponent("OrderForm");

let make = (_children) => {
  ...component,

  initialState: () => {
    qtyStr: "1",
    sizeStr: Shirt.Size.toString(Shirt.Size.Medium),
    sleeveStr: Shirt.Sleeve.toString(Shirt.Sleeve.Long),
    colorStr: Shirt.Color.toString(Shirt.Color.White),
    patternStr: Shirt.Pattern.toString(Shirt.Pattern.Solid),
    orders: [| |],
    nextOrderNumber: 1,
    errorText: ""
  },
  /* State transitions */

  reducer: (action, state:state) =>
    switch (action) {
    | Enter(order) => {
        let n = toIntWithDefault(state.qtyStr, 0);
        if (n > 0 && n <= 100) {
          ReasonReact.Update({...state, 
            orders: Belt.Array.concat(state.orders, [|order|]), 
            nextOrderNumber: state.nextOrderNumber + 1, 
            errorText: "" 
          })
        } else {
          ReasonReact.Update({...state,
            errorText: "Quantity must be between 1 and 100." 
          })
        }
      }
    | ChangeQty(newQty) => {
        ReasonReact.Update({...state, qtyStr: newQty})
      }
    | ChangeSize(newSize) => {
        ReasonReact.Update({...state, sizeStr: newSize})
      }
    | ChangeSleeve(newSleeve) => {
        ReasonReact.Update({...state, sleeveStr: newSleeve})
      }
    | ChangeColor(newColor) => {
        ReasonReact.Update({...state, colorStr: newColor})
      }
    | ChangePattern(newPattern) => {
        ReasonReact.Update({...state, patternStr: newPattern})
      }
    | Delete(order) => {
        ReasonReact.Update({...state,
        orders: Belt.Array.keep(state.orders,
                    (item) => (item.orderNumber != order.orderNumber))})
      }
    },
  render: self => {
    let orderItems = Belt.Array.map(self.state.orders, (order) => 
        <OrderItem key={string_of_int(order.orderNumber)}
          order={order} deleteFunction=(_event => self.send(Delete(order)))/>);
    let orderTable = 
      if (Belt.Array.length(self.state.orders) > 0) {
         <table>
          <thead>
            <tr>
              <th>{ReasonReact.string("Qty")}</th>
              <th>{ReasonReact.string("Size")}</th>
              <th>{ReasonReact.string("Sleeve")}</th>
              <th>{ReasonReact.string("Color")}</th>
              <th>{ReasonReact.string("Pattern")}</th>
              <th>{ReasonReact.string("Action")}</th>
            </tr>
          </thead>
          <tbody>
            {ReasonReact.array(orderItems)}
          </tbody>
        </table>
     } else {
        <p>
          {ReasonReact.string("No orders entered yet.")}
        </p>
    };

    <div>
      <p className="flex">
      <span className="item"> 
        {ReasonReact.string("Qty: ")}
        <input type_="text" size=4
          value={self.state.qtyStr} 
          onChange={(event)=> 
            self.send(ChangeQty(ReactEvent.Form.target(event)##value))}/> 
      </span>
      {makeSelect("Size", 
        [|"XS", "S", "M", "L", "XL", "XXL", "XXXL"|],
        self.state.sizeStr,
        (event) => self.send(ChangeSize(
          ReactEvent.Form.target(event)##value)))}
      {makeSelect("Sleeve",
        [|"Short sleeve", "Long sleeve", "Extra-long sleeve"|],
        self.state.sleeveStr,
        (event) => self.send(ChangeSleeve(
          ReactEvent.Form.target(event)##value)))}

      {makeSelect("Color",
        [|"White", "Blue", "Red", "Green", "Brown"|],
        self.state.colorStr,
        (event) => self.send(ChangeColor(
          ReactEvent.Form.target(event)##value)))}

      {makeSelect("Pattern",
        [|"Solid", "Pinstripe", "Checked"|],
        self.state.patternStr,
        (event) => self.send(ChangePattern(
          ReactEvent.Form.target(event)##value)))}
      <span className="item">
        <button onClick=(_event => { 
            let order = createOrder(self.state);
            self.send(Enter(order))}) >
          {ReasonReact.string("Add")}
        </button>
      </span>
      </p>

      <p id="errorText"> 
        {ReasonReact.string(self.state.errorText)}
      </p>

      {orderTable} 
    </div>;
  },
};
