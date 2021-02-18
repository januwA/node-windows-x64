export declare function invoke<T>(option: {

  /**
   * 模块名
   */
  module: string;

  /**
   * 函数名
   */
  method: string;

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
  )[];
  lpAddress?: number;
  dwSize?: number;
  flAllocationType?: number;
  flProtect?: number;

  /**
   * 如果arg是字符串，将在invoke中保存到内存，默认存的char类型
   * 
   * 如果调用unicode的函数(method后缀带W的)，则需要设置将isWideChar设置为true
   * 
   * invoke会自动检查method是否包含有W的后缀，如果包含则自动保存为wchar_t, 如果出现意外，将isWideChar设置为false
   */
  isWideChar?: boolean;
}): T;

export declare function mem_alloc(dwSize?: number): number;
export declare function mem_alloc(opt: {
  dwSize: number;
  lpAddress?: number;
  flAllocationType?: number;
  flProtect?: number;
}): number;

export declare function mem_free(lpAddress: number): boolean;
