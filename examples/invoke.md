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

## use dll
```js
nw['LoadLibraryA']('dll1.dll');
const r = nw['Dll1.fndll1'](1, "p2", (p3) => p3, 4, "p5", (p6) => p6);
console.log(r);
```
```c++
extern "C" {
  __declspec(dllexport) int fndll1(int p1, char* p2, int (*p3)(int), int p4, char* p5, int (*p6)(int))
  {
      printf("p1: %d\n", p1);
      printf("p2: %s\n", p2);
      printf("p3: %d\n", p3(3));
      printf("p4: %d\n", p4);
      printf("p5: %s\n", p5);
      printf("p6: %d\n", p6(6));
      return p1 + p4;
  }
}
```

## 处理浮点数
```ts
nw["LoadLibraryA"]("Dll1.dll");

const pHello = nw.getAddress("Dll1.hello");

const floatSize = 4;
const mem = nw.alloc(3 * floatSize);
const pX = mem + floatSize * 0;
const pY = mem + floatSize * 1;
const pResult = mem + floatSize * 2;
nw.writeFloat(pX, 1.3);
nw.writeFloat(pY, 5.5);

nw.aa(
  `
  sub rsp,8
  mov [rsp],rcx

  sub rsp,32
  movss xmm0, [rcx]
  movss xmm1, [rcx+4]
  mov rax, 0x${pHello.toString(16)}
  call rax
  add rsp,32
  
  mov rcx,[rsp]
  movss [rcx+8],xmm0
  add rsp,8
  ret
`,
  mem
);

console.log( nw.readFloat(pResult) ); // 6.800000190734863
nw.free(mem);
```
```c++
extern "C"
{
  float __declspec(dllexport) hello(float x, float y)
  {
    return x + y;
  }
}
```


## 返回值类型
```js
nw['LoadLibraryA']('dll1.dll');

// int fndll2();
console.log(nw.invoke({
  method: 'dll1.fndll2',
  retType: 'int'
}));

// float fndll3();
console.log(nw.invoke({
  method: 'dll1.fndll3',
  retType: 'float'
}));

// double fndll4();
console.log(nw.invoke({
  method: 'dll1.fndll4',
  retType: 'double'
}));

// INT64 fndll5();
console.log(nw.invoke({
  method: 'dll1.fndll5',
  retType: 'int64'
}));

// short fndll6();
console.log(nw.invoke({
  method: 'dll1.fndll6',
  retType: 'int'
}));
```

## 设置参数类型
```js
// double fndll7(double p1, double p2);
nw.invoke({
  method: 'dll1.fndll7',
  args: [4.67, 9.12],
  argsType: ['double', 'double'],
  retType: 'double'
});

// float fndll8(float p1, float p2);
nw.invoke({
  method: 'dll1.fndll8',
  args: [4.67, 9.12],
  argsType: ['float', 'float'],
  retType: 'float'
});

// int fndll9(float p1, int p2)
nw.invoke({
  method: 'dll1.fndll9',
  args: [4.67, 10],
  argsType: ['float', 'int'],
  retType: 'int'
});

nw.invoke({
  method: 'MessageBoxA',
  args: [0, "content", "title", 1],
  argsType: ['int', 'str', 'str', 'int'],
  retType: 'int'
});

nw.invoke({
  method: 'MessageBoxW',
  args: [0, "content", "title", 1],
  argsType: ['int', 'wstr', 'wstr', 'int'],
  retType: 'int'
});

nw['MessageBoxA'](0, "content", "title", 1);

nw['MessageBoxW'](0, "content", "title", 1);
```

## 给函数参数定义类型

`fndll1`函数接收一个回调函数，并向这个回调函数提供数据

```c++
extern "C" __declspec(dllexport)  float fndll1(
  float (*cb)(int, uint32_t, int64_t, uintptr_t, float, double,const char*, const wchar_t*)
) 
{
	return cb(-100, 100, -233, 10, 1.22, 7.334, "char*", L"wchar*");
}
```

在js中调用`fndll1`函数

```js
nw['LoadLibraryA']('dll1.dll');

const result = nw.invoke({

  method: 'dll1.fndll1',

  args: [(...args) => {
    console.log(args); // [ -100, 100, -233, 10, 1.2200000286102295, 7.334, 'char*', 'wchar*' ]
    return 99.99;
  }],

  argsType: [
    'fn2(int,uint,int64,uintptr,float,double,str,wstr):float', // 定义一个个函数参数的类型和返回值
  ],

  retType: 'float', // 定义 fndll1 函数的返回类型
});

console.log(result); // 99.98999786376953
```