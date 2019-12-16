[%bs.raw {|require('./App.css')|}];

open Config;
open Belt;

type action =
  | TypeNumber(string)
  | TypeOperator(string)
  | Result
  | Reset;

type state = {
  operand1: string,
  operand2: string,
  operator: option(string),
  justCalced: bool,
};

let defaultState = {
  operand1: "",
  operand2: "",
  operator: None,
  justCalced: false,
};

let reducer = (state, action: action) => {
  let {operand1, operand2, operator, justCalced} = state;

  let calc = (a, b, operator) =>
    Utils.Math.calc(a, b, operator) |> Js.Float.toString;

  let handleTypeNumber = number =>
    switch (operator, justCalced) {
    | (None, false) => {
        ...state,
        operand1: Utils.String.normalize(operand1 ++ number),
      }
    | (None, true) => {
        ...state,
        operand1: Utils.String.normalize(number),
        justCalced: false,
      }
    | (Some(operator), _) => {
        ...state,
        operand2: Utils.String.normalize(operand2 ++ number),
      }
    };

  let handleTypeOperator = nextOperator =>
    switch (
      Utils.String.isNotEmpty(operand1),
      Utils.String.isNotEmpty(operand2),
    ) {
    | (true, true) => {
        ...state,
        operand1: calc(operand1, operand2, operator),
        operand2: "",
        operator: Some(nextOperator),
      }
    | (true, false) => {...state, operator: Some(nextOperator)}
    | (false, _) => state
    };

  let handleResult = () => {
    switch (
      Utils.String.isNotEmpty(operand1),
      Utils.String.isNotEmpty(operand2),
      operator,
    ) {
    | (true, true, Some(operator)) => {
        operand1: calc(operand1, operand2, Some(operator)),
        operand2: "",
        operator: None,
        justCalced: true,
      }
    | (true, false, Some(operator)) => {
        operand1: calc(operand1, operand1, Some(operator)),
        operand2: "",
        operator: None,
        justCalced: true,
      }
    | _ => state
    };
  };

  switch (action) {
  | TypeNumber(number) => handleTypeNumber(number)
  | TypeOperator(operator) => handleTypeOperator(operator)
  | Result => handleResult()
  | Reset => defaultState
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, defaultState);

  let displayValue =
    switch (state.operand1, state.operand2) {
    | ("", "") => "0"
    | (operand1, "") => operand1
    | (_, operand2) => operand2
    };

  <div className="app">
    <Screen value=displayValue />
    <Buttons
      onNumberType={number => dispatch(TypeNumber(number))}
      onActionType={action => dispatch(TypeOperator(action))}
      onResult={action => dispatch(Result)}
      onReset={action => dispatch(Reset)}
    />
  </div>;
  // DEBUG INFO
  // <div> {React.string(state.operand1)} </div>
  // <br />
  // <div> {React.string(state.operand2)} </div>
  // <br />
  // <div>
  //   {React.string("Operator: ")}
  //   {switch (state.operator) {
  //    | None => <span />
  //    | Some(value) => <span> {React.string(value)} </span>
  //    }}
  // </div>
};