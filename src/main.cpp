#pragma once
#include <iostream>
#include <napi.h>
#include "mem.hpp"
#include "test.hpp"
#include "tools.hpp"
#include "invoke.hpp"
#include "byte_table.hpp"
#include "va_manage.h"
#include "win32_gui.h"
#include "global_define.hpp"

#define __EXPORT(name, func) exports.Set(Napi::String::New(env, name), Napi::Function::New(env, func))

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  VAManage::Init(env, exports);
  Win32Gui::Init(env, exports);

  __EXPORT("invoke", invoke);
  __EXPORT("test", test);

  __EXPORT("getProcessID", getProcessID);
  __EXPORT("getCurrentProcess", getCurrentProcess);
  __EXPORT("openProcess", openProcess);
  __EXPORT("closeHandle", closeHandle);
  __EXPORT("getMousePos", getMousePos);
  __EXPORT("setMousePos", setMousePos);
  __EXPORT("isKeyPressed", isKeyPressed);
  __EXPORT("keyDown", keyDown);
  __EXPORT("keyUp", keyUp);
  __EXPORT("doKeyPress", doKeyPress);
  __EXPORT("mouse_event", e_mouse_event);
  __EXPORT("readFromClipboard", readFromClipboard);
  __EXPORT("writeToClipboard", writeToClipboard);
  __EXPORT("getScreenHeight", getScreenHeight);
  __EXPORT("getScreenWidth", getScreenWidth);
  __EXPORT("getWorkAreaWidth", getWorkAreaWidth);
  __EXPORT("getWorkAreaHeight", getWorkAreaHeight);
  __EXPORT("getPixel", getPixel);
  __EXPORT("beep", beep);
  __EXPORT("speak", speak);
  __EXPORT("sleep", sleep);
  __EXPORT("findWindow", findWindow);
  __EXPORT("getWindow", getWindow);
  __EXPORT("getWindowCaption", getWindowCaption);
  __EXPORT("getWindowClassName", getWindowClassName);
  __EXPORT("getWindowProcessID", getWindowProcessID);
  __EXPORT("getForegroundWindow", getForegroundWindow);
  __EXPORT("sendMessage", sendMessage);
  __EXPORT("setlocale", e_setlocale);
  __EXPORT("registerSymbol", registerSymbol);
  __EXPORT("unregisterSymbol", unregisterSymbol);
  __EXPORT("getAddress", getAddress);
  __EXPORT("globalDefine", globalDefine);

  __EXPORT("aa", aa);

  __EXPORT("mem_alloc", mem_alloc);
  __EXPORT("mem_free", mem_free);
  __EXPORT("mem_write_str", mem_write_str);
  __EXPORT("mem_write_bytes", mem_write_bytes);
  __EXPORT("mem_write_word", mem_write_word);
  __EXPORT("mem_write_dword", mem_write_dword);
  __EXPORT("mem_write_qword", mem_write_qword);
  __EXPORT("mem_write_float", mem_write_float);
  __EXPORT("mem_write_double", mem_write_double);
  __EXPORT("mem_write_region_to_file", mem_write_region_to_file);

  __EXPORT("mem_read_str", mem_read_str);
  __EXPORT("mem_read_bytes", mem_read_bytes);
  __EXPORT("mem_read_word", mem_read_word);
  __EXPORT("mem_read_dword", mem_read_dword);
  __EXPORT("mem_read_qword", mem_read_qword);
  __EXPORT("mem_read_bytes", mem_read_bytes);
  __EXPORT("mem_read_pointer", mem_read_pointer);
  __EXPORT("mem_read_float", mem_read_float);
  __EXPORT("mem_read_double", mem_read_double);
  __EXPORT("mem_read_region_from_file", mem_read_region_from_file);

  __EXPORT("word_to_byte_table", word_to_byte_table);
  __EXPORT("dword_to_byte_table", dword_to_byte_table);
  __EXPORT("qword_to_byte_table", qword_to_byte_table);
  __EXPORT("float_to_byte_table", float_to_byte_table);
  __EXPORT("double_to_byte_table", double_to_byte_table);
  __EXPORT("str_to_byte_table", str_to_byte_table);
  __EXPORT("wstr_to_byte_table", wstr_to_byte_table);

  __EXPORT("byte_table_to_word", byte_table_to_word);
  __EXPORT("byte_table_to_dword", byte_table_to_dword);
  __EXPORT("byte_table_to_qword", byte_table_to_qword);
  __EXPORT("byte_table_to_float", byte_table_to_float);
  __EXPORT("byte_table_to_double", byte_table_to_double);
  __EXPORT("byte_table_to_str", byte_table_to_str);
  __EXPORT("byte_table_to_wstr", byte_table_to_wstr);
  return exports;
}

NODE_API_MODULE(hello, Init)
