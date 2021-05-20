import { node_windows_x64 as nw } from "../";

nw.registerSymbol("中文", 2);

console.log( nw.getAddress("中文+2") );
