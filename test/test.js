const { node_windows_x64: nw } = require("../");

function findChildWindow(hWndParent) {
  let hwinList = [];

  const res = nw['user32.EnumChildWindows'](hWndParent,
    (hwnd, lParam) => {
      console.log("EnumChildWindows:", hwnd, lParam);
      hwinList.push(hwnd);
      return true;
    },
    1);

  console.log("res", res);

  return hwinList;
}

const hwinList = findChildWindow(0x0003004a);
console.log(hwinList);
