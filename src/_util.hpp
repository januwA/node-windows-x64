#pragma once
#include <iostream>
#include <span>
#include <functional>
#include <napi.h>

template <class T, class _Fn>
Napi::Array span_to_array(const Napi::Env &env, const std::span<T> s, _Fn f) noexcept
{
  auto a = Napi::Array::New(env, s.size());
  for (size_t i = 0, l = s.size(); i < l; i++)
    a.Set(i, f(s[i]));
  return a;
}

template <class T>
Napi::Array span_to_array(const Napi::Env &env, const std::span<T> s) noexcept
{
  auto a = Napi::Array::New(env, s.size());
  for (size_t i = 0, l = s.size(); i < l; i++)
    a.Set(i, s[i]);
  return a;
}

template <class T, class _Fn>
std::vector<T> array_to_vector(const Napi::Array &array, _Fn f) noexcept
{
  std::vector<T> bytes;
  for (size_t i = 0, l = array.Length(); i < l; i++)
    bytes.push_back(f(array.Get(i)));
  return bytes;
}