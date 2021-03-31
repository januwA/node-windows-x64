import { node_windows_x64 as nw } from "../";

console.log( nw.asmBytes(`
  mov eax,1
  ret
`) );

