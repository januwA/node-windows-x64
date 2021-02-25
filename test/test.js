const nw = require("../build/Release/node-windows-x64");

const strMem = nw.mem_alloc(100);
nw.mem_write_str(strMem, "node-windows-x64");

const addr = nw.mem_alloc(1024);
nw.registerSymbol("newmem", addr);

nw.mem_write_dword("newmem", 1);
nw.mem_write_dword("newmem+4", 2);
nw.mem_write_qword("newmem+8", strMem);

console.log(nw.mem_read_dword("newmem"));   // 1
console.log(nw.mem_read_dword("newmem+4")); //2
console.log(nw.mem_read_str("[newmem+8]")); // node-windows-x64


nw.mem_free(strMem);
nw.mem_free("newmem");
nw.unregisterSymbol("newmem");