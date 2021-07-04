import { node_windows_x64 as nw } from "../";

nw.registerSymbol("a", 2);

setTimeout(() => {
  console.log(nw.getAddress("1 + a"));

  nw["user32.messageboxa"](0, "a", "b", 0);
}, 2000);
