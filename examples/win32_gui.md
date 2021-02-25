
## Use Win32 gui example
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

## mosue dbclick

只有具有CS_DBLCLKS样式的窗口才能接收WM_LBUTTONDBLCLK消息.

https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input-notifications

```js
nw.globalDefine();

wui.messageLoop((hWnd, message, wParam, lParam) => {
  const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
  const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

  const x = ll,
    y = lh,
    CTRL = (wParam & MK_CONTROL) !== 0,
    SHIFT = (wParam & MK_SHIFT) !== 0,
    Back = (wParam & MK_XBUTTON1) !== 0,
    Go = (wParam & MK_XBUTTON2) !== 0;

  switch (message) {
    case WM_LBUTTONDBLCLK:
      console.log(
        "dbclick: x: %d, y: %d, CTRL:%o, SHIFT: %o, Go: %o, Back: %o",
        x, y, CTRL, SHIFT, Go, Back
      );
      break;
    default:
      break;
  }
});
```


## keyup
```js
switch (message) {
  case WM_KEYUP:
    console.log("keyup", wParam, String.fromCharCode(wParam));
    break;
  default:
    break;
}
```

## keydown
```js
switch (message) {
  case WM_KEYDOWN:
    console.log("keydown", wParam, String.fromCharCode(wParam));
    break;
  default:
    break;
}
```

```js
switch (message) {
  case WM_KEYDOWN:
    switch (wParam) {
      case VK_LEFT:
        console.log("left");
        break;
      case VK_RIGHT:
        console.log("right");
        break;
      case VK_UP:
        console.log("up");
        break;
      case VK_DOWN:
        console.log("down");
        break;
      default:
        break;
    }
    break;
  default:
    break;
}
```


## char

如果想区分大小写，可以用char

```js
switch (message) {
  case WM_CHAR:
    console.log("char", wParam, String.fromCharCode(wParam));
    break;
  default:
    break;
}
```

## system down

alt+key

https://docs.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

```js
switch (message) {
  case WM_SYSKEYDOWN:
    console.log("system down", wParam, String.fromCharCode(wParam));
    break;
  default:
    break;
}
```


## button,checkbox,radio
```js
wui.button({
  id: 1,
  windowName: "push button",
});

wui.radio({
  id: 2,
  windowName: "radio 1",
  y: 50,
});

wui.checkbox({
  id: 3,
  windowName: "checkbox 1",
  y: 100,
});

wui.messageLoop((hWnd, message, wParam, lParam) => {
  const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
  const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

  switch (message) {
    case WM_COMMAND:
      const id = wl;
      const hwnd = lParam;
      
      switch (id) {
        case 1:
          if (wh == BN_CLICKED) console.log("click push button");
          break;
        case 2:
          if (wh == BN_CLICKED) console.log("click radio");
          break;
        case 3:
          if (wh == BN_CLICKED)
            console.log(
              "click checkbox: checkend: %o",
              // nw.SendMessageA(hwnd, BM_GETCHECK, 0, 0) === BST_CHECKED
              nw.Win32Gui.getCheck(hwnd)
            );
          break;
      }

      break;
  }
});
```