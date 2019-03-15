/*
 * Bind to JavaScript require() function
 */
[@bs.val] external require : string => string = "";

/*
 * Require bird.png, cat.png, dog.png, and fish.png
 * from the images directory. There is also a file
 * named unknown.png for other species.
 */

let component = ReasonReact.statelessComponent("Animal");

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
    <div> /* Your style goes in this tag */
      <img src=""/> /* Your image source goes in this element */
      <span><br /></span>
      /* Display animal name here */
    </div>,
};
