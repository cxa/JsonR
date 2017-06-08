# bs-json-util

A BuckleScript lib for handling JSON, written in [ReasonML](http://facebook.github.io/reason/).

## Usage

Add `bs-json-util` to your project's dependencies by `yarn` or `npm`, And add it to `bs-dependencies` for `bsconfig.json`, e.g.

```json
{
    "name": "coolproj",
    "bs-dependencies": [
      "bs-json-util"
    ]
}
```

### Basic example

```reason

open JsonUtil;
open Js_result;

let json = parse_result json_source;

/* Access a field and its value, return a Js_result type */

let _ = member "title" json |> to_string;

/* you can also pass key path, this is our selling point :) */

let age = member "author.age" json |> to_int;

switch age {
| Ok a => DoWhatYouWant a
| Error e => HeyWeCantParseOutTheAge_CheckTheErrorMessage e
};

```

You can open `__tests__/test.re` to view more examples.

## LICENSE

MIT.
