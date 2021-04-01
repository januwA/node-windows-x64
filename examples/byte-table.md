# To table

## wordToByteTable
```js
nw.wordToByteTable(10) // [ 10, 0 ]
```

## dwordToByteTable
```js
nw.dwordToByteTable(10) // [ 10, 0, 0, 0 ]
```

## qwordToByteTable
```js
nw.qwordToByteTable(10) // [ 10, 0, 0, 0, 0, 0, 0, 0 ]
```

## floatToByteTable
```js
nw.floatToByteTable(1.2) // [ 154, 153, 153, 63 ]
```

## doubleToByteTable
```js
nw.doubleToByteTable(1.2) // [ 51, 51, 51, 51, 51, 51, 243, 63 ]
```

## strToByteTable
```js
nw.strToByteTable('abc') // [ 97, 98, 99 ]
```

## wstrToByteTable
```js
nw.wstrToByteTable('abc') // [ 97, 0, 98, 0, 99, 0 ]
```

# Form table

## byteTableToWord
```js
nw.byteTableToWord([ 10, 0 ]) // 10
```

## byteTableToDword
```js
nw.byteTableToDword([ 10, 0, 0, 0 ]) // 10
```

## byteTableToQword
```js
nw.byteTableToQword([ 10, 0, 0, 0, 0, 0, 0, 0 ]) // 10
```

## byteTableToFloat
```js
nw.byteTableToFloat([ 154, 153, 153, 63 ]) // 1.2000000476837158
```

## byteTableToDouble
```js
nw.byteTableToDouble([ 51, 51, 51, 51, 51, 51, 243, 63 ]) // 1.2
```

## byteTableToStr
```js
nw.byteTableToStr([ 97, 98, 99 ]) // abc
```

## byteTableToWstr
```js
nw.byteTableToWstr([ 97, 0, 98, 0, 99, 0 ]) // abc
```