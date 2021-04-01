export function wordToByteTable(value: number): number[];
export function dwordToByteTable(value: number): number[];
export function qwordToByteTable(value: number): number[];
export function floatToByteTable(value: number): number[];
export function doubleToByteTable(value: number): number[];
export function strToByteTable(value: string): number[];
export function wstrToByteTable(value: string): number[];

export function byteTableToWord(table: number[]): number;
export function byteTableToDword(table: number[]): number;
export function byteTableToQword(table: number[]): number;
export function byteTableToFloat(table: number[]): number;
export function byteTableToDouble(table: number[]): number;
export function byteTableToStr(table: number[]): string;
export function byteTableToWstr(table: number[]): string;
