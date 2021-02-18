#include "va_manage.h"

Napi::Value VAManage::GetSize(const Napi::CallbackInfo& info)
{
  nm_init;
  nm_ret(this->size_);
}
Napi::Value VAManage::GetMemory(const Napi::CallbackInfo& info)
{
  nm_init;
  nm_ret((uintptr_t)this->memory_);
}
Napi::Value VAManage::GetPosition(const Napi::CallbackInfo& info)
{
  nm_init;
  nm_ret((uintptr_t)this->position_);
}
void VAManage::SetPosition(const Napi::CallbackInfo& info, const Napi::Value& value)
{
  nm_init;
  this->position_ = nm_qword(value);
}
Napi::Object VAManage::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "VAManage",
    {
      InstanceAccessor<&VAManage::GetSize>("size"),
      InstanceAccessor<&VAManage::GetMemory>("memory"),
      InstanceAccessor<&VAManage::GetPosition,&VAManage::SetPosition>("position"),

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
    }
  );
  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  constructor->SuppressDestruct();

  exports.Set("VAManage", func);
  return exports;
}
VAManage::VAManage(const CallbackInfo& info) : ObjectWrap<VAManage>(info), size_(nm_IsNullishOr(info[0], nm_qword, 1024)), position_(0)
{
  memory_ = VirtualAlloc(0, size_, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
}

VAManage::~VAManage()
{
}

void* VAManage::ptr()
{
  return (BYTE*)this->memory_ + this->position_;
}

Napi::Value VAManage::read(const Napi::CallbackInfo& info)
{
  nm_init;
  size_t size = nm_qword(info[0]);
  Array r = Array::New(env, size);
  for (size_t i = 0; i < size; i++) r.Set(i, Mem::read_byte( (void*)((uintptr_t)this->ptr() + i)) );
  return r;
}

#define WRITE_TYPE_FORM(type)\
nm_init; \
nm_ret( Mem::read_##type(this->ptr()) ); \

Napi::Value VAManage::readByte(const Napi::CallbackInfo& info)
{
  WRITE_TYPE_FORM(byte);
}

Napi::Value VAManage::readWord(const Napi::CallbackInfo& info)
{
  WRITE_TYPE_FORM(word);
}

Value VAManage::readDword(const CallbackInfo& info)
{
  WRITE_TYPE_FORM(dword);
}

Napi::Value VAManage::readQword(const Napi::CallbackInfo& info)
{
  WRITE_TYPE_FORM(qword);
}

Napi::Value VAManage::readFloat(const Napi::CallbackInfo& info)
{
  WRITE_TYPE_FORM(float);
}

Napi::Value VAManage::readDouble(const Napi::CallbackInfo& info)
{
  WRITE_TYPE_FORM(double);
}

Napi::Value VAManage::readStr(const Napi::CallbackInfo& info)
{
  nm_init;
  size_t maxSize = nm_IsNullishOr(info[0], nm_qword, -1);
  nm_rets(SSString::strFormMem(this->ptr(), maxSize));
}

Napi::Value VAManage::readWstr(const Napi::CallbackInfo& info)
{
  nm_init;
  size_t maxSize = nm_IsNullishOr(info[0], nm_qword, -1);
  nm_rets(SSString::ustrFormMem(this->ptr(), maxSize));
}

void VAManage::write(const Napi::CallbackInfo& info)
{
  nm_init;
  Array table = nm_arr(info[0]);
  size_t count = nm_IsNullishOr(info[1], nm_qword, table.Length());

  vector<BYTE> vect;
  for (size_t i = 0; i < count; i++)
    vect.push_back(nm_dword(table.Get(i)));

  Mem::write_bytes(this->ptr(), vect);
  this->position_ += count;
}

void VAManage::writeByte(const Napi::CallbackInfo& info)
{
  nm_init;
  uint32_t v = nm_dword(info[0]);
  memset(this->ptr(), v, sizeof(BYTE));
  this->position_ += sizeof(BYTE);
}

void VAManage::writeWord(const Napi::CallbackInfo& info)
{
  nm_init;
  uint32_t v = nm_dword(info[0]);
  Mem::write_word(this->ptr(), v);
  this->position_ += sizeof(WORD);
}

void VAManage::writeDword(const Napi::CallbackInfo& info)
{
  nm_init;
  uint32_t v = nm_dword(info[0]);
  Mem::write_dword(this->ptr(), v);
  this->position_ += sizeof(DWORD);
}

void VAManage::writeQword(const Napi::CallbackInfo& info)
{
  nm_init;
  uintptr_t v = nm_qword(info[0]);
  Mem::write_qword(this->ptr(), v);
  this->position_ += sizeof(ULONGLONG);
}
void VAManage::writeFloat(const Napi::CallbackInfo& info)
{
  nm_init;
  float v = nm_float(info[0]);
  Mem::write_float(this->ptr(), v);
  this->position_ += sizeof(float);
}

void VAManage::writeDouble(const Napi::CallbackInfo& info)
{
  nm_init;
  double v = nm_double(info[0]);
  Mem::write_double(this->ptr(), v);
  this->position_ += sizeof(double);
}

void VAManage::writeStr(const Napi::CallbackInfo& info)
{
  nm_init;
  String text = info[0].As<String>();
  string str = text.Utf8Value();
  Mem::write_str(this->ptr(), str);
  this->position_ += SSString::count(str);
}

void VAManage::writeWstr(const Napi::CallbackInfo& info)
{
  nm_init;
  String text = info[0].As<String>();
  u16string ustr = text.Utf16Value();
  Mem::write_str(this->ptr(), ustr);
  this->position_ += SSString::count(ustr);
}

void VAManage::loadFromFile(const Napi::CallbackInfo& info)
{
  string filename = nm_str(info[0]);
  Mem::read_region_from_file(filename, this->ptr(), &this->position_);
}

void VAManage::saveToFile(const Napi::CallbackInfo& info)
{
  nm_init;
  string filename = nm_str(info[0]);
  Mem::write_region_to_file(filename, this->ptr(), -1);
}

void VAManage::destroy(const Napi::CallbackInfo& info)
{
  Mem::free(this->memory_);
}
