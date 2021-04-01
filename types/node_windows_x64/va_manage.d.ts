export class VAManage {
  /**
   *
   * @param size 默认大小 1024
   */
  constructor(size?: number, hProcess?: number);
  /**
   * 管理内存的大小，初始化时设置
   */
  readonly size: number;

  /**
   * 虚拟内存基指针
   */
  readonly memory: number;

  /**
   * 基于memory的偏移地址，write系类会修改这个值
   */
  position: number;

  /**
   * memory+position
   */
  readonly ptr: number;

  read(size: number): number;
  readByte(): number;
  readWord(): number;
  readDword(): number;
  readQword(): number;
  readFloat(): number;
  readDouble(): number;
  readStr(maxSize?: number): number;
  readWstr(maxSize?: number): number;

  write(table: number[], count?: number): any;
  writeByte(byte: number): any;
  writeWord(word: number): any;
  writeDword(dword: number): any;
  writeQword(qword: number): any;
  writeFloat(float: number): any;
  writeDouble(double: number): any;
  writeStr(str: string): any;
  writeWstr(str: string): any;

  loadFromFile(filename: string): any;
  saveToFile(filename: string): any;

  /**
   * 释放虚拟内存
   */
  destroy(): boolean;
}
