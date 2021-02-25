#define nm_init Napi::Env env = info.Env()

// init and check arg length
#define nm_init_cal(len)                               \
  nm_init;                                             \
  if (info.Length() < len)                             \
  {                                                    \
    nm_jserr("Not enough parameters, at least " #len); \
    nm_retu;                                           \
  }

#define nm_is_nullish(value) (value.IsUndefined() || value.IsNull())

// get option param
#define nm_is_nullishOr(value, type, default) nm_is_nullish(value) ? (default) : type(value)
#define nmi_is_nullishOr(i, type, default) nm_is_nullish(info[i]) ? (default) : type(info[i])

#define nm_is_str(value) value.IsString()
#define nm_is_num(value) value.IsNumber()
#define nm_is_bool(value) value.IsBoolean()
#define nm_is_arr(value) value.IsArray()
#define nm_is_abuffer(value) value.IsArrayBuffer()
#define nm_is_obj(value) value.IsObject()
#define nm_is_fun(value) value.IsFunction()

#define nmi_is_str(i) nm_is_str(info[i])
#define nmi_is_num(i) nm_is_num(info[i])
#define nmi_is_bool(i) nm_is_bool(info[i])
#define nmi_is_arr(i) nm_is_arr(info[i])
#define nmi_is_abuffer(i) nm_is_abuffer(info[i])
#define nmi_is_obj(i) nm_is_obj(info[i])
#define nmi_is_fun(i) nm_is_fun(info[i])

#define nm_str(value) value.ToString().Utf8Value()
#define nm_ustr(value) value.ToString().Utf16Value()
#define nm_int(value) value.ToNumber().Int32Value()
#define nm_dword(value) value.ToNumber().Uint32Value()
#define nm_qword(value) value.ToNumber().Int64Value()
#define nm_float(value) value.ToNumber().FloatValue()
#define nm_double(value) value.ToNumber().DoubleValue()
#define nm_bool(value) value.ToBoolean()
#define nm_arr(value) value.As<Napi::Array>()
#define nm_obj(value) value.As<Napi::Object>()
#define nm_fun(value) value.As<Napi::Function>()

#define nmi_str(i) nm_str(info[i])
#define nmi_ustr(i) nm_ustr(info[i])
#define nmi_int(i) nm_int(info[i])
#define nmi_dword(i) nm_dword(info[i])
#define nmi_qword(i) nm_qword(info[i])
#define nmi_float(i) nm_float(info[i])
#define nmi_double(i) nm_double(info[i])
#define nmi_bool(i) nm_bool(info[i])
#define nmi_arr(i) nm_arr(info[i])
#define nmi_obj(i) nm_obj(info[i])
#define nmi_fun(i) nm_fun(info[i])



#define nm_ret(value) return Napi::Number::New(env, value)
#define nm_rets(value) return Napi::String::New(env, value)
#define nm_retb(value) return Napi::Boolean::New(env, value)
#define nm_retbt return Napi::Boolean::New(env, true)
#define nm_retbf return Napi::Boolean::New(env, false)
#define nm_retu return env.Undefined()
#define nm_retn return env.Null()

#define nm_jserr(err) Napi::Error::New(env, err).ThrowAsJavaScriptException()


#define nm_arr_form_vect(to, form) \
Napi::Array to = Napi::Array::New(env, form.size());\
for (size_t i = 0; i < form.size(); i++)\
{\
to.Set(i, form[i]); \
}\

