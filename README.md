## node-windows-x64

 Provides some low-level APIs

 > Only tested on Windows 10 and Intel 64-bit cpu

 ## Install
 ```sh
 $ npm i node-windows-x64
 ```

## Example
 ```js
//  import { node_windows_x64 as nw } from "node-windows-x64";
 const { node_windows_x64: nw } = require("node-windows-x64");

const newmem = nw.mem_alloc(1024);

let title = "xxx";
let body = "hello world";
let lpTitle = newmem;
let lpBody  = newmem + 100;

nw.mem_write_str(lpTitle, title);
nw.mem_write_str(lpBody, body);

let r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxA",
  args: [0, lpBody, lpTitle, 1],
});
console.log("result: ", r);

nw.mem_free(newmem);
```

## Callback

```js
let r = nw.invoke({
  module: "user32.dll",
  method: "EnumWindows",
  args: [
    (hwnd, param) => {
      console.log("hwnd: %d, param: %d", hwnd, param);
      return true;
    },
    10,
  ],
});

console.log("result: ", r);
```

## View all api
```js
const { node_windows_x64: nw } = require("node-windows-x64");
console.log(nw);
```

## invoke automatically manages the string
```js
nw.invoke({
  module: "user32.dll",
  method: "MessageBoxWA",
  args: [0, "body", "title", 3],
});

nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});
```

There are more examples under the "examples" file