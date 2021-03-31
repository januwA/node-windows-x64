## Auto Asm
```js
const r = nw.aa(
  `
  inc rcx
  mov rax,rcx
  ret
`,
  1
);

console.log(r); // 2
```


## asmBytes
```js
console.log( nw.asmBytes(`
  mov eax,1
  ret
`) ); // ArrayBuffer { [Uint8Contents]: <b8 01 00 00 00 c3>, byteLength: 6 }
```