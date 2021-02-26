import { node_windows_x64 as nw } from "../";

nw.globalDefine();

const className = "Node Win32 Gui";
const windowName = "window caption";

const wui = new nw.Win32Gui(className, windowName);

if (wui.initRegisterClass() && wui.initWindow()) {
  wui.button({
    id: 1,
    windowName: "click me",
    events: {
      // click() {
      //   console.log(2);
      // },
      keydown() {},
    },
  });

  wui.messageLoop();
}
