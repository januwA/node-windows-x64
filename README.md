## node-windows-x64

 Provides some low-level APIs

 > Only tested on Windows 10 and Intel 64-bit cpu

 ## Install
 ```sh
 $ npm i node-windows-x64
 ```

## Example
 ```js
// import { node_windows_x64 as nw } from "node-windows-x64";
 const { node_windows_x64: nw } = require("node-windows-x64");

nw.MessageBoxA(0, "body", "title", 3);
```

## Callback
```js
const r = nw["user32.EnumWindows"]((hwnd, param) => {
  console.log("hwnd: %d, param: %d", hwnd, param);
  return true;
}, 10);

console.log("result: ", r);
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

## Auto Asm
```js
const r = nw.aa(
  `
  inc rcx
  mov rax,rcx
  ret
`,
  1
);

console.log(r); // 2
```



# There are more examples under the "examples" file