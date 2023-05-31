import { node_windows_x64 as nw } from "../";

(nw as any)["user32.messageboxa"](0, "content", "title", 1);

nw.invoke({
  method: '',
  argsType: [
    'int',
    'fn',
    'fn():int',
    'fn(int,int):int',
    'fn(int,int,int64):int',
    'fn(int,int,str):void',
  ]
})