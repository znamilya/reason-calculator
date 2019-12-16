[%bs.raw {|require('./Buttons.css')|}];

open Config;

[@react.component]
let make = (~onNumberType, ~onActionType, ~onResult, ~onReset) => {
  <div className="buttons">
    {buttons.numbers
     |> List.map(number =>
          <OperandButton number onClick=onNumberType key=number />
        )
     |> Array.of_list
     |> ReasonReact.array}
    // Basic Actions
    {buttons.basicActions
     |> List.map(action =>
          <OperatorButton
            action
            onClick={action === "=" ? onResult : onActionType}
            key=action
          />
        )
     |> Array.of_list
     |> ReasonReact.array}
    <Button className="dot-button" onClick={_evt => onNumberType(".")}>
      "."
    </Button>
    <Button className="reset-button" theme="dark" onClick={_evt => onReset()}>
      "C"
    </Button>
  </div>;
};