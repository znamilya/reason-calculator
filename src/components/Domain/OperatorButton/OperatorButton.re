[%bs.raw {|require('./OperatorButton.css')|}];

let operatorToCssModirier = operator =>
  switch (operator) {
  | "+" => "plus"
  | "-" => "minus"
  | "*" => "multiply"
  | "/" => "divide"
  | "=" => "equals"
  | _ => ""
  };

[@react.component]
let make = (~action, ~onClick) => {
  <Button
    className={
      "operator-button " ++ "_type_" ++ operatorToCssModirier(action)
    }
    theme="dark"
    onClick={_evt => onClick(action)}>
    action
  </Button>;
};