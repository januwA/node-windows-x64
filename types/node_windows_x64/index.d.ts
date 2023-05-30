export * from "./aa";
export * from "./byte-table";
export * from "./mem";
export * from "./target";
export * from "./tools";
export * from "./va_manage";
export * from "./win32_gui";

export declare function invoke<T>(option: {
  /**
   * 模块名
   */
  module?: string;

  /**
   * 函数名，或者函数地址，或者CEAddtrssString
   */
  method: string | number;

  /**
   * 参数最多32个
   */
  args?: (
    | ((
        rcx?: number,
        rdx?: number,
        r8?: number,
        r9?: number,
        lpOtherArg?: number
      ) => any)
    | number
    | string
  )[];

  /**
   * 如果arg是字符串，将在invoke中保存到内存，默认存的char类型
   *
   * 如果调用unicode的函数(method后缀带W的)，则需要设置将isWideChar设置为true
   *
   * invoke会自动检查method是否包含有W的后缀，如果包含则自动保存为wchar_t, 如果出现意外，将isWideChar设置为false
   */
  isWideChar?: boolean;

  /**
   * 默认会猜测args中每个参数的类型，但是不能分辨整数和浮点数
   *
   * 使用 argsType 明确每个参数的类型
   */
  argsType?: (
    | "int"
    | "uint"
    | "int64"
    | "uintptr"
    | "float"
    | "double"
    | "str"
    | "wstr"
    | `fn${string}`
  )[];

  /**
   * 函数返回的类型, 默认 uintptr, 无符号整数就用 uintptr
   */
  retType?: "uintptr" | "int" | "int64" | "float" | "double";
}): T;

export declare function test(...args: any[]): any;
