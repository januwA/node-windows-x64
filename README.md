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

## invoke automatically manages the string
```js
nw.invoke({
  module: "user32.dll",
  method: "MessageBoxA",
  args: [0, "body", "title", 3],
});

nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});
```

## Proxy

The node_windows_x64 is proxied to map all non-existent attributes to the invoke function.

```js
nw.MessageBoxA(0, "body", "title", 3);

nw["user32.MessageBoxA"](0, "body", "title", 3);
```

The code above is actually

```js
target.invoke({
  method: "MessageBoxA",
  args: [0, "body", "title", 3],
});

target.invoke({
  method: "user32.MessageBoxA",
  args: [0, "body", "title", 3],
});
```

## Optional method parameter
```js
nw.invoke({
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});
```

## win32 gui
```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";
const btnid = 10;

const wui = new nw.Win32Gui(className, windowName, {
  x: 100,
  y: 100,
  width: 600,
  height: 400,
  style: WS_OVERLAPPEDWINDOW,
});

if (wui.initRegisterClass() && wui.initWindow()) {
  // create a button
  wui.createWindow({
    className: "button",
    windowName: "click me",
    style: WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    x: 0,
    y: 0,
    width: 100,
    height: 50,
    id: btnid,
  });

  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
    switch (message) {
      case WM_COMMAND:
        if (wl === btnid) {
          console.log("click button.");
        }
        break;

      default:
        break;
    }
  });
}
```

There are more examples under the "examples" file