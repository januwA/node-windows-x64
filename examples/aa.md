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

```js
const lpFloatVal = nw.alloc(8);
nw.writeFloat(lpFloatVal, 2.0);
nw.writeFloat(lpFloatVal + 4, 3.0);

nw.aa(
  `
 movss xmm0,[rcx]
 mulss xmm0,[rcx+4]
 movss [rcx],xmm0
 ret
`,
  lpFloatVal
);

console.log(nw.readFloat(lpFloatVal)); // 6
nw.free(lpFloatVal);
```


## asmBytes
```js
console.log( nw.asmBytes(`
  mov eax,1
  ret
`) ); // ArrayBuffer { [Uint8Contents]: <b8 01 00 00 00 c3>, byteLength: 6 }
```