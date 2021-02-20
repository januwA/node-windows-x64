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
const newmem = nw.mem_alloc({
  size: 1024,
});

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
const newmem = nw.mem_alloc({
  size: 100,
});

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
const newmem = nw.mem_alloc({
  size: 1024,
});

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
      console.log(hwnd, param); // xxx 10 
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