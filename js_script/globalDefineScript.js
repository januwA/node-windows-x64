/**
 *
 * 动态生成 globalDefine.hpp和define.d.ts
 *
 */

const fs = require("fs");
const path = require("path");

const wk = "D:\\Windows Kits\\10\\Include\\10.0.18362.0\\um";
const win10SDK_winuser = path.join(wk, "WinUser.h");
const win10SDK_wingdi = path.join(wk, "wingdi.h");
const win10SDK_wingnt = path.join(wk, "winnt.h");

let props = ``;
let typescriptDeclarationFile = "";
let m;
let obj = {};

const toStr = (h, exp, comment) => {
  m = h.matchAll(exp);
  if (!m) return;
  props += `
  /*
   * ${comment}
   */
  `;

  for (const it of Array.from(m)) {
    const key = it[1].trim();

    if (obj[key]) continue; // 跳过重复项

    props += `g.Set("${key}", ${it[2]
      .replace(/\/\/.*/g, "")
      .replace(/WINUSERAPI[^]*/gi, "")
      .replace(/typedef[^]*/gi, "")
      .replace(/\/\*[^]+\*\//gi, "")
      .trim()});`;
    typescriptDeclarationFile += `declare const ${key}: number;`;

    obj[key] = true;
  }
  props += "\r\n";
  obj = {};
};

// 直到下一个#
const getExp = (key) => new RegExp(`#define\\s+(${key})\\s+([^#]+)`, "g");

const WinUser = fs.readFileSync(win10SDK_winuser).toString("utf-8");

toStr(WinUser, getExp("HSHELL_[A-Z0-9_]+"), `Shell support`);

toStr(WinUser, getExp("WM_[A-Z0-9_]+"), `Window Messages`);
toStr(WinUser, getExp("WS_[A-Z0-9_]+"), `Window Styles`);
toStr(WinUser, getExp("CS_[A-Z0-9_]+"), `Class styles`);

toStr(WinUser, getExp("BS_[A-Z0-9_]+"), `Button Control Styles`);
toStr(WinUser, getExp("BM_[A-Z0-9_]+"), `Button Control Messages`);
toStr(WinUser, getExp("BST_[A-Z0-9_]+"), `Button State`);
toStr(WinUser, getExp("BN_[A-Z0-9_]+"), `Button Notification Codes`);

toStr(WinUser, getExp("CBS_[A-Z0-9_]+"), `Combo Box styles`);
toStr(WinUser, getExp("CB_[A-Z0-9_]+"), `Combo Box messages`);
toStr(WinUser, getExp("CBN_[A-Z0-9_]+"), `Combo Box Notification Codes`);

toStr(WinUser, getExp("ES_[A-Z0-9_]+"), `Listbox Styles`);
toStr(WinUser, getExp("LB_[A-Z0-9_]+"), `Listbox messages`);
toStr(WinUser, getExp("LBS_[A-Z0-9_]+"), `Edit Control Styles`);

toStr(WinUser, getExp("LBN_[A-Z0-9_]+"), `Listbox Notification Codes`);
toStr(WinUser, getExp("SBS_[A-Z0-9_]+"), `Scroll Bar Styles`);
toStr(WinUser, getExp("SS_[A-Z0-9_]+"), `Static Control Constants`);
toStr(
  WinUser,
  getExp("GWL_[A-Z0-9_]+"),
  `Window field offsets for GetWindowLong()`
);
toStr(
  WinUser,
  getExp("GWLP_[A-Z0-9_]+"),
  `_WIN64 Window field offsets for GetWindowLong()`
);

toStr(WinUser, getExp("MK_[A-Z0-9_]+"), `key State Masks for Mouse Messages`);
toStr(WinUser, getExp("EN_[A-Z0-9_]+"), `Edit Control Notification Codes`);
toStr(WinUser, getExp("VK_[A-Z0-9_]+"), `Virtual Keys`);

// vk 0-9
for (let i = 0, vk = 0x30; i < 10; i++, vk++) {
  props += `g.Set("VK_${i}", ${vk});`;
  typescriptDeclarationFile += `declare const VK_${i}: number;`;
}

// vk A-Z
for (let vk = 0x41; vk <= 0x5a; vk++) {
  props += `g.Set("VK_${String.fromCharCode(vk)}", ${vk});`;
  typescriptDeclarationFile += `declare const VK_${String.fromCharCode(
    vk
  )}: number;`;
}

const wingdi = fs.readFileSync(win10SDK_wingdi).toString("utf-8");
toStr(
  wingdi,
  getExp("[A-Z_]+_(?:BRUSH|FONT|PEN|PALETTE)"),
  `Stock Logical Objects`
);

const Winnt = fs.readFileSync(win10SDK_wingnt).toString("utf-8");
toStr(Winnt, getExp("(?:MEM|PAGE)_[A-Z0-9_]+"), `winnt.h`);

fs.writeFileSync(
  path.resolve(__dirname, "../src/global_define.hpp"),
  ` #pragma once
#include <napi.h>
#include "_napi_macro.h"
#include <Windows.h>

Napi::Value globalDefine(const Napi::CallbackInfo &info)
{
  nm_init;
  Napi::Object g;
  if (info.Length() && nmi_is_obj(0))
    g = nmi_obj(0);
  else
    g = env.Global();

  ${props}

  nm_retu;
}
`
);

fs.writeFileSync(
  path.resolve(__dirname, "../types/node_windows_x64/define.d.ts"),
  typescriptDeclarationFile
);
