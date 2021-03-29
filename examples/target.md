```js
const t = new nw.Target("game2.exe");
if (t.pid && t.hProcess) {
  console.log(t.name);
  console.log(t.pid);
  console.log(t.hProcess);
}
```

## setNop
```js
/**
define(address,"Tutorial-i386.exe"+2578F)
define(bytes,29 83 AC 04 00 00)

[ENABLE]
address:
  db 90 90 90 90 90 90

[DISABLE]
address:
  db bytes
 
  */

const t = new nw.Target("Tutorial-i386.exe");
if (t.pid && t.hProcess) {

  const address = nw.getAddress(`"Tutorial-i386.exe"+2578F`, t.hProcess);
  const handle = t.setNop(address, 6);
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
```