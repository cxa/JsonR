open Js_result;

let flat_map f r =>
  switch r {
  | Ok a => f a
  | Error r => Error r
  };

let map f r =>
  switch r {
  | Ok a => Ok (f a)
  | Error r => Error r
  };

let to_result f e o =>
  switch o {
  | Some v => Ok (f v)
  | _ => Error e
  };

let id x => x;

let parse_result json_str =>
  try (Ok (Js_json.parseExn json_str)) {
  | _ => Error "bs-json-util: Invalid JSON source"
  };

let member keypath result => {
  let to_result json key =>
    switch (Js_json.reifyType json) {
    | (Js_json.Object, value) =>
      switch (Js.Dict.get value key) {
      | Some v => Ok v
      | _ => Error {j|bs-json-util: value for $(key) does not exist |j}
      }
    | _ => Error {j|bs-json-util: value for $(key) not an object|j}
    };
  let is_ok r =>
    switch r {
    | Ok _ => true
    | _ => false
    };
  let f json => {
    let keys = Js_string.split "." keypath;
    let i = ref 0;
    let maxIdx = Array.length keys - 1;
    let r = ref (to_result json keys.(!i));
    while (!i < maxIdx && is_ok !r) {
      incr i;
      r := flat_map (fun j => to_result j keys.(!i)) !r
    };
    !r
  };
  flat_map f result
};

let to_bool r => {
  let f j => to_result Js.to_bool "bs-json-util: value is not a boolean" (Js_json.decodeBoolean j);
  flat_map f r
};

let to_float r => {
  let f j => to_result id "bs-json-util: value is not a number" (Js_json.decodeNumber j);
  flat_map f r
};

let to_int r => map int_of_float (to_float r);

let to_string r => {
  let f j => to_result id "bs-json-util: value is not a string" (Js_json.decodeString j);
  flat_map f r
};

let to_array r => {
  let f j => to_result id "bs-json-util: value is not an array" (Js_json.decodeArray j);
  flat_map f r
};

let to_dict r => {
  let f j => to_result id "bs-json-util: value is not an object" (Js_json.decodeObject j);
  flat_map f r
};
