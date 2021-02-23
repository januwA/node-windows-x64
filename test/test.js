const nw = require("../build/Release/node-windows-x64");

let r = nw.invoke({
  module: "user32.dll",
  method: "EnumWindows",
  args: [
    (hwnd, param) => {
      console.log("hwnd: %d, param: %d", hwnd, param);
      return true;
    },
    10,
  ],
});
