module RR = ReasonReact;
  
let component = RR.statelessComponent("OrderItem");

let make = (~order: Shirt.Order.t, ~deleteFunction, ~editFunction, ~editing, _children) => {
  ...component,
      
  render: (_self) => {
    <tr className={editing? "editRow" : "normalRow"}>
      <td>{RR.string(string_of_int(order.quantity))}</td>
      <td>{RR.string(Shirt.Size.toString(order.size))}</td>
      <td>{RR.string(Shirt.Sleeve.toString(order.sleeve))}</td>
      <td>{RR.string(Shirt.Color.toString(order.color))}</td>
      <td>{RR.string(Shirt.Pattern.toString(order.pattern))}</td>
      <td>
        <button onClick={editFunction}>{RR.string("Edit")}</button>
        <button onClick={deleteFunction}>{RR.string("Delete")}</button>
      </td>
    </tr>
  }
};
