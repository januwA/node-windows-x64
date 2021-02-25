/**
 *
 * 动态生成 globalDefine.hpp
 *
 */

const fs = require("fs");
const win10SDKWinUserPath =
  "D:\\Windows Kits\\10\\Include\\10.0.18362.0\\um\\WinUser.h";

let gdMacroString = ``;
let m;

const WinUser = fs.readFileSync(win10SDKWinUserPath).toString("utf-8");

const toGdMacroString = (exp, comment) => {
  m = WinUser.matchAll(exp);
  if (!m) return;
  gdMacroString += `
  /*
   * ${comment}
   */
  `;
  gdMacroString += Array.from(m)
    .map((it) => `gd(${it[1].trim()});`)
    .join("");
  gdMacroString += "\r\n";
};

toGdMacroString(/#define\s+(WM_[A-Z0-9_]+)\s/g, `Window Messages`);

toGdMacroString(/#define\s+(WS_[A-Z0-9_]+)\s/g, `Window Styles`);
toGdMacroString(/#define\s+(CS_[A-Z0-9_]+)\s/g, `Class styles`);
toGdMacroString(/#define\s+(BS_[A-Z0-9_]+)\s/g, `Button Control Styles`);
toGdMacroString(/#define\s+(CBS_[A-Z0-9_]+)\s/g, `Combo Box styles`);
toGdMacroString(/#define\s+(ES_[A-Z0-9_]+)\s/g, `Listbox Styles`);
toGdMacroString(/#define\s+(LBS_[A-Z0-9_]+)\s/g, `Edit Control Styles`);
toGdMacroString(/#define\s+(SBS_[A-Z0-9_]+)\s/g, `Scroll Bar Styles`);
toGdMacroString(/#define\s+(SS_[A-Z0-9_]+)\s/g, `Static Control Constants`);
toGdMacroString(/#define\s+(BN_[A-Z0-9_]+)\s/g, `User Button Notification Codes`);
toGdMacroString(/#define\s+(BM_[A-Z0-9_]+)\s/g, `Button Control Messages`);
toGdMacroString(/#define\s+(BST_[A-Z0-9_]+)\s/g, `Button State`);

toGdMacroString(
  /#define\s+(MK_[A-Z0-9_]+)\s/g,
  `key State Masks for Mouse Messages`
);
toGdMacroString(/#define\s+(VK_[A-Z0-9_]+)\s/g, `Virtual Keys`);

// 0-9
for (let i = 0, vk = 0x30; i < 10; i++, vk++) {
  gdMacroString += `global.Set("VK_${i}", ${vk});`;
}

// A-Z
for (let vk = 0x41; vk <= 0x5a; vk++) {
  gdMacroString += `global.Set("VK_${String.fromCharCode(vk)}", ${vk});`;
}

let temp = ` #pragma once
#include <napi.h>
#include "_napi_macro.h"
#include <Windows.h>

using namespace Napi;

#define gd(key) global.Set(#key, key);

Value globalDefine(const CallbackInfo &info)
{
  nm_init;
  Napi::Object global;

  if (info.Length() && nmi_is_obj(0))
  {
    global = nmi_obj(0);
  }
  else
  {
    global = env.Global();
  }

  ${gdMacroString}

  nm_retu;
}
`;
fs.writeFileSync("./globalDefine.hpp", temp);
