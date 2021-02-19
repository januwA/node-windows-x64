const nw = require("../build/Release/node-windows-x64");
const assert = require("assert");
// console.log(addon);

WM_IME_CHAR = 0x0286
let text = "hi!";
let hWnd = 0x0006063E;

for (const t of text) {
  let wParam = t.charCodeAt(0)
  let lParam = t.charCodeAt(0)
  nw.sendMessage( hWnd, WM_IME_CHAR, wParam, lParam )
}