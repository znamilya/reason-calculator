[%bs.raw {|require('./Screen.css')|}];

[@react.component]
let make = (~value) => {
  <div className="screen"> {React.string(value)} </div>;
};