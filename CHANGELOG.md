## 0.0.10 [2021-5-19]

- *test version*
- feat: CEAddressString ignore case
- perf: CEAddressString Rewrite the parser (use Flex&Bison)
- perf: use c++20
- Remove the `(expr)` syntax of CEAddressString

## 0.0.9 [2021-4-1]

- *test version*
- feat: Add "Ex" series of functions, user operation target process memory
- refactor: The underscore naming style is changed to the camel naming style
- refactor: "mem" series of functions, delete the "mem" prefix `mem_read_byte` => `readByte`

## 0.0.8 [2021-3-29]

- *test version*
- perf: CEAddressString
- perf: function getAddress(CEAddressString: string, hProcess?: number): number;
- feat: class Target
- feat: function asmBytes(asmString: string): ArrayBuffer; 

## 0.0.7 [2021-2-28]

- *test version*
- perf: Use asmjit to rewrite invoke
- fix: fix globalDefineScript.js
- perf: Improve CEAddressString parser

## 0.0.6 [2021-2-27]

- *test version*
- fix: Fix the error when invoke handles callback


## 0.0.5 [2021-2-27]

- *test version*
- fix: Fix the error of invoke parameter address offset

## 0.0.4 [2021-2-27]

- *test version*
- feat: Support parsing CEAddressString
- feat: add registerSymbol and unregisterSymbol
- perf: Use asmjit to rewrite the "createCallback" function
- perf: The module of invoke is now an optional parameter
- docs: undate invoke docs
- feat: "nw.mem_*" Series supports CEAddressString
- feat: Map attributes that do not exist on node_windows_x64 to the invoke function
- feat: Add "globalDefineScript" script to define a large number of global variables in global
- feat: win32 gui add more functions to generate controls
- feat: win32 gui add event listener callback
- feat: Auto Asm

## 0.0.3 [2021-2-22]

- *test version*
- feat: asmtk

## 0.0.2 [2021-2-21]

- *test version*
- feat: asmjit

## 0.0.1 [2021-2-19]
- *test version*
- feat: invoke
- feat: win32 gui
- feat: va_manage
- feat: mem
- feat: byte_table
- feat: tools