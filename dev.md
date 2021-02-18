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