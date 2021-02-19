```js
const assert = require('assert')

let mem = new nw.VAManage(200);
mem.position = 0;

// write
mem.writeDword(10);
assert(mem.position === 4)

mem.writeDword(20);
assert(mem.position === 8)

mem.writeDouble(1.2);
assert(mem.position === 16)

// read
mem.position = 0;
console.log(mem.readDword()); // 10

mem.position = 4;
console.log(mem.readDword()); // 20

mem.position = 8;
console.log(mem.readDouble()); // 1.2

mem.destroy();
```

## loadFromFile
```js
let mem = new nw.VAManage(200);
mem.position = 0;
mem.loadFromFile("C:\\Users\\ajanuw\\Desktop\\x.txt")
console.log( mem.position ); // 22

mem.position = 0;
console.log( mem.readStr() );

mem.destroy();
```

## saveToFile
```js
let mem = new nw.VAManage(200);
mem.position = 0;
mem.writeStr("hello.")

mem.position = 0;
mem.saveToFile("C:\\Users\\ajanuw\\Desktop\\b.txt")

mem.destroy();
```

## ptr
```js
import * as assert from "assert";

const mem = new nw.VAManage();

mem.writeDword(10);
assert(mem.ptr === (mem.memory + mem.position) )

mem.destroy();
```