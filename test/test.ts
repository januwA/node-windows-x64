import { node_windows_x64 as nw } from "../";

let r = nw.invoke({
  module: 'user32.dll',
  method: "SendMessageTimeoutW",
  args: [65822, 0x052c, 0, 0, 0x0000, 1000, 0],
});

console.log(r);
