[%bs.raw {|require('./OperandButton.css')|}];

[@react.component]
let make = (~number, ~onClick) => {
  let className = "operand-button " ++ "_type_" ++ number;

  <Button className theme="light" onClick={_evt => onClick(number)}>
    number
  </Button>;
};