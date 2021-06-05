#pragma once
#include <napi.h>
#include "mem.hpp"
#include "test.hpp"
#include "tools.hpp"
#include "invoke.hpp"
#include "byte_table.hpp"
#include "va_manage.h"
#include "win32_gui.h"
#include "global_define.hpp"
#include "target.hpp"
#include "createThread.hpp"

#define __EXPORT(name, func) exports.Set(Napi::String::New(env, name), Napi::Function::New(env, func))

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  VAManage::Init(env, exports);
  Win32Gui::Init(env, exports);
  Target::Init(env, exports);
  __EXPORT("createTargetWithName", createTargetWithName);
  __EXPORT("createTargetWithPID", createTargetWithPID);

  __EXPORT("createThread", createThread);

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
  __EXPORT("asmBytes", asmBytes);

  __EXPORT("alloc", memAlloc);
  __EXPORT("free", memFree);
  __EXPORT("writeStr", memWriteStr);
  __EXPORT("writeBytes", memWriteBytes);
  __EXPORT("writeWord", memWriteWord);
  __EXPORT("writeDword", memWriteDword);
  __EXPORT("writeQword", memWriteQword);
  __EXPORT("writeFloat", memWriteFloat);
  __EXPORT("writeDouble", memWriteDouble);
  __EXPORT("writeRegionToFile", memWriteRegionToFile);

  __EXPORT("allocEx", memAllocEx);
  __EXPORT("freeEx", memFreeEx);
  __EXPORT("writeStrEx", memWriteStrEx);
  __EXPORT("writeBytesEx", memWriteBytesEx);
  __EXPORT("writeWordEx", memWriteWordEx);
  __EXPORT("writeDwordEx", memWriteDwordEx);
  __EXPORT("writeQwordEx", memWriteQwordEx);
  __EXPORT("writeFloatEx", memWriteFloatEx);
  __EXPORT("writeDoubleEx", memWriteDoubleEx);
  __EXPORT("writeRegionToFileEx", memWriteRegionToFileEx);

  __EXPORT("readStr", memReadStr);
  __EXPORT("readBytes", memReadBytes);
  __EXPORT("readWord", memReadWord);
  __EXPORT("readDword", memReadDword);
  __EXPORT("readQword", memReadQword);
  __EXPORT("readBytes", memReadBytes);
  __EXPORT("readPointer", memReadPointer);
  __EXPORT("readFloat", memReadFloat);
  __EXPORT("readDouble", memReadDouble);
  __EXPORT("readRegionFromFile", memReadRegionFromFile);

  __EXPORT("readStrEx", memReadStrEx);
  __EXPORT("readBytesEx", memReadBytesEx);
  __EXPORT("readWordEx", memReadWordEx);
  __EXPORT("readDwordEx", memReadDwordEx);
  __EXPORT("readQwordEx", memReadQwordEx);
  __EXPORT("readBytesEx", memReadBytesEx);
  __EXPORT("readPointerEx", memReadPointerEx);
  __EXPORT("readFloatEx", memReadFloatEx);
  __EXPORT("readDoubleEx", memReadDoubleEx);
  __EXPORT("readRegionFromFileEx", memReadRegionFromFileEx);

  __EXPORT("wordToByteTable", wordToByteTable);
  __EXPORT("dworDToByteTable", dwordToByteTable);
  __EXPORT("qworDToByteTable", qwordToByteTable);
  __EXPORT("floaTToByteTable", floatToByteTable);
  __EXPORT("doublEToByteTable", doubleToByteTable);
  __EXPORT("strToByteTable", strToByteTable);
  __EXPORT("wstrToByteTable", wstrToByteTable);

  __EXPORT("byteTableToWord", byteTableToWord);
  __EXPORT("byteTableToDword", byteTableToDword);
  __EXPORT("byteTableToQword", byteTableToQword);
  __EXPORT("byteTableToFloat", byteTableToFloat);
  __EXPORT("byteTableToDouble", byteTableToDouble);
  __EXPORT("byteTableToStr", byteTableToStr);
  __EXPORT("byteTableToWstr", byteTableToWstr);
  return exports;
}

NODE_API_MODULE(hello, Init)
