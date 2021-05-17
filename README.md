## node-windows-x64

 Provides some low-level APIs

 > Only tested on Windows 10 and Intel 64-bit cpu and vs2019

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

const wui = new nw.Win32Gui(className, windowName, {
  x: 100,
  y: 100,
  width: 600,
  height: 400,
  style: WS_OVERLAPPEDWINDOW,
});

if (wui.initRegisterClass() && wui.initWindow()) {

  // create a button
  wui.button({
    id: 1,
    windowName: "click me",
    events: {
      click() {
        console.log('button clicked.');
      },
    },
  });

  wui.messageLoop((hWnd, message, wParam, lParam) => {});
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

## Target
```js
/**
define(address,"Tutorial-i386.exe"+2578F)
define(bytes,29 83 AC 04 00 00)

[ENABLE]
address:
  db 90 90 90 90 90 90

[DISABLE]
address:
  db bytes
 
*/

const t = nw.createTargetWithName("Tutorial-i386.exe");
if (t.pid && t.hProcess) {

  const address = nw.getAddress(`"Tutorial-i386.exe"+2578F`, t.hProcess);
  const handle = t.setNop(address, 6);
  console.log(handle);
  
  if (handle.bSuccess) {
    handle.enable();

    setTimeout(() => {
      handle.disable();

      // 如果不在使用handle，那么一定要调用delete函数
      handle.delete();
    }, 1000 * 10);
  }
  
}
```



# There are more examples under the "examples" file