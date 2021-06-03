export function getProcessID(name?: string): number;
export function getCurrentProcess(): number;
export function openProcess(
  dwDesiredAccess?: number,
  bInheritHandle?: number,
  dwProcessId?: number
): number;
export function closeHandle(hObject: number): boolean;
export function getMousePos(): {
  x: number;
  y: number;
};
export function setMousePos(X: number, Y: number): boolean;
export function isKeyPressed(nVirtKey: number): boolean;
export function keyDown(bVk: number): any;
export function keyUp(bVk: number): void;
export function doKeyPress(bVk: number): void;
export function mouse_event(
  dwFlags: number,
  dx?: number,
  dy?: number,
  dwData?: number,
  dwExtraInf?: number
): number;

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
export function readFromClipboard(): string;

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
export function writeToClipboard(output: string): boolean | undefined;

export function getScreenHeight(): number;
export function getScreenWidth(): number;
export function getWorkAreaWidth(): number;
export function getWorkAreaHeight(): number;

export function getPixel(
  x: number,
  y: number
): {
  r: number;
  g: number;
  b: number;
  rgb: number;
};

export function beep(dwFreq?: number, dwDuration?: number): boolean;

// https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/jj127460(v=msdn.10)?redirectedfrom=MSDN
export function speak(pwcs: string): boolean;

export function sleep(dwMilliseconds: number): undefined;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
export function findWindow(lpClassName?: string, lpWindowName?: string): number;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindow
export function getWindow(hWnd: number, uCmd: number): number;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
export function getWindowCaption(hWnd: number): string;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname
export function getWindowClassName(hWnd: number): string;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
export function getWindowProcessID(hWnd: number): { pid: number; tid: number };

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow
export function getForegroundWindow(): number;

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
export function sendMessage(
  hWnd: number,
  Msg: number,
  wParam: number,
  lParam: number
): number;

/**
 * 当中文出现异常，尝试setlocale
 *
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setlocale-wsetlocale?view=msvc-160&viewFallbackFrom=vs-2019
 * @param _Category
 * @param _Locale
 */
export function setlocale(_Category?: number, _Locale?: string): string;

/**
 *
 * @param symbolname
 * @param address
 */
export function registerSymbol(symbolname: string, address: number): void;

/**
 *
 * @param symbolname
 */
export function unregisterSymbol(symbolname: string): void;

/**
 *
 * @param CEAddressString
 */
export declare function getAddress(
  CEAddressString: string,
  hProcess?: number
): number;

/**
 *
 * @param global 如果设置了这个参数，会将所有数据定义到这个对象中，否者将定义到全局的global中
 */
export declare function globalDefine(global?: { [k: string]: number }): number;

/**
 * https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
 * @param cbFunc 
 * @param lpParameter 
 * @param dwCreationFlags 
 */
export declare function createThread(
  cbFunc: (lpParameter: number) => void,
  lpParameter?: number,
  dwCreationFlags?: number
): number;
