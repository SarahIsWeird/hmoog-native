#include "native.hpp"

#include <node.h>

void DoNativeInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    const auto didSucceed = NativeInit();

    const auto returnValue = v8::Boolean::New(isolate, didSucceed);
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
    assert(args.Length() == 1);
    assert(args[0]->IsBoolean());

    v8::Isolate *isolate = args.GetIsolate();

    const auto isRightClick = args[0].As<v8::Boolean>()->Value();
    const auto strokes = NativeSendMouseClick(isRightClick);

    const auto returnValue = v8::Boolean::New(isolate, strokes);
    args.GetReturnValue().Set(returnValue);
}

void Initialize(const v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "init", DoNativeInit);
    NODE_SET_METHOD(exports, "sendKeystrokes", SendKeystrokes);
    NODE_SET_METHOD(exports, "sendMouseClick", SendMouseClick);
}

NODE_MODULE(node_module, Initialize)
