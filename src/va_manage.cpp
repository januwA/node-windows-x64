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
  auto constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  constructor->SuppressDestruct();

  exports.Set("VAManage", func);
  return exports;
}

nm_api(VAManage::GetSize)
{
  nm_init;
  nm_ret(_Mybase::size);
}
nm_api(VAManage::GetMemory)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::memory);
}
nm_api(VAManage::GetPosition)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::position);
}
nm_sapi(VAManage::SetPosition)
{
  nm_init;
  this->position = nm_ull(value);
}

VAManage::VAManage(const Napi::CallbackInfo &info)
    : ObjectWrap<VAManage>(info),
      _Mybase(nmi_is_und(0, ull, 1024), (HANDLE)(nmi_is_und(1, ull, NULL)))
{
}

VAManage::~VAManage()
{
}

nm_api(VAManage::read)
{
  nm_init;
  auto size = nmi_ull(0);
  auto table = _Mybase::read(size);
  return span_to_array<uint8_t>(env, table);
}

#define WRITE_TYPE_FORM(type) \
  nm_init;                    \
  nm_ret(_Mybase::read##type());

nm_api(VAManage::readByte)
{
  WRITE_TYPE_FORM(Byte);
}

nm_api(VAManage::readWord)
{
  WRITE_TYPE_FORM(Word);
}

nm_api(VAManage::readDword)
{
  WRITE_TYPE_FORM(Dword);
}

nm_api(VAManage::readQword)
{
  WRITE_TYPE_FORM(Qword);
}

nm_api(VAManage::readFloat)
{
  WRITE_TYPE_FORM(Float);
}

nm_api(VAManage::readDouble)
{
  WRITE_TYPE_FORM(Double);
}

nm_api(VAManage::readStr)
{
  nm_init;
  size_t maxSize = nmi_is_und(0, ull, -1);
  nm_rets(_Mybase::readStr(maxSize));
}

nm_api(VAManage::readWstr)
{
  nm_init;
  size_t maxSize = nmi_is_und(0, ull, -1);
  nm_rets(_Mybase::readUstr(maxSize));
}

nm_api(VAManage::write)
{
  nm_init_cal(1);
  auto table = nmi_a(0);
  size_t count = nmi_is_und(1, ull, table.Length());
  auto vect = array_to_vector<uint8_t>(table, [](auto i)
                                       { return nm_ui(i); });
  _Mybase::write(vect, count);
  nm_retu;
}

nm_api(VAManage::writeByte)
{
  nm_init_cal(1);
  _Mybase::writeByte(nmi_ui(0));
  nm_retu;
}

nm_api(VAManage::writeWord)
{
  nm_init_cal(1);
  _Mybase::writeWord(nmi_ui(0));
  nm_retu;
}

nm_api(VAManage::writeDword)
{
  nm_init_cal(1);
  _Mybase::writeDword(nmi_ui(0));
  nm_retu;
}

nm_api(VAManage::writeQword)
{
  nm_init_cal(1);
  _Mybase::writeQword(nmi_ull(0));
  nm_retu;
}
nm_api(VAManage::writeFloat)
{
  nm_init_cal(1);
  _Mybase::writeFloat(nmi_f(0));
  nm_retu;
}

nm_api(VAManage::writeDouble)
{
  nm_init_cal(1);
  _Mybase::writeDouble(nmi_d(0));
  nm_retu;
}

nm_api(VAManage::writeStr)
{
  nm_init_cal(1);
  _Mybase::writeStr(nmi_s(0));
  nm_retu;
}

nm_api(VAManage::writeWstr)
{
  nm_init_cal(1);
  _Mybase::writeUstr(nmi_us(0));
  nm_retu;
}

nm_api(VAManage::loadFromFile)
{
  nm_init_cal(1);
  _Mybase::loadFromFile(nmi_s(0));
  nm_retu;
}

nm_api(VAManage::saveToFile)
{
  nm_init_cal(1);
  _Mybase::saveToFile(nmi_s(0));
  nm_retu;
}

nm_api(VAManage::destroy)
{
  nm_init;
  nm_retb(_Mybase::destroy());
}

nm_api(VAManage::GetPtr)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::ptr());
}
