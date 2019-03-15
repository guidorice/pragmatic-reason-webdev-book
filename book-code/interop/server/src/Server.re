let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:3000"
  };

let app = Express.express();
let server = Express.App.listen(app, ~port=3000, ~onListen, ());

[@bs.deriving abstract]
type options = {
  root: string,
};

Express.App.get(app, ~path="/", 
  Express.Middleware.from((_, _) => {
    Express.Response.sendFile("index.html", options(~root="./dist"));
  }
));

Express.App.get(app, ~path="/json") @@
  Express.Middleware.from((_, req) => {
    Express.Request.query(req)
    -> Js.Dict.unsafeGet("choice")
    -> Json.Decode.string
    -> Stats.processFile("orders.csv", _)
    -> Express.Response.sendJson;
  });

Express.App.get(app, ~path="/:filename") @@
Express.Middleware.from((_, req) => {
  Express.Request.params(req)
  -> Js.Dict.unsafeGet("filename")
  -> Json.Decode.string
  -> Express.Response.sendFile(options(~root="./dist"))
});








