## node-windows-x64

 Provides some low-level APIs

 > Only tested on Windows 10 and Intel 64-bit cpu and vs2019/vs2022

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

## Parameter types and return value types
```js
nw.invoke({
  method: 'dll1.fndll9',
  args: [4.67, 10],
  argsType: ['float', 'int'],
  retType: 'int'
});

nw.invoke({
  method: 'MessageBoxA',
  args: [0, "content", "title", 1],
  argsType: ['int', 'str', 'str', 'int'],
  retType: 'int'
});

nw.invoke({
  method: 'MessageBoxW',
  args: [0, "content", "title", 1],
  argsType: ['int', 'wstr', 'wstr', 'int'],
  retType: 'int'
});
```

## Callback function signature
```js
const result = nw.invoke({
  method: 'dll1.fndll1',
  args: [(...args) => {
    console.log(args); // [ -100, 100, -233, 10, 1.2200000286102295, 7.334, 'char*', 'wchar*' ]
    return 99.99;
  }],
  argsType: ['fn2(int,uint,int64,uintptr,float,double,str,wstr):float'],
  retType: 'float'
});
```
```c++
extern "C" __declspec(dllexport)  float fndll1(
  float (*cb)(int, uint32_t, int64_t, uintptr_t, float, double,const char*, const wchar_t*)
) 
{
	return cb(-100, 100, -233, 10, 1.22, 7.334, "char*", L"wchar*");
}
```


> There are more examples under the "examples" file
