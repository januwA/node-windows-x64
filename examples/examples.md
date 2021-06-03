## getProcessID
```js
nw.getProcessID()
```

## getCurrentProcess
```js
nw.getCurrentProcess()
```

## isKeyPressed
```js
VK_A = 65
nw.isKeyPressed(VK_A);
```

## keyDown and keyUp
```js
VK_A = 65
VK_B = 66
VK_C = 67

nw.keyDown(VK_A);
nw.keyUp(VK_A);

nw.keyDown(VK_B);
nw.keyUp(VK_B);

nw.keyDown(VK_C);
nw.keyUp(VK_C);
```

## doKeyPress
```js
VK_A = 65
VK_B = 66
VK_C = 67

nw.doKeyPress(VK_A);
nw.doKeyPress(VK_B);
nw.doKeyPress(VK_C);
```

## readFromClipboard
```js
console.log(nw.readFromClipboard());
```

## mouse_event
```js
nw.setMousePos(335, 742 )
nw.mouse_event(MOUSEEVENTF_LEFTDOWN)
nw.mouse_event(MOUSEEVENTF_LEFTUP)
```

## beep
```js
console.log( nw.beep(2000) );
```

## speak
```js
nw.speak("hello world");
console.log('done');
```

## sleep
```js
console.log('start');
nw.sleep(1000)
console.log('end');
```

## findWindow
```js
let hwnd = nw.findWindow("WTWindow", "Game");
l(hwnd);
```

## getWindowCaption
```js
let hwnd = nw.findWindow("WTWindow", "Game");
l(nw.getWindowCaption(hwnd)); // Game
```

## getWindowClassName
```js
let hwnd = nw.findWindow("WTWindow", "Game");
l(nw.getWindowClassName(hwnd)); // WTWindow
```

## getWindowProcessID
```js
let hwnd = nw.findWindow("WTWindow", "Game");
l(nw.getWindowProcessID(hwnd)); // { pid: 93088, tid: 83140 }
```

## getForegroundWindow
```js
l( nw.getWindowCaption( nw.getForegroundWindow()) );
```

## sendMessage
```js
WM_IME_CHAR = 0x0286
let text = "hello world";
let hWnd = 0x0018071E;

for (const t of text) {
  let wParam = t.charCodeAt(0)
  let lParam = t.charCodeAt(0)
  nw.sendMessage( hWnd, WM_IME_CHAR, wParam, lParam )
}
```

## globalDefine

调用后，将在global中设置大量变量

```js
nw.globalDefine();
console.log(VK_BACK);
```

## createThread
```ts
const hThread = nw.createThread(
  function (arg) {
    console.log(arg); // 10
  },
  10,
  0x00000004
);

setTimeout(() => {
  nw["Kernel32.ResumeThread"](hThread);
}, 2000);
```

## getAddress
```ts
nw.registerSymbol("中文", 1);
nw.registerSymbol("한글", 2);
nw.registerSymbol("ああさっそうとしている", 3);

 console.log( nw.getAddress("中文 + 한글 + ああさっそうとしている + 2") ); // 8
```