import { node_windows_x64 as nw } from "../";

nw.invoke({
  method: "EnumWindows",
  args: [
    (hwnd, lpParam) => {
      console.log(hwnd, lpParam);
      
      const SHELLDLL_DefView = nw['FindWindowExA'](hwnd, 0, "SHELLDLL_DefView", 0);
      // console.log(SHELLDLL_DefView);
      // if (SHELLDLL_DefView !== 0) {
      //   // 将其下一个同级分配给workerw。
      //   const workerw = nw.FindWindowExA(0, hwnd, "WorkerW", 0);
      //   const isVisible = nw.IsWindowVisible(workerw);
      //   if (isVisible) {
      //     // 设置窗口为未激活状态，否则这个窗口会遮挡视频
      //     nw.ShowWindow(workerw, 0);
      //   }
      //   nw.SetParent(ffplayw, progman);
      // }

      return true;
    },
    0,
  ],
});
