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

## win32 gui
```js
WS_OVERLAPPEDWINDOW =
  0x00000000 | 0x00c00000 | 0x00080000 | 0x00040000 | 0x00020000 | 0x00010000;
BS_PUSHBUTTON = 0x00000000;
WS_CHILD = 0x40000000;
WS_VISIBLE = 0x10000000;
WM_COMMAND = 0x0111;


const className = "Node Win32 Gui";
const windowName = "window caption";
const btnid = 10;
const buttonStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

const wui = new nw.Win32Gui(className, windowName, {
  x: 100,
  y: 100,
  width: 600,
  height: 400,
  style: WS_OVERLAPPEDWINDOW,
});


if (wui.initRegisterClass() && wui.initWindow()) {

  // create a button
  wui.createWindow("button", "click me", buttonStyle, 0, 0, 100, 50, btnid);

  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const wmId = wParam & 0xffff;
    switch (message) {
      case WM_COMMAND:
        if (wmId === btnid) {
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