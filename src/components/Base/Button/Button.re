[%bs.raw {|require('./Button.css')|}];

[@react.component]
let make = (~className="", ~theme="light", ~children, ~onClick) => {
  let className = "button " ++ "_theme_" ++ theme ++ " " ++ className;

  <button className onClick> {React.string(children)} </button>;
};