open Jest;

open Expect;

open JsonR.Json;

let obj = {
  "title": "Real World OCaml",
  "tags": [|"functional programming", "ocaml", "algorithms"|],
  "pages": 450,
  "authors": [
    {"name": "Jason Hickey", "affiliation": "Google"},
    {"name": "Anil Madhavapeddy", "affiliation": "Cambridge"},
    {"name": "Yaron Minsky", "affiliation": "Jane Street"}
  ],
  "fortest": {"only": {"deep": Js.true_}},
  "is_online": Js.true_
};

let json = parse_string @@ Js.Json.stringify (Obj.magic obj);

let is_ok r =>
  switch r {
  | Js_result.Ok _ => true
  | _ => false
  };

let unsafe_ok r =>
  switch r {
  | Js_result.Ok a => a
  | Js_result.Error e => failwith (string_of_error e)
  };

let _ = {
  test "member_single_key" (fun () => expect (is_ok (member "title" json)) |> toEqual true);
  test
    "member_multiple_keys"
    (fun () => expect (is_ok (member "fortest.only.deep" json)) |> toEqual true);
  test
    "member_multiple_keys_value"
    (fun () => expect (unsafe_ok (member "fortest.only.deep" json |> to_bool)) |> toEqual true);
  test
    "member_invalid_single_key"
    (fun () => expect (is_ok (member "nonexist" json)) |> toEqual false);
  test
    "member_invalid_multiple_keys"
    (fun () => expect (is_ok (member "nonexist.a.b" json)) |> toEqual false);
  let is_online = member "is_online" json;
  test "to_bool" (fun () => expect (unsafe_ok (to_bool is_online)) |> toEqual true);
  let title = member "title" json;
  test "to_string" (fun () => expect (unsafe_ok (to_string title)) |> toEqual "Real World OCaml");
  let pages = member "pages" json;
  test "to_int" (fun () => expect (unsafe_ok (to_int pages)) |> toEqual 450);
  test "to_float" (fun () => expect (unsafe_ok (to_float pages)) |> toEqual 450.);
  let tags = member "tags" json;
  test "to_array" (fun () => expect (Array.length (unsafe_ok (to_array tags))) |> toEqual 3);
  let fortest = member "fortest" json;
  test
    "to_dict"
    (
      fun () =>
        expect (Js_option.isSome (Js.Dict.get (unsafe_ok (to_dict fortest)) "only")) |>
        toEqual true
    )
};
