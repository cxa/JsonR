module type Result = {
  type t 'good 'bad =
    | Ok 'good
    | Error 'bad;
};

module Impl (R: Result) => {
  type error =
    | InvalidJsonSource string
    | KeyNotExisted string
    | WrongVauleType string
    | Context string
  [@@bs.deriving {accessors: accessors}];
  let string_of_error =
    fun
    | InvalidJsonSource s
    | KeyNotExisted s
    | WrongVauleType s
    | Context s => s;
  let flat_map f r =>
    switch r {
    | R.Ok a => f a
    | R.Error r => R.Error r
    };
  let map f r =>
    switch r {
    | R.Ok a => R.Ok (f a)
    | R.Error r => R.Error r
    };
  let to_result f e o =>
    switch o {
    | Some v => R.Ok (f v)
    | _ => R.Error e
    };
  let id x => x;
  let parse_string json_str =>
    try (R.Ok (Js_json.parseExn json_str)) {
    | _ => R.Error (InvalidJsonSource "bs-json-util: Invalid JSON source")
    };
  let member keypath result => {
    let to_result json key =>
      switch (Js_json.classify json) {
      | JSONObject value =>
        switch (Js.Dict.get value key) {
        | Some v => R.Ok v
        | _ => R.Error (KeyNotExisted {j|bs-json-util: value for $(key) does not exist |j})
        }
      | _ => R.Error (KeyNotExisted {j|bs-json-util: value for $(key) not an object|j})
      };
    let is_Ok r =>
      switch r {
      | R.Ok _ => true
      | _ => false
      };
    let f json => {
      let keys = Js_string.split "." keypath;
      let i = ref 0;
      let maxIdx = Array.length keys - 1;
      let r = ref (to_result json keys.(!i));
      while (!i < maxIdx && is_Ok !r) {
        incr i;
        r := flat_map (fun j => to_result j keys.(!i)) !r
      };
      !r
    };
    flat_map f result
  };
  let is_null json =>
    switch (Js_json.classify json) {
    | Js_json.JSONNull => true
    | _ => false
    };
  let bool_for keypath r => {
    let f j =>
      to_result
        Js.to_bool
        (WrongVauleType {j|bs-json-util: value for `$(keypath)` is not a boolean|j})
        (Js_json.decodeBoolean j);
    r |> member keypath |> flat_map f
  };
  let float_for keypath r => {
    let f j =>
      to_result
        id
        (WrongVauleType {j|bs-json-util: value for `$(keypath)` is not a number|j})
        (Js_json.decodeNumber j);
    r |> member keypath |> flat_map f
  };
  let int_for keypath r => map int_of_float (float_for keypath r);
  let string_for keypath r => {
    let f j =>
      to_result
        id
        (WrongVauleType {j|bs-json-util: value for `$(keypath)` is not a string|j})
        (Js_json.decodeString j);
    r |> member keypath |> flat_map f
  };
  let array_for keypath r => {
    let f j =>
      to_result
        id
        (WrongVauleType {j|bs-json-util: value for `$(keypath)` is not an array|j})
        (Js_json.decodeArray j);
    r |> member keypath |> flat_map f
  };
  let dict_for keypath r => {
    let f j =>
      to_result
        id
        (WrongVauleType {j|bs-json-util: value for `$(keypath)` is not an object|j})
        (Js_json.decodeObject j);
    r |> member keypath |> flat_map f
  };
  let to_bool r => {
    let f j =>
      to_result
        Js.to_bool
        (WrongVauleType "bs-json-util: value is not a boolean")
        (Js_json.decodeBoolean j);
    flat_map f r
  };
  let to_float r => {
    let f j =>
      to_result id (WrongVauleType "bs-json-util: value is not a number") (Js_json.decodeNumber j);
    flat_map f r
  };
  let to_int r => map int_of_float (to_float r);
  let to_string r => {
    let f j =>
      to_result id (WrongVauleType "bs-json-util: value is not a string") (Js_json.decodeString j);
    flat_map f r
  };
  let to_array r => {
    let f j =>
      to_result id (WrongVauleType "bs-json-util: value is not an array") (Js_json.decodeArray j);
    flat_map f r
  };
  let to_dict r => {
    let f j =>
      to_result
        id (WrongVauleType "bs-json-util: value is not an object") (Js_json.decodeObject j);
    flat_map f r
  };
};

module Json = Impl Js_result;
