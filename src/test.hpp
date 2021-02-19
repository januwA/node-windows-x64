#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "ajanuw.h"

using namespace Napi;
using namespace ajanuw;

void test(const CallbackInfo &info)
{
  nm_init;
}