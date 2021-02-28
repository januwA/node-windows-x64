export declare function mem_alloc(dwSize?: number): number;
export declare function mem_alloc(opt: {
  dwSize: number;
  lpAddress?: number;
  flAllocationType?: number;
  flProtect?: number;
}): number;

export declare function mem_free(lpAddress: number): boolean;

export function mem_write_str(
  lpAddress: number,
  str: string,
  isWideChar?: boolean
): any;
export function mem_write_bytes(lpAddress: number, table: number[]): any;
export function mem_write_word(lpAddress: number, word: number): any;
export function mem_write_dword(lpAddress: number, dword: number): any;
export function mem_write_qword(lpAddress: number, qword: number): any;
export function mem_write_float(lpAddress: number, float: number): any;
export function mem_write_double(lpAddress: number, double: number): any;
export function mem_write_region_to_file(
  filename: string,
  lpAddress: number,
  size: number
): any;

export function mem_read_str(
  lpAddress: number,
  maxSize?: number,
  isWideChar?: boolean
): string;
export function mem_read_bytes(lpAddress: number, size: number): number[];
export function mem_read_word(lpAddress: number): number;
export function mem_read_dword(lpAddress: number): number;
export function mem_read_qword(lpAddress: number): number;
export function mem_read_pointer(lpAddress: number): number;
export function mem_read_float(lpAddress: number): number;
export function mem_read_double(lpAddress: number): number;
export function mem_read_region_from_file(
  filename: string,
  lpAddress: number
): undefined;
