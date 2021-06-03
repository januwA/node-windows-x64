#include "va_manage.h"

Napi::Object VAManage::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "VAManage",
                                    {
                                        InstanceAccessor<&VAManage::GetSize>("size"),
                                        InstanceAccessor<&VAManage::GetMemory>("memory"),
                                        InstanceAccessor<&VAManage::GetPtr>("ptr"),
                                        InstanceAccessor<&VAManage::GetPosition, &VAManage::SetPosition>("position"),

                                        InstanceMethod<&VAManage::read>("read"),
                                        InstanceMethod<&VAManage::readByte>("readByte"),
                                        InstanceMethod<&VAManage::readWord>("readWord"),
                                        InstanceMethod<&VAManage::readDword>("readDword"),
                                        InstanceMethod<&VAManage::readQword>("readQword"),
                                        InstanceMethod<&VAManage::readFloat>("readFloat"),
                                        InstanceMethod<&VAManage::readDouble>("readDouble"),
                                        InstanceMethod<&VAManage::readStr>("readStr"),
                                        InstanceMethod<&VAManage::readWstr>("readWstr"),

                                        InstanceMethod<&VAManage::write>("write"),
                                        InstanceMethod<&VAManage::writeByte>("writeByte"),
                                        InstanceMethod<&VAManage::writeWord>("writeWord"),
                                        InstanceMethod<&VAManage::writeDword>("writeDword"),
                                        InstanceMethod<&VAManage::writeQword>("writeQword"),
                                        InstanceMethod<&VAManage::writeFloat>("writeFloat"),
                                        InstanceMethod<&VAManage::writeDouble>("writeDouble"),
                                        InstanceMethod<&VAManage::writeStr>("writeStr"),
                                        InstanceMethod<&VAManage::writeWstr>("writeWstr"),

                                        InstanceMethod<&VAManage::loadFromFile>("loadFromFile"),
                                        InstanceMethod<&VAManage::saveToFile>("saveToFile"),
                                        InstanceMethod<&VAManage::destroy>("destroy"),
                                    });
  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  constructor->SuppressDestruct();

  exports.Set("VAManage", func);
  return exports;
}

Napi::Value VAManage::GetSize(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(_Mybase::size);
}
Napi::Value VAManage::GetMemory(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::memory);
}
Napi::Value VAManage::GetPosition(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::position);
}
void VAManage::SetPosition(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  this->position = nm_qword(value);
}

VAManage::VAManage(const Napi::CallbackInfo &info)
    : ObjectWrap<VAManage>(info),
      _Mybase(
          nm_is_nullishOr(info[0], nm_qword, 1024),
          info.Length() > 1 ? (HANDLE)nmi_qword(1) : NULL)
{
}

VAManage::~VAManage()
{
}

Napi::Value VAManage::read(const Napi::CallbackInfo &info)
{
  nm_init;
  auto size = nmi_qword(0);
  auto table = _Mybase::read(size);
  nm_arr_form_vect(result, table);
  return result;
}

#define WRITE_TYPE_FORM(type) \
  nm_init;                    \
  nm_ret(_Mybase::read##type());

Napi::Value VAManage::readByte(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Byte);
}

Napi::Value VAManage::readWord(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Word);
}

Napi::Value VAManage::readDword(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Dword);
}

Napi::Value VAManage::readQword(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Qword);
}

Napi::Value VAManage::readFloat(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Float);
}

Napi::Value VAManage::readDouble(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Double);
}

Napi::Value VAManage::readStr(const Napi::CallbackInfo &info)
{
  nm_init;
  size_t maxSize = nm_is_nullishOr(info[0], nm_qword, -1);
  nm_rets(_Mybase::readStr(maxSize));
}

Napi::Value VAManage::readWstr(const Napi::CallbackInfo &info)
{
  nm_init;
  size_t maxSize = nm_is_nullishOr(info[0], nm_qword, -1);
  nm_rets(_Mybase::readUstr(maxSize));
}

void VAManage::write(const Napi::CallbackInfo &info)
{
  nm_init;
  auto table = nmi_arr(0);
  size_t count = nmi_is_nullishOr(1, nm_qword, table.Length());

  std::vector<uint8_t> vect;
  for (size_t i = 0; i < count; i++)
    vect.push_back(nm_dword(table.Get(i)));

  _Mybase::write(vect, count);
}

void VAManage::writeByte(const Napi::CallbackInfo &info)
{
  _Mybase::writeByte(nmi_dword(0));
}

void VAManage::writeWord(const Napi::CallbackInfo &info)
{
  _Mybase::writeWord(nmi_dword(0));
}

void VAManage::writeDword(const Napi::CallbackInfo &info)
{
  _Mybase::writeDword(nmi_dword(0));
}

void VAManage::writeQword(const Napi::CallbackInfo &info)
{
  _Mybase::writeQword(nmi_qword(0));
}
void VAManage::writeFloat(const Napi::CallbackInfo &info)
{
  _Mybase::writeFloat(nmi_float(0));
}

void VAManage::writeDouble(const Napi::CallbackInfo &info)
{
  _Mybase::writeDouble(nmi_double(0));
}

void VAManage::writeStr(const Napi::CallbackInfo &info)
{
  _Mybase::writeStr(nmi_str(0));
}

void VAManage::writeWstr(const Napi::CallbackInfo &info)
{
  _Mybase::writeUstr(nmi_ustr(0));
}

void VAManage::loadFromFile(const Napi::CallbackInfo &info)
{
  _Mybase::loadFromFile(nmi_str(0));
}

void VAManage::saveToFile(const Napi::CallbackInfo &info)
{
  _Mybase::saveToFile(nmi_str(0));
}

Napi::Value VAManage::destroy(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(_Mybase::destroy());
}

Napi::Value VAManage::GetPtr(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::ptr());
}
