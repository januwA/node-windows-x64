
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

## mouse dbclick

只有具有CS_DBLCLKS样式的窗口才能接收WM_LBUTTONDBLCLK消息.

https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input-notifications

```js
nw.globalDefine();

const wui = new nw.Win32Gui(className, windowName, {
  style: WS_OVERLAPPEDWINDOW,
});

if (wui.initRegisterClass() && wui.initWindow()) {
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
}
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
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  wui.button({
    id: 1,
    windowName: "push button",
  });

  wui.radio({
    id: 2,
    windowName: "radio 1",
    y: 50,
  });

  wui.radio({
    id: 3,
    windowName: "radio 2",
    x: 150,
    y: 50,
  });

  wui.checkbox({
    id: 4,
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
          case 3:
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
}
```

## static text
```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  wui.text({
    id: 1,
    windowName: "static texttttttttttttttttt...",
  });

  wui.text({
    id: 2,
    y: 100,
    windowName: "static texttttttttttttttttt...",
  });

  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
    const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

    switch (message) {
      case WM_CTLCOLORSTATIC:
        const hdc = wParam;
        const hwnd = lParam;
        const id = nw.GetWindowLongW(hwnd, GWLP_ID);
        if (id == 1) {
          // nw.SetTextColor(hdc, 0xff0000);
          nw.SetTextColor(hdc, nw.Win32Gui.rgb(0, 0, 255)); // text color
          nw.SetBkColor(hdc, nw.Win32Gui.rgb(0, 255, 0)); // text bgcolor
          return nw.GetStockObject(BLACK_BRUSH);
        }
        if (id == 2) {
          // nw.SetTextColor(hdc, 0xff0000);
          nw.SetTextColor(hdc, nw.Win32Gui.rgb(255, 0, 255)); // text color
          nw.SetBkColor(hdc, nw.Win32Gui.rgb(255, 255, 0)); // text bgcolor
          return nw.GetStockObject(BLACK_BRUSH);
        }
        break;
    }
  });
}
```

## input,textarea
```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  const sInputValue = nw.alloc(100);
  wui.input({
    id: 1,
    windowName: "password...",
    style: ES_PASSWORD,
  });

  wui.textarea({
    id: 2,
    y: 100,
    windowName: "text...",
  });
  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
    const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

    switch (message) {
      case WM_COMMAND:
        {
          const hwnd = lParam;
          const id = wl;
          const code = wh;
          if (code === EN_CHANGE) {
            if (id == 1) {
              nw.GetWindowTextA(hwnd, sInputValue, 100);
              console.log("input value change: ", nw.read_str(sInputValue));
            }
            if (id == 2) {
              console.log("textarea value change..");
            }
          }
        }
        break;
      case WM_CTLCOLOREDIT: {
        const hdc = wParam;
        const hwnd = lParam;
        const id = nw.GetWindowLongW(hwnd, GWLP_ID);
        if (id == 2) {
          // set textarea color
          nw.SetTextColor(hdc, nw.Win32Gui.rgb(255, 0, 0));
          nw.SetBkMode(hdc, 1);
          return nw.GetStockObject(WHITE_BRUSH);
        }
        break;
      }
    }
  });

  nw.free(sInputValue);
}
```

## listbox
```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  const hwnd = wui.listbox({
    id: 1,
    windowName: "listbox",
    style: LBS_MULTIPLESEL,
  });

  for (let i = 0; i < 20; i++) {
    nw.sendMessage(hwnd, LB_ADDSTRING, 0, "list " + i);
  }
  nw.sendMessage(hwnd, LB_INSERTSTRING, 1, "list insert");

  const buf = nw.alloc(100);
  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
    const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

    switch (message) {
      case WM_COMMAND:
        const hwnd = lParam;
        const id = wl;
        const code = wh;
        if (id === 1 && code === LBN_SELCHANGE) {
          const index = nw.sendMessage(hwnd, LB_GETCURSEL, 0, 0);
          nw.sendMessage(hwnd, LB_GETTEXT, index, buf);
          console.log("select change(%d): ", index, nw.read_str(buf));
        }
        break;
      case WM_CTLCOLORLISTBOX:
        {
          const hdc = wParam;
          const hwnd = lParam;
          const id = nw.GetWindowLongW(hwnd, GWLP_ID);
          if (id == 1) {
            nw.SetTextColor(hdc, nw.Win32Gui.rgb(255, 0, 0));
            nw.SetBkColor(hdc, nw.Win32Gui.rgb(0, 255, 0));
            return nw.GetStockObject(BLACK_BRUSH);
          }
        }
        break;
    }
  });

  nw.free(100);
}
```


## select
```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  const hwnd = wui.select({
    id: 1,
  });

  for (let i = 0; i < 10; i++) {
    nw.sendMessage(hwnd, CB_ADDSTRING, 0, "list " + i);
  }
  nw.sendMessage(hwnd, CB_INSERTSTRING, 1, "list insert");
  nw.sendMessage(hwnd, CB_SETCURSEL, 0, 0);

  const buf = nw.alloc(100);
  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const [wh, wl] = nw.Win32Gui.getHLMessage(wParam);
    const [lh, ll] = nw.Win32Gui.getHLMessage(lParam);

    switch (message) {
      case WM_COMMAND:
        const hwnd = lParam;
        const id = wl;
        const code = wh;
        if (id == 1 && code == CBN_SELCHANGE) {
          const index = nw.sendMessage(hwnd, CB_GETCURSEL, 0, 0);
          nw.sendMessage(hwnd, CB_GETLBTEXT, index, buf);
          console.log("select change(%d): ", index, nw.read_str(buf));
        }
        break;
    }
  });
  nw.free(100);
}
```

## groupbox

分组只是视觉上的

```js
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  wui.groupbox({
    id: 1,
    width: 300,
    height: 80,
    windowName: "group box",
  });

  wui.radio({
    id: 2,
    windowName: "radio 1",
    x: 10,
    y: 40,
    style: WS_GROUP,
  });

  wui.radio({
    id: 3,
    windowName: "radio 2",
    x: 120,
    y: 40,
  });

  wui.messageLoop();
}
```

## events
```ts
nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  wui.button({
    id: 1,
    windowName: "push button",
    events: {
      click: (
        hWnd: number,
        message: number,
        wParam: number,
        lParam: number
      ) => {
        console.log("click me");
      },
    },
  });

  wui.messageLoop();
}
```