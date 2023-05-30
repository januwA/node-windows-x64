```sh
$ npm i -g node-gyp windows-build-tools

$ npm i
$ npm run c
$ npm run bt
```

> 要是已经安装了vs2019和python没必要安装windows-build-tools


## 必须配置python和msvs_version
```
$ npm config set python D:\Program\Miniconda3
$ npm config set msvs_version 2019

$ npm config get python
$ npm config get msvs_version
```

## 去函数体

将.h文件拷贝到.d.ts中时

https://stackoverflow.com/questions/38110833/match-the-body-of-a-function-using-regex
```
(\w*\s[^{};]*)\n^\{($[^}$]*)\}$

$1
```

## .gyp 文件

预定义变量 https://gyp.gsrc.io/docs/InputFormatReference.md#Variables-and-Conditionals
```
PRODUCT_DIR        -> <project-dir>\build\Release

INTERMEDIATE_DIR    -> Release\obj\node-windows-x64\

module_root_dir   -> <project-dir>
```

## vs2019 组件

![](./images/2021-02-22-16-56-15.png)

## api函数使用宏替换
```
Napi::Value ([\w:]+)\(const Napi::CallbackInfo &info\)

nm_api($1)
```

```
void ([\w:]+)\(const Napi::CallbackInfo &info, const Napi::Value &value\)

nm_sapi($1)
```

5整数
```
    a(1, 2, 3, 4, 5);
00007FF686082347  mov         dword ptr [rsp+20h],5  
00007FF68608234F  mov         r9d,4  
00007FF686082355  mov         r8d,3  
00007FF68608235B  mov         edx,2  
00007FF686082360  mov         ecx,1  
00007FF686082365  call        a (07FF686081488h) 
```

5浮点
```
    a(1.0, 2.0, 3.0, 4.0, 5.0);
00007FF6265D2347  movss       xmm0,dword ptr [__real@40a00000 (07FF6265DAC20h)]  
00007FF6265D234F  movss       dword ptr [rsp+20h],xmm0  
00007FF6265D2355  movss       xmm3,dword ptr [__real@40800000 (07FF6265DAC1Ch)]  
00007FF6265D235D  movss       xmm2,dword ptr [__real@40400000 (07FF6265DAC18h)]  
00007FF6265D2365  movss       xmm1,dword ptr [__real@40000000 (07FF6265DAC14h)]  
00007FF6265D236D  movss       xmm0,dword ptr [__real@3f800000 (07FF6265DAC10h)]  
00007FF6265D2375  call        a (07FF6265D1483h)  
```

5双浮点
```
    a(1.0, 2.0, 3.0, 4.0, 5.0);
00007FF6FE1D2347  movsd       xmm0,mmword ptr [__real@4014000000000000 (07FF6FE1DAC90h)]  
00007FF6FE1D234F  movsd       mmword ptr [rsp+20h],xmm0  
00007FF6FE1D2355  movsd       xmm3,mmword ptr [__real@4010000000000000 (07FF6FE1DAC28h)]  
00007FF6FE1D235D  movsd       xmm2,mmword ptr [__real@4008000000000000 (07FF6FE1DAC20h)]  
00007FF6FE1D2365  movsd       xmm1,mmword ptr [__real@4000000000000000 (07FF6FE1DAC18h)]  
00007FF6FE1D236D  movsd       xmm0,mmword ptr [__real@3ff0000000000000 (07FF6FE1DAC10h)]  
00007FF6FE1D2375  call        a (07FF6FE1D148Dh) 
```

2整数,2浮点
```
    a(1, 2, 3.0, 4.0);
00007FF6A2A82347  movsd       xmm3,mmword ptr [__real@4010000000000000 (07FF6A2A8ACC8h)]  
00007FF6A2A8234F  movss       xmm2,dword ptr [__real@40400000 (07FF6A2A8ACD4h)]  
00007FF6A2A82357  mov         edx,2  
00007FF6A2A8235C  mov         ecx,1  
00007FF6A2A82361  call        a (07FF6A2A81159h) 
```

2浮点,2整数
```
    a(1.0, 2.0, 3, 4);
00007FF6A02E2347  mov         r9d,4  
00007FF6A02E234D  mov         r8d,3  
00007FF6A02E2353  movss       xmm1,dword ptr [__real@40000000 (07FF6A02EAC14h)]  
00007FF6A02E235B  movss       xmm0,dword ptr [__real@3f800000 (07FF6A02EAC10h)]  
00007FF6A02E2363  call        a (07FF6A02E1474h)  
```


float, float, int, int, float, int, float
```
    a(1.0, 2.0, 3, 4, 5.0, 6, 7);
00007FF7A4772347  movss       xmm0,dword ptr [__real@40e00000 (07FF7A477AC1Ch)]  
00007FF7A477234F  movss       dword ptr [rsp+30h],xmm0  
00007FF7A4772355  mov         dword ptr [rsp+28h],6  
00007FF7A477235D  movss       xmm0,dword ptr [__real@40a00000 (07FF7A477AC18h)]  
00007FF7A4772365  movss       dword ptr [rsp+20h],xmm0  
00007FF7A477236B  mov         r9d,4  
00007FF7A4772371  mov         r8d,3  
00007FF7A4772377  movss       xmm1,dword ptr [__real@40000000 (07FF7A477AC14h)]  
00007FF7A477237F  movss       xmm0,dword ptr [__real@3f800000 (07FF7A477AC10h)]  
00007FF7A4772387  call        a (07FF7A477147Eh)  
```

TODO:
 - 给回调函数添加参数类型和返回值类型，类似 `fn(int,double):double` int储存在rcx，double存在xmm1,返回类型double则需要定义对应的模板函数`double cccccc`