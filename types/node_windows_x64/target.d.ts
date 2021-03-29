export class Target {
  name: string;
  pid: string;
  hProcess: number;
  constructor(name: string);

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
}
