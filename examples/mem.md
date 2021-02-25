## mem_write_word
```js
nw.mem_write_word(lpAddress, 1);
```

## mem_write_dword
```js
nw.mem_write_dword(lpAddress, 1);
```

## mem_write_qword
```js
nw.mem_write_qword(lpAddress, 1);
```

## mem_write_float
```js
nw.mem_write_float(lpAddress, 1.2);
```

## mem_write_double
```js
nw.mem_write_double(lpAddress, 1.2);
```

## mem_write_region_to_file
```js
const newmem = nw.mem_alloc({
  size: 20,
})

nw.mem_write_str(newmem, "save file.")

nw.mem_write_region_to_file("C:\\Users\\ajanuw\\Desktop\\save.txt", newmem, 20);

nw.mem_free(newmem);
```

## mem_read_bytes
```js
const newmem = nw.mem_alloc({
  size: 20,
})

nw.mem_write_str(newmem, "abcd")

let bytes = nw.mem_read_bytes(newmem, 3);
console.log(bytes); // [ 97, 98, 99 ]

nw.mem_free(newmem);
```

## mem_read_word
```js
const newmem = nw.mem_alloc({
  size: 20,
})

nw.mem_write_str(newmem, "abcd")

let bytes = nw.mem_read_word(newmem);
console.log(bytes.toString('16')); // 6261

nw.mem_free(newmem);
```

## mem_read_dword
```js
nw.mem_read_dword(newmem)
```

## mem_read_qword
```js
nw.mem_read_qword(newmem)
```

## mem_read_pointer
```js
nw.mem_read_pointer(newmem)
```

## mem_read_float
```js
nw.mem_read_float(newmem)
```

## mem_read_double
```js
nw.mem_read_double(newmem)
```

## mem_read_str
```js
nw.mem_read_str(newmem)
nw.mem_read_str(newmem, null, true)
```

## mem_read_region_from_file
```js
const newmem = nw.mem_alloc({
  size: 20,
})

nw.mem_read_region_from_file("C:\\Users\\ajanuw\\Desktop\\中文.txt", newmem);
console.log( nw.mem_read_str(newmem) )

nw.mem_free(newmem);
```

## use CEAddressString Example
```js
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
```