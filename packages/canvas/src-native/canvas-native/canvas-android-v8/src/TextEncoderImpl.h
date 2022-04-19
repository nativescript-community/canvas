//
// Created by Osei Fortune on 19/04/2022.
//

#pragma once

#include "Common.h"
#include "Caches.h"
#include "Helpers.h"
#include "rust/cxx.h"
#include "canvas-android-v8/src/bridges/context.rs.h"

class TextEncoderImpl {
public:
    TextEncoderImpl(rust::Box <TextEncoder> encoder);

    static void Init(v8::Isolate *isolate);

    static void Create(const v8::FunctionCallbackInfo<v8::Value> &args);

    static TextEncoderImpl *GetPointer(v8::Local<v8::Object> object);

    static void GetEncoding(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value> &info);

    static void Encode(const v8::FunctionCallbackInfo<v8::Value> &args);

private:
    rust::Box <TextEncoder> encoder_;

    static v8::Local<v8::Function> GetCtor(v8::Isolate *isolate);
};