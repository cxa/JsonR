# JsonR

A BuckleScript lib for handling JSON in `Result` favor, written in [ReasonML](http://facebook.github.io/reason/).

## Usage

Add `json-r` to your project's dependencies by `yarn` or `npm`, And add it to `bs-dependencies` for `bsconfig.json`, e.g.

```json
{
    "name": "coolproj",
    "bs-dependencies": [
      "json-r"
    ]
}
```

### Basic example

```reason

open JsonR.Json;
open Js_result;

let json = parse_result json_source;

/* Access a field and its value, return a Js_result type */

let title = json |> string_for "title";

/* or more verbose */
let title = json |> member "title" |> to_string;


/* you can also pass key path */
let age = json |> int_for "author.age";

/ * or */
let age = json |> member "author.age" |> to_int;

switch age {
| Ok a => DoWhatYouWant a
| Error e => HeyWeCantParseOutTheAge_CheckTheErrorMessage e
};

```

You can open `__tests__/test.re` to view more examples.

### Advance usage

Need to use the another `Result` type such as `Containers.Result`? Just `Module Json = JsonR.Impl Containers.Result;`.

## LICENSE

MIT.
