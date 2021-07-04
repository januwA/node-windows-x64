import { node_windows_x64 as nw } from "../";

nw["LoadLibraryA"]("C:\\Users\\ajanuw\\Desktop\\Dll1\\x64\\Release\\Dll1.dll");

const pHello = nw.getAddress("Dll1.hello");

const floatSize = 4;
const mem = nw.alloc(3 * floatSize);
const pX = mem + floatSize * 0;
const pY = mem + floatSize * 1;
const pResult = mem + floatSize * 2;
nw.writeFloat(pX, 1.3);
nw.writeFloat(pY, 5.5);

nw.aa(
  `
  sub rsp,8
  mov [rsp],rcx

  sub rsp,32
  movss xmm0, [rcx]
  movss xmm1, [rcx+4]
  mov rax, 0x${pHello.toString(16)}
  call rax
  add rsp,32
  
  mov rcx,[rsp]
  movss [rcx+8],xmm0
  add rsp,8
  ret
`,
  mem
);
console.log(nw.readFloat(pResult));

nw.free(mem);
