import { node_windows_x64 as nw } from "../";

const t = nw.createTargetWithName("Tutorial-i386.exe");
if (t.pid && t.hProcess) {
  const addrs = t.moduleScan("? 83 AC 04 00 00");
  console.log(addrs);
}
