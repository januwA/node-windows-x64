```sh
$ npm i -g node-gyp windows-build-tools

$ npm i
$ npm run c
$ npm run bt
```

## 替换win路径
```
\\(\w)
\\\$1
```

## 查看所有api
```js
const addon = require("node-windows-x64");
console.log(addon)
```

## 去函数体

https://stackoverflow.com/questions/38110833/match-the-body-of-a-function-using-regex
```
(\w*\s[^{};]*)\n^\{($[^}$]*)\}$

$1
```

## nm to nmi
```
nm_(\w+)\(info\[(\d)\]\)

nmi_$1($2)
```


## .gyp

预定义变量 https://gyp.gsrc.io/docs/InputFormatReference.md#Variables-and-Conditionals
```
PRODUCT_DIR        -> <project-dir>\build\Release

INTERMEDIATE_DIR    -> Release\obj\node-windows-x64\

module_root_dir   -> <project-dir>
```