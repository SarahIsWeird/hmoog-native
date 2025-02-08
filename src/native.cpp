#include "native.hpp"

#include <node.h>

void DoNativeInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    const auto didSucceed = NativeInit();

    const auto returnValue = v8::Boolean::New(isolate, didSucceed);
    args.GetReturnValue().Set(returnValue);
}

#define SET_PROPERTY(object, key, value) \
{ \
    const auto v8Key = v8::String::NewFromUtf8(isolate, key).ToLocalChecked(); \
    object->Set(isolate->GetCurrentContext(), v8Key, value); \
}

#define SET_NUMBER_PROPERTY(object, key, value) SET_PROPERTY(object, key, v8::Number::New(isolate, value))

void GetNativeInfo(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    const auto info = NativeGetInfo();
    if (info == nullptr) {
        args.GetReturnValue().SetNull();
        return;
    }

    const auto returnValue = v8::Object::New(isolate);
    SET_NUMBER_PROPERTY(returnValue, "width", info->screenWidth);
    SET_NUMBER_PROPERTY(returnValue, "height", info->screenHeight);
    args.GetReturnValue().Set(returnValue);
}

void SendKeystrokes(const v8::FunctionCallbackInfo<v8::Value>& args) {
    assert(args.Length() == 1);
    assert(args[0]->IsString());

    v8::Isolate *isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);

    const bool success = NativeSendKeystrokes(*str);
    const auto returnValue = v8::Number::New(isolate, success);
    args.GetReturnValue().Set(returnValue);
}

void SendMouseClick(const v8::FunctionCallbackInfo<v8::Value>& args) {
    assert(args.Length() == 3);
    assert(args[0]->IsNumber());
    assert(args[1]->IsNumber());
    assert(args[2]->IsBoolean());

    v8::Isolate *isolate = args.GetIsolate();

    const auto x = args[0].As<v8::Number>()->Value();
    const auto y = args[1].As<v8::Number>()->Value();
    const auto isRightClick = args[2].As<v8::Boolean>()->Value();
    const auto strokes = NativeSendMouseClick(static_cast<int>(x), static_cast<int>(y), isRightClick);

    const auto returnValue = v8::Boolean::New(isolate, strokes);
    args.GetReturnValue().Set(returnValue);
}

void Initialize(const v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "init", DoNativeInit);
    NODE_SET_METHOD(exports, "getInfo", GetNativeInfo);
    NODE_SET_METHOD(exports, "sendKeystrokes", SendKeystrokes);
    NODE_SET_METHOD(exports, "sendMouseClick", SendMouseClick);
}

NODE_MODULE(node_module, Initialize)
