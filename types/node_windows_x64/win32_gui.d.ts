export interface Win32CreateOption {
  id: number;
  windowName?: string;
  style?: number;
  x?: number;
  y?: number;
  width?: number;
  height?: number;
  parent?: number;
  events?: {
    [type: string]: (
      hWnd: number,
      message: number,
      wParam: number,
      lParam: number
    ) => undefined | number | void;
  };
}

export class Win32Gui {
  static getCheck(hwnd: number): boolean;
  static rgb(r: number, g: number, b: number): number;
  static getHLMessage(num: number): [number, number];

  hwnd: number;
  x: number;
  y: number;
  width: number;
  height: number;
  style: number;

  constructor(
    className: string,
    windowName: string,
    opt?: {
      x?: number;
      y?: number;
      width?: number;
      height?: number;
      style?: number;
    }
  );

  initRegisterClass(): boolean;
  initWindow(): boolean;
  messageLoop(
    OnReceiveMessage?: (
      hWnd: number,
      message: number,
      wParam: number,
      lParam: number
    ) => undefined | number | void
  ): number;

  createWindow(opt: {
    className: string;
    id: number;
    windowName?: string;
    style?: number;
    x?: number;
    y?: number;
    width?: number;
    height?: number;
    parent?: number;
  }): number;

  button(opt: Win32CreateOption): number;

  checkbox(opt: Win32CreateOption): number;

  radio(opt: Win32CreateOption): number;

  groupbox(opt: Win32CreateOption): number;

  text(opt: Win32CreateOption): number;

  input(opt: Win32CreateOption): number;

  textarea(opt: Win32CreateOption): number;

  listbox(opt: Win32CreateOption): number;

  select(opt: Win32CreateOption): number;
}
