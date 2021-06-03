## MessageBoxA Example
```js
const newmem = nw.alloc(1024);

let title = "xxx";
let body = "hello world";
let lpTitle = newmem;
let lpBody  = newmem + 100;

nw.writeStr(lpTitle, title);
nw.writeStr(lpBody, body);

let r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxA",
  args: [0, lpBody, lpTitle, 1],
});

console.log("result: ", r);

nw.free(newmem);
```

## MessageBoxW Example
```js
const newmem = nw.alloc(1024);

let title = "xxx";
let body = "hello world";

let lpTitle = newmem;
let lpBody  = newmem + 100;

nw.writeStr(lpTitle, title, true);
nw.writeStr(lpBody, body, true);

let r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, lpBody, lpTitle, 3],
});

console.log("result: ", r);
nw.free(newmem);
```


## SystemParametersInfoA Example
```js
const newmem = nw.alloc(100);

const SPI_SETDESKWALLPAPER = 0x0014;
const SPIF_SENDCHANGE = 0x02;

nw.writeStr(newmem, "C:\\Users\\ajanuw\\Pictures\\Saved Pictures\\1.jpg");

nw.invoke({
  module: "user32.dll",
  method: "SystemParametersInfoA",
  args: [SPI_SETDESKWALLPAPER, 0, newmem, SPIF_SENDCHANGE],
});

nw.free(newmem);
```

## GetWindowTextW Example
```js
const newmem = nw.alloc(1024);

let r = nw.invoke({
  module: "User32.dll",
  method: "GetWindowTextW",
  args: [0x20306, newmem, 1024],
});
console.log(r);
console.log(nw.readStr(newmem, null, true));

nw.free(newmem);
```

## EnumWindows
```js
let r = nw.invoke({
  module: "user32.dll",
  method: "EnumWindows",
  args: [
    (hwnd, param) => {
      console.log(hwnd, param, nw.getWindowCaption(hwnd));
      return true;
    },
    10,
  ],
});

console.log("result: ", r);
```

## invoke automatically manages the string
```js
nw.invoke({
  module: "user32.dll",
  method: "MessageBoxA",
  args: [0, "body", "title", 3],
});

nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, "body", "title", 3],
});
```

```js
nw.invoke({
  method: "user32.MessageBoxW",
  args: [0, "body", "title", 3],
});


const addr = nw.getAddress("user32.MessageBoxA");
nw.invoke({
  method: addr,
  args: [0, "body", "title", 3],
});


const addr = nw.getAddress("user32.MessageBoxW");
nw.invoke({
  method: addr,
  args: [0, "body", "title", 3],
  isWideChar: true,
});


const addr = nw.getAddress("user32.MessageBoxW");
nw.registerSymbol("bbox", addr);

nw.invoke({
  method: "bbox",
  args: [0, "body", "title", 3],
  isWideChar: true,
});
```

## Proxy

The node_windows_x64 is proxied to map all non-existent attributes to the invoke function.

```js
nw.MessageBoxA(0, "body", "title", 3);

nw["user32.MessageBoxA"](0, "body", "title", 3);
```

The code above is actually

```js
nw.invoke({
  method: "MessageBoxA",
  args: [0, "body", "title", 3],
});

nw.invoke({
  method: "user32.MessageBoxA",
  args: [0, "body", "title", 3],
});
```