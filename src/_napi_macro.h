#define nm_init Napi::Env env = info.Env()

// init and check arg length
#define nm_init_cal(len) \
  nm_init;\
  if (info.Length() < len) \
    nm_jserr("Not enough parameters, at least "#len);\
    nm_retu\


#define nm_IsNullish(value) (value.IsUndefined() || value.IsNull())

// get option param
#define nm_IsNullishOr(value, type, default) nm_IsNullish(value) ? (default) : type(value)

#define nm_str(value) value.ToString().Utf8Value()
#define nm_wstr(value) value.ToString().Utf16Value()
#define nm_int(value) value.ToNumber().Int32Value()
#define nm_dword(value) value.ToNumber().Uint32Value()
#define nm_qword(value) value.ToNumber().Int64Value()
#define nm_float(value) value.ToNumber().FloatValue()
#define nm_double(value) value.ToNumber().DoubleValue()
#define nm_bool(value) value.ToBoolean()
#define nm_arr(value) value.As<Napi::Array>()
#define nm_obj(value) value.As<Napi::Object>()

#define nm_ret(value) return Napi::Number::New(env, value)
#define nm_rets(value) return Napi::String::New(env, value)
#define nm_retb(value) return Napi::Boolean::New(env, value)
#define nm_retbt return Napi::Boolean::New(env, true)
#define nm_retbf return Napi::Boolean::New(env, false)
#define nm_retu return env.Undefined()
#define nm_retn return env.Null()

#define nm_jserr(err) Napi::Error::New(env, err).ThrowAsJavaScriptException()
