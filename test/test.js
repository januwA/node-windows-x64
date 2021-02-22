const nw = require("../build/Release/node-windows-x64");

const WS_OVERLAPPEDWINDOW =
  0x00000000 | 0x00c00000 | 0x00080000 | 0x00040000 | 0x00020000 | 0x00010000;
const BS_PUSHBUTTON = 0x00000000;
const WS_CHILD = 0x40000000;
const WS_VISIBLE = 0x10000000;
const WM_COMMAND = 0x0111;

const className = "Node Win32 Gui";
const windowName = "window caption";
const btnid = 10;
const buttonStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

const wui = new nw.Win32Gui(className, windowName, {
  x: 100,
  y: 100,
  width: 600,
  height: 400,
  style: WS_OVERLAPPEDWINDOW,
});

if (wui.initRegisterClass() && wui.initWindow()) {
  // create a button
  wui.createWindow("button", "click me", buttonStyle, 0, 0, 100, 50, btnid);

  wui.messageLoop((hWnd, message, wParam, lParam) => {
    const wmId = wParam & 0xffff;
    switch (message) {
      case WM_COMMAND:
        if (wmId === btnid) {
          console.log("click button.");
        }
        break;

      default:
        break;
    }
  });
}