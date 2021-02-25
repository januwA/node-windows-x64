const { node_windows_x64: nw } = require("../index");

nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption 中文";

const wui = new nw.Win32Gui(className, windowName, {
  x: 100,
  y: 100,
  width: 600,
  height: 400,
  style: WS_OVERLAPPEDWINDOW,
});

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
}
