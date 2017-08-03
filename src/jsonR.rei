module type Result = {
  type t 'good 'bad =
    | Ok 'good
    | Error 'bad;
};

module Impl:
  (R: Result) =>
  {
    type error =
      | InvalidJsonSource string
      | KeyNotExisted string
      | WrongVauleType string
      | Context string;
    let invalidJsonSource: string => error;
    let keyNotExisted: string => error;
    let wrongVauleType: string => error;
    let context: string => error;
    let string_of_error: error => string;
    let parse_result: string => R.t Js_json.t error;
    let member: Js_string.t => R.t Js_json.t error => R.t Js_json.t error;
    let is_null: Js_json.t => bool;
    let bool_for: Js_string.t => R.t Js_json.t error => R.t bool error;
    let float_for: Js_string.t => R.t Js_json.t error => R.t float error;
    let int_for: Js_string.t => R.t Js_json.t error => R.t int error;
    let string_for: Js_string.t => R.t Js_json.t error => R.t Js_string.t error;
    let array_for: Js_string.t => R.t Js_json.t error => R.t (array Js_json.t) error;
    let dict_for: Js_string.t => R.t Js_json.t error => R.t (Js_dict.t Js_json.t) error;
    let to_bool: R.t Js_json.t error => R.t bool error;
    let to_float: R.t Js_json.t error => R.t float error;
    let to_int: R.t Js_json.t error => R.t int error;
    let to_string: R.t Js_json.t error => R.t Js_string.t error;
    let to_array: R.t Js_json.t error => R.t (array Js_json.t) error;
    let to_dict: R.t Js_json.t error => R.t (Js_dict.t Js_json.t) error;
  };

module Json: {
  type error =
    Impl(Js_result).error =
      | InvalidJsonSource string | KeyNotExisted string | WrongVauleType string | Context string;
  let invalidJsonSource: string => error;
  let keyNotExisted: string => error;
  let wrongVauleType: string => error;
  let context: string => error;
  let string_of_error: error => string;
  let parse_result: string => Js_result.t Js_json.t error;
  let member: Js_string.t => Js_result.t Js_json.t error => Js_result.t Js_json.t error;
  let is_null: Js_json.t => bool;
  let bool_for: Js_string.t => Js_result.t Js_json.t error => Js_result.t bool error;
  let float_for: Js_string.t => Js_result.t Js_json.t error => Js_result.t float error;
  let int_for: Js_string.t => Js_result.t Js_json.t error => Js_result.t int error;
  let string_for: Js_string.t => Js_result.t Js_json.t error => Js_result.t Js_string.t error;
  let array_for: Js_string.t => Js_result.t Js_json.t error => Js_result.t (array Js_json.t) error;
  let dict_for:
    Js_string.t => Js_result.t Js_json.t error => Js_result.t (Js_dict.t Js_json.t) error;
  let to_bool: Js_result.t Js_json.t error => Js_result.t bool error;
  let to_float: Js_result.t Js_json.t error => Js_result.t float error;
  let to_int: Js_result.t Js_json.t error => Js_result.t int error;
  let to_string: Js_result.t Js_json.t error => Js_result.t Js_string.t error;
  let to_array: Js_result.t Js_json.t error => Js_result.t (array Js_json.t) error;
  let to_dict: Js_result.t Js_json.t error => Js_result.t (Js_dict.t Js_json.t) error;
};
