import { node_windows_x64 as nw } from "../";
nw.globalDefine();

let WM_ShellHook = 0;
const wui = new nw.Win32Gui("Node Win32 Gui", "window caption");

if (wui.initRegisterClass() && wui.initWindow()) {
  if (nw["user32.RegisterShellHookWindow"](wui.hwnd)) {
    WM_ShellHook = nw["user32.RegisterWindowMessageA"]("SHELLHOOK");
    if (WM_ShellHook === 0) {
      console.log("RegisterWindowMessageA fail.");
    }
  } else {
    console.log("RegisterShellHookWindow fail.");
  }

  wui.messageLoop((hWnd, message, wParam, lParam) => {
    switch (message) {
      case WM_ShellHook:
        switch (wParam) {
          case HSHELL_WINDOWCREATED:
            console.log("WINDOWCREATED");
            break;

          case HSHELL_WINDOWDESTROYED:
            console.log("WINDOWDESTROYED");
            break;

          case HSHELL_ACTIVATESHELLWINDOW:
            console.log("ACTIVATESHELLWINDOW");
            break;

          default:
            break;
        }
        break;

      default:
        break;
    }
  });
}
