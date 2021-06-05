#define nm_init Napi::Env env = info.Env()

// init and check arg length
#define nm_init_cal(len)                             \
  nm_init;                                           \
  if (info.Length() < len)                           \
  {                                                  \
    nm_err("Not enough parameters, at least " #len); \
    nm_retu;                                         \
  }

#define nm_is_un(value) (value.IsUndefined() || value.IsNull())

// get option param
#define nm_is_und(value, type, default) nm_is_un(value) ? (default) : nm_##type(value)
#define nmi_is_und(i, type, default) nm_is_un(info[i]) ? (default) : nm_##type(info[i])
#define nmo_is_und(p, type, default) nm_is_un(o.Get(p)) ? (default) : nm_##type(o.Get(p))

#define nm_is_s(value) value.IsString()
#define nm_is_n(value) value.IsNumber()
#define nm_is_b(value) value.IsBoolean()
#define nm_is_a(value) value.IsArray()
#define nm_is_ab(value) value.IsArrayBuffer()
#define nm_is_o(value) value.IsObject()
#define nm_is_fu(value) value.IsFunction()

#define nmi_is_s(i) nm_is_s(info[i])
#define nmi_is_n(i) nm_is_n(info[i])
#define nmi_is_b(i) nm_is_b(info[i])
#define nmi_is_a(i) nm_is_a(info[i])
#define nmi_is_ab(i) nm_is_ab(info[i])
#define nmi_is_o(i) nm_is_o(info[i])
#define nmi_is_fu(i) nm_is_fu(info[i])

#define nm_s(value) value.ToString().Utf8Value()
#define nm_us(value) value.ToString().Utf16Value()
#define nm_i(value) value.ToNumber().Int32Value()
#define nm_ll(value) value.ToNumber().Int64Value()
#define nm_ui(value) value.ToNumber().Uint32Value()
#define nm_ull(value) ((uintptr_t)value.ToNumber().Int64Value())
#define nm_f(value) value.ToNumber().FloatValue()
#define nm_d(value) value.ToNumber().DoubleValue()
#define nm_b(value) value.ToBoolean()
#define nm_a(value) value.As<Napi::Array>()
#define nm_o(value) value.As<Napi::Object>()
#define nm_fu(value) value.As<Napi::Function>()
#define nm_pfu(value) Napi::Persistent(nm_fu(value))

#define nmi_s(i) nm_s(info[i])
#define nmi_us(i) nm_us(info[i])
#define nmi_i(i) nm_i(info[i])
#define nmi_ll(i) nm_ll(info[i])
#define nmi_ui(i) nm_ui(info[i])
#define nmi_ull(i) nm_ull(info[i])
#define nmi_f(i) nm_f(info[i])
#define nmi_d(i) nm_d(info[i])
#define nmi_b(i) nm_b(info[i])
#define nmi_a(i) nm_a(info[i])
#define nmi_o(i) nm_o(info[i])
#define nmi_fu(i) nm_fu(info[i])
#define nmi_pfu(i) nm_pfu(info[i])

#define nm_ret(value) return Napi::Number::New(env, value)
#define nm_rets(value) return Napi::String::New(env, value)
#define nm_retb(value) return Napi::Boolean::New(env, value)
#define nm_retbt return Napi::Boolean::New(env, true)
#define nm_retbf return Napi::Boolean::New(env, false)
#define nm_retu return env.Undefined()
#define nm_retn return env.Null()

#define nm_err(err) Napi::Error::New(env, err).ThrowAsJavaScriptException()

#define nmo_get(p, type) nm_##type(o.Get(p))
#define nmo_is(p, type) nm_is_##type(o.Get(p))

// class method
#define nm_api(name) Napi::Value name(const Napi::CallbackInfo &info)
#define nm_sapi(name) void name(const Napi::CallbackInfo &info, const Napi::Value &value)