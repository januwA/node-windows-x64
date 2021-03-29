import { node_windows_x64 as nw } from "../";

const t = nw.createTargetWithName("Tutorial-i386.exe");

if (t.pid && t.hProcess) {
  console.log(t.name);
  console.log(t.pid);
  console.log(t.hProcess);
}
