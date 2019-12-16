open Config;
open Belt;

/**
 * Convert array of symbols to string
 *
 * @example
 * symbolsToString(["1", "2", ".", "3"]) // "12.3"
 */
let symbolsToString = symbols =>
  List.(
    length(symbols) === 0
      ? "0" : symbols->reduce("", (acc, symbol) => acc ++ symbol)
  );

module Math = {
  let calc = (a, b, operator) => {
    let floatA = float_of_string(a);
    let floatB = float_of_string(b);

    switch (operator) {
    | Some("-") => floatA -. floatB
    | Some("/") => floatA /. floatB
    | Some("*") => floatA *. floatB
    | Some("+")
    | None
    | _ => floatA +. floatB
    };
  };
};

/**
 * Check if the symbol is one of possible operands
 */
let isSymbolOperand = s =>
  s === "." || List.(buttons.numbers->has(s, (a, b) => a === b));

module String = {
  let isNotEmpty = string => String.length(string) > 0;

  // 0x -> x
  // .x -> x
  let normalize = string =>
    string |> Js.String.replaceByRe([%re "/^[0.]+/g"], "");
};