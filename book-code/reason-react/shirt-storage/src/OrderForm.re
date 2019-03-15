let toInt = (s:string): option(int) => {
  switch (int_of_string(s)) {
    | result => Some(result)
    | exception(Failure("int_of_string")) => None
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
  editingNumber: option(int)
};

type action =
  | Enter(Shirt.Order.t)
  | ChangeQty(string)
  | ChangeSize(string)
  | ChangeSleeve(string)
  | ChangeColor(string)
  | ChangePattern(string)
  | Delete(Shirt.Order.t)
  | Edit(Shirt.Order.t)
  | MissingData;

let encodeState = (s: state): Js.Json.t => {
  Json.Encode.object_([
    ("qtyStr", Json.Encode.string(s.qtyStr)),
    ("sizeStr", Json.Encode.string(s.sizeStr)),
    ("sleeveStr", Json.Encode.string(s.sleeveStr)),
    ("colorStr", Json.Encode.string(s.colorStr)),
    ("patternStr", Json.Encode.string(s.patternStr)),
    ("nextOrderNumber", Json.Encode.int(s.nextOrderNumber)),
    ("orders", Json.Encode.array(Shirt.Order.encodeJson, s.orders)),
    ("errorText", Json.Encode.string(s.errorText)),
    ("editingNumber", switch (s.editingNumber) {
      | Some(n) => Json.Encode.int(n)
      | None => Json.Encode.int(-1)
      })
  ]);
};

let decodeState = (json: Js.Json.t): state => {
  {
    qtyStr: Json.Decode.field("qtyStr", Json.Decode.string, json),
    sizeStr: Json.Decode.field("sizeStr", Json.Decode.string, json),
    sleeveStr: Json.Decode.field("sleeveStr", Json.Decode.string, json),
    colorStr: Json.Decode.field("colorStr", Json.Decode.string, json),
    patternStr: Json.Decode.field("patternStr", Json.Decode.string, json),
    nextOrderNumber: Json.Decode.field("nextOrderNumber", Json.Decode.int,
      json),
    orders: Json.Decode.field("orders",
      Json.Decode.array(Shirt.Order.decodeJson), json),
    errorText: Json.Decode.field("errorText", Json.Decode.string, json),
    editingNumber: {
      let optN = (Json.Decode.field("editingNumber", Json.Decode.int, json));
      switch (optN) {
        | -1 => None
        | n => Some(n)
      }
    }
  }
};

let localStorageKey = "shirt-orders";

let storeStateLocally = theState => {
  let jsState = encodeState(theState);
  Dom.Storage.setItem(localStorageKey,
    Js.Json.stringify(jsState), Dom.Storage.localStorage);
};

let getStoredState = () => {
  let neutralState: state = {
    qtyStr: "",
    sizeStr: "",
    sleeveStr: "",
    colorStr: "",
    patternStr: "",
    orders: [| |],
    nextOrderNumber: 1,
    errorText: "",
    editingNumber: None
  };
  let optItem = Dom.Storage.getItem(localStorageKey,
    Dom.Storage.localStorage);
  switch (optItem) {
    | Some(jsonStr) => 
        switch (Js.Json.parseExn(jsonStr)) {
          | result => decodeState(result)
          | exception(_) => neutralState
        }
    | None => neutralState
  }
};

let makeSelect = (label: string, choices: array(string),
                  value: string, changeFcn) => {
  let makeOptionElement = (value: string) => {
    <option key={value} value={value}>{ReasonReact.string(value)}</option>
  };
  
  let menuOptionElements = 
    Belt.Array.concat(
      [|<option key="" value="">{ReasonReact.string(label)}</option>|],
      Belt.Array.map(choices, makeOptionElement));

    <span className="item">
      <select value={value} onChange={changeFcn}>
        {ReasonReact.array(menuOptionElements)}
      </select>
    </span>
};

let setQty = (order: Shirt.Order.t, qty: int): Shirt.Order.t => {
  {...order, quantity: qty};
};

let setSize = (order: Shirt.Order.t, newSize: Shirt.Size.t): Shirt.Order.t => {
  {...order, size: newSize}
};

let setSleeve = (order: Shirt.Order.t, newSleeve: Shirt.Sleeve.t): Shirt.Order.t => {
  {...order, sleeve: newSleeve}
};

let setColor = (order: Shirt.Order.t, newColor: Shirt.Color.t): Shirt.Order.t => {
  {...order, color: newColor}
};

let setPattern = (order: Shirt.Order.t, newPattern: Shirt.Pattern.t): Shirt.Order.t => {
  {...order, pattern: newPattern}
};

let map2 = (optA: option('a), optB: option('b), f: ('a, 'b) => 'c): option('c) => {
  switch (optA, optB) {
    | (Some(a), Some(b)) => Some(f(a, b))
    | (_, _) => None
  }
};

let createOrder = (state) : option(Shirt.Order.t) => {
  /* Set up a neutral record */
  let result: option(Shirt.Order.t) = Some({
      orderNumber: state.nextOrderNumber,
      quantity: 0,
      size: Shirt.Size.Medium,
      sleeve: Shirt.Sleeve.Long,
      color: Shirt.Color.White,
      pattern: Shirt.Pattern.Solid});
  map2(result, toInt(state.qtyStr), setQty)
  -> map2(_, Shirt.Size.fromString(state.sizeStr), setSize)
  -> map2(_, Shirt.Sleeve.fromString(state.sleeveStr), setSleeve)
  -> map2(_, Shirt.Color.fromString(state.colorStr), setColor)
  -> map2(_, Shirt.Pattern.fromString(state.patternStr), setPattern)
};

let component = ReasonReact.reducerComponent("OrderForm");

let make = (_children) => {
  ...component,

  initialState: getStoredState,

  /* State transitions */
  reducer: (action, state:state) =>
    switch (action) {
    | Enter(order) => {
        let n = Belt.Option.getWithDefault(toInt(state.qtyStr), 0);
        if (n > 0 && n <= 100) {
          ReasonReact.UpdateWithSideEffects({
            /* clear out the form fields */
            qtyStr: "",
            sizeStr: "",
            sleeveStr: "",
            colorStr: "",
            patternStr: "",
            orders: switch (state.editingNumber) {
              | Some(n) => Belt.Array.map(state.orders,
                (item) => {(item.orderNumber == n) ? order : item})
              | None => Belt.Array.concat(state.orders, [|order|])
            },
            nextOrderNumber: state.nextOrderNumber + 1,
            editingNumber: None,
            errorText: ""
          },
          (self) => storeStateLocally(self.state));
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
        ReasonReact.UpdateWithSideEffects({
        ...state,
          orders: Belt.Array.keep(state.orders,
            (item) => (item.orderNumber != order.orderNumber))},
          (self) => storeStateLocally(self.state))
      }
    | Edit(order) => {
        ReasonReact.Update({...state,
          /* set the strings here */
          qtyStr: string_of_int(order.quantity),
          sizeStr: Shirt.Size.toString(order.size),
          sleeveStr: Shirt.Sleeve.toString(order.sleeve),
          colorStr: Shirt.Color.toString(order.color),
          patternStr: Shirt.Pattern.toString(order.pattern),
          editingNumber: Some(order.orderNumber)
        })
      }
    | MissingData => {
        ReasonReact.Update({...state,
          errorText: "Please fill in all fields."})
      }
    },

  render: self => {

    let orderItems = Belt.Array.map(self.state.orders, (order) => {
        let beingEdited = switch (self.state.editingNumber) {
          | Some(n) => n == order.orderNumber
          | None => false
        };
        <OrderItem key={string_of_int(order.orderNumber)}
          order={order} deleteFunction=(_event => self.send(Delete(order)))
          editFunction=(_event => self.send(Edit(order)))
          editing={beingEdited}/>
        });

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
              let optOrder = createOrder(self.state);
              switch (optOrder) {
                | Some(order) => self.send(Enter(order))
                | None => self.send(MissingData)
              }})>
            {ReasonReact.string((self.state.editingNumber == None) ? "Add" : "Update")}
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

