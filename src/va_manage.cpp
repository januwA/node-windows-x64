#include "va_manage.h"

using namespace ajanuw;
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
  nm_ret(va_->size_);
}
Napi::Value VAManage::GetMemory(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)va_->memory_);
}
Napi::Value VAManage::GetPosition(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)va_->position_);
}
void VAManage::SetPosition(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  va_->position_ = nm_qword(value);
}

VAManage::VAManage(const CallbackInfo &info) : ObjectWrap<VAManage>(info)
{
  va_ = new ajanuw::Mem::VAManage(nm_IsNullishOr(info[0], nm_qword, 1024));
}

VAManage::~VAManage()
{
}

void *VAManage::ptr_()
{
  return va_->ptr_();
}

Napi::Value VAManage::read(const Napi::CallbackInfo &info)
{
  nm_init;
  size_t size = nm_qword(info[0]);
  std::vector<uint8_t> table = va_->read(size);
  auto r =  Array::New(env, table.size());
  for (size_t i = 0; i < table.size(); i++)
  {
    r.Set(i, table[i]);
  }
  
  return r;
}

#define WRITE_TYPE_FORM(type) \
  nm_init;                    \
  nm_ret(va_->read##type());

Napi::Value VAManage::readByte(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Byte);
}

Napi::Value VAManage::readWord(const Napi::CallbackInfo &info)
{
  WRITE_TYPE_FORM(Word);
}

Value VAManage::readDword(const CallbackInfo &info)
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
  size_t maxSize = nm_IsNullishOr(info[0], nm_qword, -1);
  nm_rets(va_->readStr(maxSize));
}

Napi::Value VAManage::readWstr(const Napi::CallbackInfo &info)
{
  nm_init;
  size_t maxSize = nm_IsNullishOr(info[0], nm_qword, -1);
  nm_rets(va_->readUstr(maxSize));
}

void VAManage::write(const Napi::CallbackInfo &info)
{
  nm_init;
  Array table = nmi_arr(0);
  size_t count = nmi_IsNullishOr(1, nm_qword, table.Length());
  vector<BYTE> vect;
  for (size_t i = 0; i < count; i++)
    vect.push_back(nm_dword(table.Get(i)));

  va_->write(vect, count);
}

void VAManage::writeByte(const Napi::CallbackInfo &info)
{
  va_->writeByte(nm_dword(info[0]));
}

void VAManage::writeWord(const Napi::CallbackInfo &info)
{
  va_->writeWord(nm_dword(info[0]));
}

void VAManage::writeDword(const Napi::CallbackInfo &info)
{
  va_->writeDword(nm_dword(info[0]));
}

void VAManage::writeQword(const Napi::CallbackInfo &info)
{
  va_->writeQword(nm_qword(info[0]));
}
void VAManage::writeFloat(const Napi::CallbackInfo &info)
{
  va_->writeFloat(nm_float(info[0]));
}

void VAManage::writeDouble(const Napi::CallbackInfo &info)
{
  va_->writeDouble(nm_double(info[0]));
}

void VAManage::writeStr(const Napi::CallbackInfo &info)
{
  va_->writeStr(nmi_str(0));
}

void VAManage::writeWstr(const Napi::CallbackInfo &info)
{
  va_->writeUstr(nmi_ustr(0));
}

void VAManage::loadFromFile(const Napi::CallbackInfo &info)
{
  va_->loadFromFile(nmi_str(0));
}

void VAManage::saveToFile(const Napi::CallbackInfo &info)
{
  va_->saveToFile(nmi_str(0));
}

Napi::Value VAManage::destroy(const Napi::CallbackInfo &info)
{
  nm_init;
  BOOL r = va_->destroy();
  delete va_;
  nm_retb(r);
}

Value VAManage::GetPtr(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)ptr_());
}
