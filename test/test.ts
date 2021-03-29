import { node_windows_x64 as nw } from "../";

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
