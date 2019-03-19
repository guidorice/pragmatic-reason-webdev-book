/*
 * Bind to JavaScript require() function
 */
[@bs.val] external require : string => string = "";

/*
 * Require bird.png, cat.png, dog.png, and fish.png
 * from the images directory. There is also a file
 * named unknown.png for other species.
 */

require("../images/bird.png");
require("../images/cat.png");
require("../images/dog.png");
require("../images/fish.png");
require("../images/unknown.png");

let component = ReasonReact.statelessComponent("Animal");

let animalSectionStyle = ReactDOMRe.Style.make(
  ~display="inline-block",
  ~textAlign="center",
  ()
);

let picture = species => {
  switch(species) {
    | "bird" => "bird.png"
    | "cat" => "cat.png"
    | "dog" => "dog.png"
    | "fish" => "fish.png"
    | _ => "unknown.png"
  }
}

/*
 * In the `<img>` element, the `src` pathname 
 * is relative to the `build` directory. Webpack
 * will put the `images` directory at the same
 * level as the `index.html` file, so we do
 * not want to use `../` here.
 * 
 * The style for this <div> in (in CSS)
 *    {
 *      display: inline-block,
 *      text-align: center
 *    }
 * 
 * You might want to create a function that generates the
 * src="" attribute so that species that don’t have pictures
 * use the "unknown.png" image.
 * 
 */
let make = (~species, ~name, _children) => {
  ...component,
  render: _self =>
    <div style={animalSectionStyle}>
      <img src={"images/" ++ picture(species)} />
      <span><br /></span>
      {ReasonReact.string(name)}
    </div>,
};
