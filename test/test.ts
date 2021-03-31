import { node_windows_x64 as nw } from "../";

/**
define(address,"Tutorial-i386.exe"+2578F)
define(bytes,29 83 AC 04 00 00)

[ENABLE]
assert(address,bytes)
alloc(newmem,$1000)

label(return)

newmem:
  sub [ebx+000004AC],0 // 83 AB AC040000 00
  jmp return

address:
  jmp newmem
  nop
return:

[DISABLE]

address:
  db bytes

dealloc(newmem)
  */

const t = nw.createTargetWithName("Tutorial-i386.exe");
if (t.pid && t.hProcess) {
  const address = nw.getAddress(`"Tutorial-i386.exe"+2578F`, t.hProcess);
  const handle = t.setHook(address, 6, `sub DWORD [ebx+0x4AC],0`);
  console.log(handle);

  if (handle.bSuccess) {
    handle.enable();

    setTimeout(() => {
      handle.disable();

      // 如果不在使用handle，那么一定要调用delete函数
      handle.delete();
    }, 1000 * 10);
  }
}
