module type Result = {
  type t 'good 'bad =
    | Ok 'good
    | Error 'bad;
};

module Impl:
  (R: Result) =>
  {
    let parse_result: string => R.t Js_json.t string;
    let member: Js_string.t => R.t Js_json.t string => R.t Js_json.t string;
    let to_bool: R.t Js_json.t string => R.t bool string;
    let to_float: R.t Js_json.t string => R.t float string;
    let to_int: R.t Js_json.t string => R.t int string;
    let to_string: R.t Js_json.t string => R.t Js_string.t string;
    let to_array: R.t Js_json.t string => R.t (array Js_json.t) string;
    let to_dict: R.t Js_json.t string => R.t (Js_dict.t Js_json.t) string;
  };

module Json: {
  let parse_result: string => Js_result.t Js_json.t string;
  let member: Js_string.t => Js_result.t Js_json.t string => Js_result.t Js_json.t string;
  let to_bool: Js_result.t Js_json.t string => Js_result.t bool string;
  let to_float: Js_result.t Js_json.t string => Js_result.t float string;
  let to_int: Js_result.t Js_json.t string => Js_result.t int string;
  let to_string: Js_result.t Js_json.t string => Js_result.t Js_string.t string;
  let to_array: Js_result.t Js_json.t string => Js_result.t (array Js_json.t) string;
  let to_dict: Js_result.t Js_json.t string => Js_result.t (Js_dict.t Js_json.t) string;
};
