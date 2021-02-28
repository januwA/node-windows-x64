## MessageBoxA Example
```js
const newmem = nw.mem_alloc(1024);

let title = "xxx";
let body = "hello world";
let lpTitle = newmem;
let lpBody  = newmem + 100;

nw.mem_write_str(lpTitle, title);
nw.mem_write_str(lpBody, body);

let r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxA",
  args: [0, lpBody, lpTitle, 1],
});

console.log("result: ", r);

nw.mem_free(newmem);
```

## MessageBoxW Example
```js
const newmem = nw.mem_alloc(1024);

let title = "xxx";
let body = "hello world";

let lpTitle = newmem;
let lpBody  = newmem + 100;

nw.mem_write_str(lpTitle, title, true);
nw.mem_write_str(lpBody, body, true);

let r = nw.invoke({
  module: "user32.dll",
  method: "MessageBoxW",
  args: [0, lpBody, lpTitle, 3],
});

console.log("result: ", r);
nw.mem_free(newmem);
```


## SystemParametersInfoA Example
```js
const newmem = nw.mem_alloc(100);

const SPI_SETDESKWALLPAPER = 0x0014;
const SPIF_SENDCHANGE = 0x02;

nw.mem_write_str(newmem, "C:\\Users\\ajanuw\\Pictures\\Saved Pictures\\1.jpg");

nw.invoke({
  module: "user32.dll",
  method: "SystemParametersInfoA",
  args: [SPI_SETDESKWALLPAPER, 0, newmem, SPIF_SENDCHANGE],
});

nw.mem_free(newmem);
```

## GetWindowTextW Example
```js
const newmem = nw.mem_alloc(1024);

let r = nw.invoke({
  module: "User32.dll",
  method: "GetWindowTextW",
  args: [0x20306, newmem, 1024],
});
console.log(r);
console.log(nw.mem_read_str(newmem, null, true));

nw.mem_free(newmem);
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
target.invoke({
  method: "MessageBoxA",
  args: [0, "body", "title", 3],
});

target.invoke({
  method: "user32.MessageBoxA",
  args: [0, "body", "title", 3],
});
```