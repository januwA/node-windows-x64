export declare function alloc(dwSize?: number): number;
export declare function alloc(opt: {
  dwSize: number;
  lpAddress?: number;
  flAllocationType?: number;
  flProtect?: number;
}): number;

export declare function free(lpAddress: number | string): boolean;

export function writeStr(
  lpAddress: number,
  str: string,
  isWideChar?: boolean
): any;
export function writeBytes(lpAddress: number | string, table: number[]): any;
export function writeWord(lpAddress: number | string, word: number): any;
export function writeDword(lpAddress: number | string, dword: number): any;
export function writeQword(lpAddress: number | string, qword: number): any;
export function writeFloat(lpAddress: number | string, float: number): any;
export function writeDouble(lpAddress: number | string, double: number): any;
export function writeRegionToFile(
  filename: string,
  lpAddress: number | string,
  size: number
): any;

export function readStr(
  lpAddress: number | string,
  maxSize?: number,
  isWideChar?: boolean
): string;
export function readBytes(lpAddress: number | string, size: number): number[];
export function readWord(lpAddress: number | string): number;
export function readDword(lpAddress: number | string): number;
export function readQword(lpAddress: number | string): number;
export function readPointer(lpAddress: number | string): number;
export function readFloat(lpAddress: number | string): number;
export function readDouble(lpAddress: number | string): number;
export function readRegionFromFile(
  filename: string,
  lpAddress: number | string
): undefined;

export declare function allocEx(hProcess: number, dwSize?: number): number;
export declare function allocEx(opt: {
  hProcess: number;
  dwSize: number;
  lpAddress?: number;
  flAllocationType?: number;
  flProtect?: number;
}): number;

export declare function freeEx(
  hProcess: number,
  lpAddress: number | string
): boolean;

export function writeStrEx(
  hProcess: number,
  lpAddress: number,
  str: string,
  isWideChar?: boolean
): any;
export function writeBytesEx(
  hProcess: number,
  lpAddress: number | string,
  table: number[]
): any;
export function writeWordEx(
  hProcess: number,
  lpAddress: number | string,
  word: number
): any;
export function writeDwordEx(
  hProcess: number,
  lpAddress: number | string,
  dword: number
): any;
export function writeQwordEx(
  hProcess: number,
  lpAddress: number | string,
  qword: number
): any;
export function writeFloatEx(
  hProcess: number,
  lpAddress: number | string,
  float: number
): any;
export function writeDoubleEx(
  hProcess: number,
  lpAddress: number | string,
  double: number
): any;
export function writeRegionToFileEx(
  hProcess: number,
  filename: string,
  lpAddress: number | string,
  size: number
): any;

export function readStrEx(
  hProcess: number,
  lpAddress: number | string,
  maxSize?: number,
  isWideChar?: boolean
): string;
export function readBytesEx(
  hProcess: number,
  lpAddress: number | string,
  size: number
): number[];
export function readWordEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readDwordEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readQwordEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readPointerEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readFloatEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readDoubleEx(
  hProcess: number,
  lpAddress: number | string
): number;
export function readRegionFromFileEx(
  hProcess: number,
  filename: string,
  lpAddress: number | string
): undefined;
