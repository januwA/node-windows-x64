# To table

## word_to_byte_table
```js
nw.word_to_byte_table(10) // [ 10, 0 ]
```

## dword_to_byte_table
```js
nw.dword_to_byte_table(10) // [ 10, 0, 0, 0 ]
```

## qword_to_byte_table
```js
nw.qword_to_byte_table(10) // [ 10, 0, 0, 0, 0, 0, 0, 0 ]
```

## float_to_byte_table
```js
nw.float_to_byte_table(1.2) // [ 154, 153, 153, 63 ]
```

## double_to_byte_table
```js
nw.double_to_byte_table(1.2) // [ 51, 51, 51, 51, 51, 51, 243, 63 ]
```

## str_to_byte_table
```js
nw.str_to_byte_table('abc') // [ 97, 98, 99 ]
```

## wstr_to_byte_table
```js
nw.wstr_to_byte_table('abc') // [ 97, 0, 98, 0, 99, 0 ]
```

# Form table

## byte_table_to_word
```js
nw.byte_table_to_word([ 10, 0 ]) // 10
```

## byte_table_to_dword
```js
nw.byte_table_to_dword([ 10, 0, 0, 0 ]) // 10
```

## byte_table_to_qword
```js
nw.byte_table_to_qword([ 10, 0, 0, 0, 0, 0, 0, 0 ]) // 10
```

## byte_table_to_float
```js
nw.byte_table_to_float([ 154, 153, 153, 63 ]) // 1.2000000476837158
```

## byte_table_to_double
```js
nw.byte_table_to_double([ 51, 51, 51, 51, 51, 51, 243, 63 ]) // 1.2
```

## byte_table_to_str
```js
nw.byte_table_to_str([ 97, 98, 99 ]) // abc
```

## byte_table_to_wstr
```js
nw.byte_table_to_wstr([ 97, 0, 98, 0, 99, 0 ]) // abc
```