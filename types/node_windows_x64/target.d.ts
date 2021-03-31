export class Target {
  name: string;
  pid: string;
  hProcess: number;
  constructor(pid: number);

  setNop(
    addr: number,
    size: number
  ): {
    enable: Function;
    disable: Function;
    toggle: Function;
    delete: Function;

    bSuccess: boolean;
    bEnable: boolean;
    addr: number;
    size: number;
    origenBytes: ArrayBuffer;
  };

  setHook(
    addr: number,
    size: number,
    hookBytes: ArrayBuffer | string
  ): {
    enable: Function;
    disable: Function;
    toggle: Function;
    delete: Function;

    bSuccess: boolean;
    bEnable: boolean;
    addr: number;
    size: number;
    origenBytes: ArrayBuffer;
  };

  moduleScan(bytes: string, offset?: number): number[];
}

export function createTargetWithName(name: string): Target;
export function createTargetWithPID(pid: number): Target;
