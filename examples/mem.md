## writeBytes
```js
nw.writeBytes(lpAddress, 1, 2, 3, 4, 0xff);
nw.writeBytes(lpAddress, [1, 2, 3, 4, 0xff]);
```

## writeWord
```js
nw.writeWord(lpAddress, 1);
```

## writeDword
```js
nw.writeDword(lpAddress, 1);
```

## writeQword
```js
nw.writeQword(lpAddress, 1);
```

## writeFloat
```js
nw.writeFloat(lpAddress, 1.2);
```

## writeDouble
```js
nw.writeDouble(lpAddress, 1.2);
```

## readwriteRegionToFile
```js
const newmem = nw.alloc({
  size: 20,
})

nw.writeStr(newmem, "save file.")

nw.readwriteRegionToFile("C:\\Users\\ajanuw\\Desktop\\save.txt", newmem, 20);

nw.free(newmem);
```

## readBytes
```js
const newmem = nw.alloc({
  size: 20,
})

nw.writeStr(newmem, "abcd")

let bytes = nw.readBytes(newmem, 3);
console.log(bytes); // [ 97, 98, 99 ]

nw.free(newmem);
```

## readWord
```js
const newmem = nw.alloc({
  size: 20,
})

nw.writeStr(newmem, "abcd")

let bytes = nw.readWord(newmem);
console.log(bytes.toString('16')); // 6261

nw.free(newmem);
```

## readDword
```js
nw.readDword(newmem)
```

## readQword
```js
nw.readQword(newmem)
```

## readPointer
```js
nw.readPointer(newmem)
```

## readFloat
```js
nw.readFloat(newmem)
```

## readDouble
```js
nw.readDouble(newmem)
```

## readStr
```js
nw.readStr(newmem)
nw.readStr(newmem, null, true)
```

## readRegionFromFile
```js
const newmem = nw.alloc({
  size: 20,
})

nw.readRegionFromFile("C:\\Users\\ajanuw\\Desktop\\中文.txt", newmem);
console.log( nw.readStr(newmem) )

nw.free(newmem);
```

## use CEAddressString Example
```js
const strMem = nw.alloc(100);
nw.writeStr(strMem, "node-windows-x64");

const addr = nw.alloc(1024);
nw.registerSymbol("newmem", addr);

nw.writeDword("newmem", 1);
nw.writeDword("newmem+4", 2);
nw.writeQword("newmem+8", strMem);

console.log(nw.readDword("newmem"));   // 1
console.log(nw.readDword("newmem+4")); //2
console.log(nw.readStr("[newmem+8]")); // node-windows-x64

nw.free(strMem);
nw.free("newmem");
nw.unregisterSymbol("newmem");


nw.registerSymbol("中文", 2);
nw.getAddress(` "中文" + 2  `); // 4
nw.unregisterSymbol("中文");


nw.getAddress(` 1 + 2 * 3 `);  // 7
nw.getAddress(` (1 + 2) * 3 `);  // 9

nw.getAddress(` "2 * 2" + 1  `) // 5
```