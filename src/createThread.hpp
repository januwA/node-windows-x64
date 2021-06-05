#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"

struct TsfnContext
{
  Napi::ThreadSafeFunction tsfn;
  HANDLE hThread;
  LPVOID lpParameter;
};

void myThread(TsfnContext *ctx)
{
  napi_status status = ctx->tsfn.BlockingCall(ctx->lpParameter, [](const Napi::Env &env, const Napi::Function &cb, LPVOID data)
                                              { cb.Call({Napi::Number::New(env, (uintptr_t)data)}); });
  if (status != napi_ok)
    Napi::Error::Fatal("ThreadEntry", "err.");
  ctx->tsfn.Release();
}

nm_api(createThread)
{
  nm_init_cal(1);
  auto cbFunc = nmi_fu(0);
  auto lpParameter = nmi_is_und(1, ull, 0);
  auto dwCreationFlags = nmi_is_und(2, ui, 0);
  auto ctx = new TsfnContext();
  ctx->tsfn = Napi::ThreadSafeFunction::New(
      env,    // Environment
      cbFunc, // JS function from caller
      "name", // Resource name
      0,      // Max queue size (0 = unlimited).
      1,      // Initial thread count
      ctx,    // Context,
      [](const Napi::Env &env, void *finalizeData, TsfnContext *context)
      {
        CloseHandle(context->hThread);
        delete context;
      },              // Finalizer
      (void *)nullptr // Finalizer data
  );
  ctx->lpParameter = (LPVOID)lpParameter;
  ctx->hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)myThread, ctx, dwCreationFlags, NULL);
  nm_ret((uintptr_t)ctx->hThread);
}
