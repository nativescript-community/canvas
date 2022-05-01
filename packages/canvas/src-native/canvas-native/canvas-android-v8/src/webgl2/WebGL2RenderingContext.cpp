//
// Created by Osei Fortune on 22/03/2022.
//

#include "WebGL2RenderingContext.h"

WebGL2RenderingContext::WebGL2RenderingContext(rust::Box<WebGLState> state) : WebGLRenderingContextBase(
        std::move(state)) {

}

WebGL2RenderingContext::~WebGL2RenderingContext() {}

void WebGL2RenderingContext::Init(v8::Isolate *isolate) {
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);

    WebGLQuery::Init(isolate);
    WebGLSampler::Init(isolate);
    WebGLSync::Init(isolate);
    WebGLTransformFeedback::Init(isolate);
    WebGLVertexArrayObject::Init(isolate);

    auto ctorFunc = GetCtor(isolate);
    auto context = isolate->GetCurrentContext();
    auto global = context->Global();
    global->Set(context, Helpers::ConvertToV8String(isolate, "WebGL2RenderingContext"),
                ctorFunc->GetFunction(context).ToLocalChecked());
    auto funcTpl = v8::FunctionTemplate::New(isolate, &InstanceFromPointer);
    global->Set(context, Helpers::ConvertToV8String(isolate, "__getWebGL2RenderingContext"),
                funcTpl->GetFunction(context).ToLocalChecked());
}

void WebGL2RenderingContext::Create(const v8::FunctionCallbackInfo<v8::Value> &args) {
    Helpers::ThrowIllegalConstructor(args.GetIsolate());
}

void WebGL2RenderingContext::InstanceFromPointer(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    auto context = isolate->GetCurrentContext();

    if (args.Length() > 0 && args[0]->IsObject()) {
        auto config = args[0].As<v8::Object>();
        std::string version("none");
        auto alpha = true;
        auto antialias = true;
        auto depth = true;
        auto fail_if_major_performance_caveat = false;
        rust::Str power_preference("default");
        auto premultiplied_alpha = true;
        auto preserve_drawing_buffer = false;
        auto stencil = false;
        auto desynchronized = false;
        auto xr_compatible = false;

        auto versionMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "version"));
        if (!versionMaybe.IsEmpty()) {
            auto versionStr = versionMaybe.ToLocalChecked();
            if (versionStr->IsString()) {
                version = Helpers::ConvertFromV8StringToString(isolate, versionStr.As<v8::String>());
            }
        }

        auto alphaMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "alpha"));
        if (!alphaMaybe.IsEmpty()) {
            auto alphaLocal = alphaMaybe.ToLocalChecked();
            if (alphaLocal->IsBoolean()) {
                alpha = alphaLocal->BooleanValue(isolate);
            }
        }

        auto antialiasMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "antialias"));
        if (!antialiasMaybe.IsEmpty()) {
            auto antialiasLocal = antialiasMaybe.ToLocalChecked();
            if (antialiasLocal->IsBoolean()) {
                antialias = antialiasLocal->BooleanValue(isolate);
            }
        }

        auto failIfMajorPerformanceCaveatMaybe = config->Get(context, Helpers::ConvertToV8String(isolate,
                                                                                                 "failIfMajorPerformanceCaveat"));
        if (!failIfMajorPerformanceCaveatMaybe.IsEmpty()) {
            auto failIfMajorPerformanceCaveatLocal = failIfMajorPerformanceCaveatMaybe.ToLocalChecked();
            if (failIfMajorPerformanceCaveatLocal->IsBoolean()) {
                fail_if_major_performance_caveat = failIfMajorPerformanceCaveatLocal->BooleanValue(isolate);
            }
        }

        auto powerPreferenceMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "powerPreference"));
        if (!powerPreferenceMaybe.IsEmpty()) {
            auto powerPreferenceLocal = powerPreferenceMaybe.ToLocalChecked();
            if (powerPreferenceLocal->IsString()) {
                power_preference = rust::Str(
                        Helpers::ConvertFromV8StringToString(isolate,
                                                             powerPreferenceLocal->ToString(context).ToLocalChecked()));
            }
        }

        auto premultipliedAlphaMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "premultipliedAlpha"));
        if (!premultipliedAlphaMaybe.IsEmpty()) {
            auto premultipliedAlphaLocal = premultipliedAlphaMaybe.ToLocalChecked();
            if (premultipliedAlphaLocal->IsBoolean()) {
                premultiplied_alpha = premultipliedAlphaLocal->BooleanValue(isolate);
            }
        }

        auto preserveDrawingBufferMaybe = config->Get(context,
                                                      Helpers::ConvertToV8String(isolate, "preserveDrawingBuffer"));
        if (!preserveDrawingBufferMaybe.IsEmpty()) {
            auto preserveDrawingBufferLocal = preserveDrawingBufferMaybe.ToLocalChecked();
            if (preserveDrawingBufferLocal->IsBoolean()) {
                preserve_drawing_buffer = preserveDrawingBufferLocal->BooleanValue(isolate);
            }
        }

        auto stencilMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "stencil"));
        if (!stencilMaybe.IsEmpty()) {
            auto stencilLocal = stencilMaybe.ToLocalChecked();
            if (stencilLocal->IsBoolean()) {
                stencil = stencilLocal->BooleanValue(isolate);
            }
        }

        auto desynchronizedMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "desynchronized"));
        if (!desynchronizedMaybe.IsEmpty()) {
            auto desynchronizedLocal = desynchronizedMaybe.ToLocalChecked();
            if (desynchronizedLocal->IsBoolean()) {
                desynchronized = desynchronizedLocal->BooleanValue(isolate);
            }
        }

        auto xrCompatibleMaybe = config->Get(context, Helpers::ConvertToV8String(isolate, "xrCompatible"));
        if (!xrCompatibleMaybe.IsEmpty()) {
            auto xrCompatibleLocal = xrCompatibleMaybe.ToLocalChecked();
            if (xrCompatibleLocal->IsBoolean()) {
                xr_compatible = xrCompatibleLocal->BooleanValue(isolate);
            }
        }


        if (version.compare("v1") == 0 || version.compare("v2") == 0) {
            args.GetReturnValue().Set(v8::Undefined(isolate));
        } else {
            auto cache = Caches::Get(isolate);

            auto ctx = canvas_native_webgl_create(
                    rust::Str(version),
                    alpha,
                    antialias,
                    depth,
                    fail_if_major_performance_caveat,
                    rust::Str(power_preference),
                    premultiplied_alpha,
                    preserve_drawing_buffer,
                    stencil,
                    desynchronized,
                    xr_compatible
            );
            WebGL2RenderingContext *renderingContext = new WebGL2RenderingContext(std::move(ctx));

            auto ctx_ptr = reinterpret_cast<intptr_t>(reinterpret_cast<intptr_t *>(renderingContext));
            auto raf_callback = new OnRafCallback(ctx_ptr, 2);
            auto raf_callback_ptr = reinterpret_cast<intptr_t>(reinterpret_cast<intptr_t *>(raf_callback));
            auto raf = canvas_native_raf_create(raf_callback_ptr);
            renderingContext->raf_ = std::make_shared<RafImpl>(raf_callback, raf_callback_ptr, std::move(raf));
            auto ret = GetCtor(isolate)->InstanceTemplate()->NewInstance(
                    context).ToLocalChecked();
            Helpers::SetInternalClassName(isolate, ret, "WebGL2RenderingContext");
            auto ext = v8::External::New(isolate, renderingContext);
            ret->SetInternalField(0, ext);
            args.GetReturnValue().Set(ret);
        }
        return;
    }
    args.GetReturnValue().Set(v8::Undefined(isolate));
}

WebGL2RenderingContext *WebGL2RenderingContext::GetPointer(v8::Local<v8::Object> object) {
    auto ptr = object->GetInternalField(0).As<v8::External>()->Value();
    if (ptr == nullptr) {
        return nullptr;
    }
    return static_cast<WebGL2RenderingContext *>(ptr);
}

WebGLRenderingContextBase *WebGL2RenderingContext::GetPointerBase(v8::Local<v8::Object> object) {
    auto ptr = object->GetInternalField(0).As<v8::External>()->Value();
    if (ptr == nullptr) {
        return nullptr;
    }
    return static_cast<WebGLRenderingContextBase *>(ptr);
}

v8::Local<v8::FunctionTemplate> WebGL2RenderingContext::GetCtor(v8::Isolate *isolate) {
    auto cache = Caches::Get(isolate);
    auto tmpl = cache->WebGL2RenderingContextTmpl.get();
    if (tmpl != nullptr) {
        return tmpl->Get(isolate);
    }

    auto context = isolate->GetCurrentContext();
    auto webgl2RenderingContextFunc = v8::FunctionTemplate::New(isolate, &Create);
    webgl2RenderingContextFunc->SetClassName(Helpers::ConvertToV8String(isolate, "WebGL2RenderingContext"));
    webgl2RenderingContextFunc->InstanceTemplate()->SetInternalFieldCount(1);

    auto webgl2RenderingContextTpl = webgl2RenderingContextFunc->InstanceTemplate();

    WebGLRenderingContext::SetConstants(isolate, webgl2RenderingContextTpl);
    WebGL2RenderingContext::SetConstants(isolate, webgl2RenderingContextTpl);

    WebGLRenderingContext::SetProps(isolate, webgl2RenderingContextTpl);
    WebGL2RenderingContext::SetProps(isolate, webgl2RenderingContextTpl);

    WebGLRenderingContext::SetMethods(isolate, webgl2RenderingContextTpl);
    WebGL2RenderingContext::SetMethods(isolate, webgl2RenderingContextTpl);


    cache->WebGL2RenderingContextTmpl = std::make_unique<v8::Persistent<v8::FunctionTemplate>>(isolate,
                                                                                               webgl2RenderingContextFunc);
    return webgl2RenderingContextFunc;
}

void WebGL2RenderingContext::BeginQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto query = args[1];

    if (target->IsNumber() && Helpers::IsInstanceOf(isolate, query, "WebGLQuery")) {
        auto queryValue = Helpers::GetPrivate(isolate, query, "instance")->ToUint32(context);
        canvas_native_webgl2_begin_query(
                target->Uint32Value(context).ToChecked(),
                queryValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::BeginTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());

    canvas_native_webgl2_begin_transform_feedback(
            args[0]->Uint32Value(context).ToChecked(),
            ptr->GetPointer()
    );
}

void WebGL2RenderingContext::BindBufferBase(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto index = args[1];
    auto buffer = args[2];
    if (target->IsNumber() && index->IsNumber() && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
        auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
        canvas_native_webgl2_bind_buffer_base(
                target->Uint32Value(context).ToChecked(),
                index->Uint32Value(context).ToChecked(),
                bufferValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }

}

void WebGL2RenderingContext::BindBufferRange(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto index = args[1];
    auto buffer = args[2];
    auto offset = args[3];
    auto size = args[4];
    if (args.Length() > 4) {
        if (target->IsNumber() && index->IsNumber() && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
            auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
            canvas_native_webgl2_bind_buffer_range(
                    target->Uint32Value(context).ToChecked(),
                    index->Uint32Value(context).ToChecked(),
                    bufferValue.ToLocalChecked()->Value(),
                    static_cast<ssize_t>(offset->IntegerValue(context).ToChecked()),
                    static_cast<ssize_t>(size->IntegerValue(context).ToChecked()),
                    ptr->GetPointer()
            )
        }
    }
}

void WebGL2RenderingContext::BindSampler(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto unit = args[0];
    auto sampler = args[1];

    if (unit->IsNumber() && Helpers::IsInstanceOf(isolate, sampler, "WebGLSampler")) {
        auto samplerValue = Helpers::GetPrivate(isolate, sampler, "instance")->ToUint32(context);
        canvas_native_webgl2_bind_sampler(
                unit->Uint32Value(context).ToChecked(),
                samplerValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::BindTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto transformFeedback = args[1];

    if (target->IsNumber() && Helpers::IsInstanceOf(isolate, transformFeedback, "WebGLTransformFeedback")) {
        auto transformFeedbackValue = Helpers::GetPrivate(isolate, transformFeedback, "instance")->ToUint32(context);
        canvas_native_webgl2_bind_transform_feedback(
                target->Uint32Value(context).ToChecked(),
                transformFeedbackValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }

}

void WebGL2RenderingContext::BindVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto vertexArray = args[0];

    if (Helpers::IsInstanceOf(isolate, vertexArray, "WebGLVertexArrayObject")) {
        auto vertexArrayValue = Helpers::GetPrivate(isolate, vertexArray, "instance")->ToUint32(context);
        canvas_native_webgl2_bind_vertex_array(
                vertexArrayValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::BlitFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());

    auto srcX0 = args[0];
    auto srcY0 = args[1];

    auto srcX1 = args[2];
    auto srcY1 = args[3];

    auto dstX0 = args[4];
    auto dstY0 = args[5];

    auto dstX1 = args[6];
    auto dstY1 = args[7];

    auto mask = args[8];
    auto filter = args[9];

    if (args.Length() > 9) {
        canvas_native_webgl2_blit_framebuffer(
                srcX0->Int32Value(context).ToChecked(),
                srcY0->Int32Value(context).ToChecked(),
                srcX1->Int32Value(context).ToChecked(),
                srcY1->Int32Value(context).ToChecked(),
                dstX0->Int32Value(context).ToChecked(),
                dstY0->Int32Value(context).ToChecked(),
                dstX1->Int32Value(context).ToChecked(),
                dstY1->Int32Value(context).ToChecked(),
                mask->Uint32Value(context).ToChecked(),
                filter->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::ClearBufferfi(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto buffer = args[0];
    auto drawbuffer = args[1];
    auto depth = args[2];
    auto stencil = args[3];

    if (args.Length() > 3 && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
        auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
        canvas_native_webgl2_clear_bufferfi(
                bufferValue.ToLocalChecked()->Value(),
                drawbuffer->Int32Value(context).ToChecked(),
                static_cast<float>(depth->NumberValue(context).ToChecked()),
                stencil->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::ClearBufferfv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto buffer = args[0];
    auto drawbuffer = args[1];
    auto values = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
        auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
        if (values->IsArray()) {
            auto array = values.As<v8::Array>();
            std::vector<float> buf;
            auto len = array->Length();
            for (int j = 0; j < len; ++j) {
                auto item = array->Get(context, j);
                if (item.IsEmpty()) {
                    buf.push_back(std::nanf(""));
                } else {
                    buf.push_back(
                            static_cast<float>(item.ToLocalChecked()->NumberValue(context).ToChecked())
                    );
                }
            }

            rust::Slice<const float> slice(buf.data(), buf.size());
            canvas_native_webgl2_clear_bufferfv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );

        } else if (values->IsFloat32Array()) {
            auto buff = values.As<v8::TypedArray>();
            auto array = buff->Buffer();
            auto store = array->GetBackingStore();
            rust::Slice<const float> slice(static_cast<float *>(store->Data()), buff->Length());
            canvas_native_webgl2_clear_bufferfv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );
        }
    }
}

void WebGL2RenderingContext::ClearBufferiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto buffer = args[0];
    auto drawbuffer = args[1];
    auto values = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
        auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
        if (values->IsArray()) {
            auto array = values.As<v8::Array>();
            std::vector <int32_t> buf;
            auto len = array->Length();
            for (int j = 0; j < len; ++j) {
                auto item = array->Get(context, j);
                buf.push_back(
                        item.ToLocalChecked()->Int32Value(context).ToChecked()
                );
            }

            rust::Slice<const int32_t> slice(buf.data(), buf.size());
            canvas_native_webgl2_clear_bufferiv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );

        } else if (values->IsInt32Array()) {
            auto buff = values.As<v8::TypedArray>();
            auto array = buff->Buffer();
            auto store = array->GetBackingStore();
            rust::Slice<const int32_t> slice(static_cast<int32_t *>(store->Data()), buff->Length());
            canvas_native_webgl2_clear_bufferiv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );
        }
    }
}

void WebGL2RenderingContext::ClearBufferuiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto buffer = args[0];
    auto drawbuffer = args[1];
    auto values = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, buffer, "WebGLBuffer")) {
        auto bufferValue = Helpers::GetPrivate(isolate, buffer, "instance")->ToUint32(context);
        if (values->IsArray()) {
            auto array = values.As<v8::Array>();
            std::vector <uint32_t> buf;
            auto len = array->Length();
            for (int j = 0; j < len; ++j) {
                auto item = array->Get(context, j);
                buf.push_back(
                        item.ToLocalChecked()->Uint32Value(context).ToChecked()
                );
            }

            rust::Slice<const uint32_t> slice(buf.data(), buf.size());
            canvas_native_webgl2_clear_bufferuiv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );

        } else if (values->IsUint32Array()) {
            auto buff = values.As<v8::TypedArray>();
            auto array = buff->Buffer();
            auto store = array->GetBackingStore();
            rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), buff->Length());
            canvas_native_webgl2_clear_bufferuiv(
                    bufferValue.ToLocalChecked()->Value(),
                    drawbuffer->Int32Value(context).ToChecked(),
                    slice,
                    ptr->GetPointer()
            );
        }
    }
}

void WebGL2RenderingContext::ClientWaitSync(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());

    auto sync = args[0];
    auto flags = args[1];
    auto timeout = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, sync, "WebGLSync")) {
        auto syncValue = WebGLSyncImpl::GetPointer(sync->ToObject(context).ToLocalChecked());
        auto ret = canvas_native_webgl2_client_wait_sync(
                syncValue->GetSync(),
                flags->Uint32Value(context).ToChecked(),
                static_cast<ssize_t>(timeout->IntegerValue(context).ToChecked()),
                ptr->GetPointer()
        );
        args.GetReturnValue().Set(ret);
        return;
    }
    // todo decide if WAIT_FAILED should be returned here
    args.GetReturnValue().Set(v8::Undefined(isolate));
}

void WebGL2RenderingContext::CompressedTexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());

    auto target = args[0];
    auto level = args[1];
    auto xoffset = args[2];
    auto yoffset = args[3];
    auto zoffset = args[4];
    auto width = args[5];
    auto height = args[6];
    auto depth = args[7];
    auto format = args[8];
    auto imageSizeOrBuf = args[9];

    if (imageSizeOrBuf->IsArrayBufferView()) {
        auto buf = imageSizeOrBuf.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        size_t srcOffset = 0;
        auto srcOffsetVal = args[10];
        if (srcOffsetVal->IsNumber()) {
            srcOffset = srcOffsetVal->IntegerValue(context).ToChecked() * buf.;
        }
        size_t srcLengthOverride = 0;
        auto srcLengthOverrideVal = args[11];
        if (srcLengthOverrideVal->IsNumber()) {
            srcLengthOverride = srcLengthOverrideVal->IntegerValue(context).ToChecked();
        }

        rust::Slice<const uint8_t> slice(static_cast<uint8_t *>(store->Data()), store->ByteLength());

        canvas_native_webgl2_compressed_tex_sub_image3d(
                target->Uint32Value(context).ToChecked(),
                level->Int32Value(context).ToChecked(),
                xoffset->Int32Value(context).ToChecked(),
                yoffset->Int32Value(context).ToChecked(),
                zoffset->Int32Value(context).ToChecked(),
                width->Int32Value(context).ToChecked(),
                height->Int32Value(context).ToChecked(),
                depth->Int32Value(context).ToChecked(),
                format->Uint32Value(context).ToChecked(),
                slice,
                srcOffset,
                srcLengthOverride,
                ptr->GetPointer()
        );
    } else {
        auto offset = args[10];
        canvas_native_webgl2_compressed_tex_sub_image3d_none(
                target->Uint32Value(context).ToChecked(),
                level->Int32Value(context).ToChecked(),
                xoffset->Int32Value(context).ToChecked(),
                yoffset->Int32Value(context).ToChecked(),
                zoffset->Int32Value(context).ToChecked(),
                width->Int32Value(context).ToChecked(),
                height->Int32Value(context).ToChecked(),
                depth->Int32Value(context).ToChecked(),
                format->Uint32Value(context).ToChecked(),
                imageSizeOrBuf->Int32Value(context).ToChecked(),
                offset->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::CopyBufferSubData(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto readTarget = args[0];
    auto writeTarget = args[1];
    auto readOffset = args[2];
    auto writeOffset = args[3];
    auto size = args[4];
    if (args.Length() > 4) {
        canvas_native_webgl2_copy_buffer_sub_data(
                readTarget->Uint32Value(context).ToChecked(),
                writeTarget->Uint32Value(context).ToChecked(),
                static_cast<ssize_t>(readOffset->IntegerValue(context).ToChecked()),
                static_cast<ssize_t>(writeOffset->IntegerValue(context).ToChecked()),
                static_cast<ssize_t>(size->IntegerValue(context).ToChecked()),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::CopyTexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto level = args[1];
    auto xoffset = args[2];
    auto yoffset = args[3];
    auto zoffset = args[4];
    auto x = args[5];
    auto y = args[6];
    auto width = args[7];
    auto height = args[8];

    if (args.Length() > 8) {
        canvas_native_webgl2_copy_tex_sub_image3d(
                target->Uint32Value(context).ToChecked(),
                level->Int32Value(context).ToChecked(),
                xoffset->Int32Value(context).ToChecked(),
                yoffset->Int32Value(context).ToChecked(),
                zoffset->Int32Value(context).ToChecked(),
                x->Int32Value(context).ToChecked(),
                y->Int32Value(context).ToChecked(),
                width->Int32Value(context).ToChecked(),
                height->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::CreateQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto instance = WebGLQuery::GetCtor(isolate)->InstanceTemplate()->NewInstance(context).ToLocalChecked();
    Helpers::SetInternalClassName(isolate, instance, "WebGLQuery");
    auto ret = canvas_native_webgl2_create_query(ptr->GetPointer());
    Helpers::SetPrivate(isolate, instance, "instance", v8::Uint32::New(isolate, ret));
    args.GetReturnValue().Set(
            instance
    );
}

void WebGL2RenderingContext::CreateSampler(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto instance = WebGLSampler::GetCtor(isolate)->InstanceTemplate()->NewInstance(context).ToLocalChecked();
    Helpers::SetInternalClassName(isolate, instance, "WebGLSampler");
    auto ret = canvas_native_webgl2_create_sampler(ptr->GetPointer());
    Helpers::SetPrivate(isolate, instance, "instance", v8::Uint32::New(isolate, ret));
    args.GetReturnValue().Set(
            instance
    );
}

void WebGL2RenderingContext::CreateTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto instance = WebGLTransformFeedback::GetCtor(isolate)->InstanceTemplate()->NewInstance(context).ToLocalChecked();
    Helpers::SetInternalClassName(isolate, instance, "WebGLTransformFeedback");
    auto ret = canvas_native_webgl2_create_transform_feedback(ptr->GetPointer());
    Helpers::SetPrivate(isolate, instance, "instance", v8::Uint32::New(isolate, ret));
    args.GetReturnValue().Set(
            instance
    );
}

void WebGL2RenderingContext::CreateVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto instance = WebGLVertexArrayObject::GetCtor(isolate)->InstanceTemplate()->NewInstance(context).ToLocalChecked();
    Helpers::SetInternalClassName(isolate, instance, "WebGLVertexArrayObject");
    auto ret = canvas_native_webgl2_create_vertex_array(ptr->GetPointer());
    Helpers::SetPrivate(isolate, instance, "instance", v8::Uint32::New(isolate, ret));
    args.GetReturnValue().Set(
            instance
    );
}

void WebGL2RenderingContext::DeleteQueryWithQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto query = args[0];

    if (Helpers::IsInstanceOf(isolate, query, "WebGLQuery")) {
        auto queryValue = Helpers::GetPrivate(isolate, query, "instance")->ToUint32(context);
        canvas_native_webgl2_delete_query_with_query(
                queryValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::DeleteSamplerWithSampler(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto sampler = args[0];

    if (Helpers::IsInstanceOf(isolate, sampler, "WebGLSampler")) {
        auto samplerValue = Helpers::GetPrivate(isolate, sampler, "instance")->ToUint32(context);
        canvas_native_webgl2_delete_sampler_with_sampler(
                samplerValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::DeleteSyncWithSync(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto sampler = args[0];

    if (Helpers::IsInstanceOf(isolate, sampler, "WebGLSync")) {
        auto sync = WebGLSyncImpl::GetPointer(sampler->ToObject(context).ToLocalChecked());
        canvas_native_webgl2_delete_sync_with_sync(
                sync->GetSync(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::DeleteTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto transformFeedback = args[0];

    if (Helpers::IsInstanceOf(isolate, transformFeedback, "WebGLTransformFeedback")) {
        auto transformFeedbackValue = Helpers::GetPrivate(isolate, transformFeedback, "instance")->ToUint32(context);
        canvas_native_webgl2_delete_transform_feedback(
                transformFeedbackValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::DeleteVertexArrayWithVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto vertexArray = args[0];

    if (Helpers::IsInstanceOf(isolate, vertexArray, "WebGLVertexArrayObject")) {
        auto vertexArrayValue = Helpers::GetPrivate(isolate, vertexArray, "instance")->ToUint32(context);
        canvas_native_webgl2_delete_vertex_array_with_vertex_array(
                vertexArrayValue.ToLocalChecked()->Value(),
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::DrawArraysInstanced(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto mode = args[0];
    auto first = args[1];
    auto count = args[2];
    auto instanceCount = args[3];

    if (args.Length() > 3) {
        canvas_native_webgl2_draw_arrays_instanced(
                mode->Uint32Value(context).ToChecked(),
                first->Int32Value(context).ToChecked(),
                count->Int32Value(context).ToChecked(),
                instanceCount->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::DrawBuffers(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto buffers = args[0];
    if (buffers->IsArray()) {
        auto array = buffers.As<v8::Array>();
        std::vector <uint32_t> buf;
        auto len = array->Length();
        for (int j = 0; j < len; ++j) {
            auto item = array->Get(context, j).ToLocalChecked();
            buf.push_back(item->Uint32Value(context).ToChecked());
        }
        rust::Slice<const uint32_t> slice(buf.data(), buf.size());
        canvas_native_webgl2_draw_buffers(slice, ptr->GetPointer());
    }
}

void WebGL2RenderingContext::DrawElementsInstanced(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto mode = args[0];
    auto count = args[1];
    auto type = args[2];
    auto offset = args[3];
    auto instanceCount = args[4];
    if (args.Length() > 4) {
        canvas_native_webgl2_draw_elements_instanced(
                mode->Uint32Value(context).ToChecked(),
                count->Int32Value(context).ToChecked(),
                type->Uint32Value(context).ToChecked(),
                static_cast<ssize_t>(offset->NumberValue(context).ToChecked()),
                instanceCount->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::DrawRangeElements(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto mode = args[0];
    auto start = args[1];
    auto end = args[2];
    auto count = args[3];
    auto type = args[4];
    auto offset = args[5];
    if (args.Length() > 5) {
        canvas_native_webgl2_draw_range_elements(
                mode->Uint32Value(context).ToChecked(),
                start->Uint32Value(context).ToChecked(),
                end->Uint32Value(context).ToChecked(),
                count->Int32Value(context).ToChecked(),
                type->Uint32Value(context).ToChecked(),
                static_cast<ssize_t>(offset->IntegerValue(context).ToChecked()),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::EndQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    if (target->IsNumber()) {
        canvas_native_webgl2_end_query(target->Uint32Value(context).ToChecked(), ptr->GetPointer());
    }
}

void WebGL2RenderingContext::EndTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    canvas_native_webgl2_end_transform_feedback(ptr->GetPointer());
}

void WebGL2RenderingContext::FenceSync(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto condition = args[0];
    auto flags = args[1];
    if (args.Length() > 1) {
        canvas_native_webgl2_fence_sync(
                condition->Uint32Value(context).ToChecked(),
                flags->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::FramebufferTextureLayer(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto target = args[0];
    auto attachment = args[1];
    auto texture = args[2];
    auto level = args[3];
    auto layer = args[4];
    if (args.Length() > 4 && Helpers::IsInstanceOf(isolate, texture, "WebGLTexture")) {
        auto textureValue = Helpers::GetPrivate(isolate, texture, "instance")->ToUint32(context);
        canvas_native_webgl2_framebuffer_texture_layer(
                target->Uint32Value(context).ToChecked(),
                attachment->Uint32Value(context).ToChecked(),
                textureValue.ToLocalChecked()->Value(),
                level->Int32Value(context).ToChecked(),
                layer->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}



void WebGL2RenderingContext::Uniform1ui(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto v0 = args[1];
    if (args.Length() > 1 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation")) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);
        canvas_native_webgl2_uniform1ui(
                locationValue.ToLocalChecked()->Value(),
                v0->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::Uniform1uiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto data = args[1];
    if (args.Length() > 1 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsUint32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Uint32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), len);

        canvas_native_webgl2_uniform1uiv(
                locationValue.ToLocalChecked()->Value(),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::Uniform2ui(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto v0 = args[1];
    auto v1 = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation")) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);
        canvas_native_webgl2_uniform2ui(
                locationValue.ToLocalChecked()->Value(),
                v0->Uint32Value(context).ToChecked(),
                v1->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::Uniform2uiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto data = args[1];
    if (args.Length() > 1 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsUint32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Uint32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), len);

        canvas_native_webgl2_uniform2uiv(
                locationValue.ToLocalChecked()->Value(),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::Uniform3ui(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto v0 = args[1];
    auto v1 = args[2];
    auto v2 = args[3];
    auto v3 = args[4];
    if (args.Length() > 3 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation")) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);
        canvas_native_webgl2_uniform3ui(
                locationValue.ToLocalChecked()->Value(),
                v0->Uint32Value(context).ToChecked(),
                v1->Uint32Value(context).ToChecked(),
                v2->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::Uniform3uiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto data = args[1];
    if (args.Length() > 1 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsUint32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Uint32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), len);

        canvas_native_webgl2_uniform3uiv(
                locationValue.ToLocalChecked()->Value(),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::Uniform4ui(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto v0 = args[1];
    auto v1 = args[2];
    auto v2 = args[3];
    auto v3 = args[4];
    if (args.Length() > 4 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation")) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);
        canvas_native_webgl2_uniform4ui(
                locationValue.ToLocalChecked()->Value(),
                v0->Uint32Value(context).ToChecked(),
                v1->Uint32Value(context).ToChecked(),
                v2->Uint32Value(context).ToChecked(),
                v3->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::Uniform4uiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto data = args[1];
    if (args.Length() > 1 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsUint32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Uint32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), len);

        canvas_native_webgl2_uniform4uiv(
                locationValue.ToLocalChecked()->Value(),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformBlockBinding(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto program = args[0];
    auto uniformBlockIndex = args[1];
    auto uniformBlockBinding = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, program, "WebGLProgram")) {
        auto programValue = Helpers::GetPrivate(isolate, program, "instance")->ToUint32(context);
        canvas_native_webgl2_uniform_block_binding(
                programValue.ToLocalChecked()->Value(),
                uniformBlockIndex->Uint32Value(context).ToChecked(),
                uniformBlockBinding->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::UniformMatrix2x3fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix2x3fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformMatrix2x4fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix2x4fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformMatrix3x2fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix3x2fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformMatrix3x4fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix3x4fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformMatrix4x2fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix4x2fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::UniformMatrix4x3fv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto location = args[0];
    auto transpose = args[1];
    auto data = args[2];
    if (args.Length() > 2 && Helpers::IsInstanceOf(isolate, location, "WebGLUniformLocation") &&
        data->IsFloat32Array()) {
        auto locationValue = Helpers::GetPrivate(isolate, location, "instance")->ToInt32(context);

        auto len = data.As<v8::Float32Array>()->Length();
        auto buf = data.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const float> slice(static_cast<float *>(store->Data()), len);

        canvas_native_webgl2_uniform_matrix4x3fv(
                locationValue.ToLocalChecked()->Value(),
                transpose->BooleanValue(isolate),
                slice,
                ptr->GetPointer()
        )
    }
}

void WebGL2RenderingContext::VertexAttribDivisor(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto index = args[0];
    auto divisor = args[1];
    if (args.Length() > 1) {
        canvas_native_webgl2_vertex_attrib_divisor(
                index->Uint32Value(context).ToChecked(),
                divisor->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::VertexAttribI4i(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto index = args[0];
    auto v0 = args[1];
    auto v1 = args[2];
    auto v2 = args[3];
    auto v3 = args[4];

    if (args.Length() > 4) {
        canvas_native_webgl2_vertex_attrib_i4i(
                index->Uint32Value(context).ToChecked(),
                v0->Int32Value(context).ToChecked(),
                v1->Int32Value(context).ToChecked(),
                v2->Int32Value(context).ToChecked(),
                v3->Int32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::VertexAttribI4iv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto index = args[0];
    auto value = args[1];
    if (args.Length() > 1 && value->IsInt32Array()) {
        auto len = value.As<v8::Int32Array>()->Length();
        auto buf = value.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const int32_t> slice(static_cast<int32_t *>(store->Data()), len);
        canvas_native_webgl2_vertex_attrib_i4iv(
                index->Uint32Value(context).ToChecked(),
                slice,
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::VertexAttribI4ui(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto index = args[0];
    auto v0 = args[1];
    auto v1 = args[2];
    auto v2 = args[3];
    auto v3 = args[4];

    if (args.Length() > 4) {
        canvas_native_webgl2_vertex_attrib_i4ui(
                index->Uint32Value(context).ToChecked(),
                v0->Uint32Value(context).ToChecked(),
                v1->Uint32Value(context).ToChecked(),
                v2->Uint32Value(context).ToChecked(),
                v3->Uint32Value(context).ToChecked(),
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::VertexAttribI4uiv(const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto ptr = GetPointerBase(args.Holder());
    auto index = args[0];
    auto value = args[1];
    if (args.Length() > 1 && value->IsUint32Array()) {
        auto len = value.As<v8::Uint32Array>()->Length();
        auto buf = value.As<v8::ArrayBufferView>();
        auto array = buf->Buffer();
        auto store = array->GetBackingStore();
        rust::Slice<const uint32_t> slice(static_cast<uint32_t *>(store->Data()), len);
        canvas_native_webgl2_vertex_attrib_i4uiv(
                index->Uint32Value(context).ToChecked(),
                slice,
                ptr->GetPointer()
        );
    }
}

void WebGL2RenderingContext::SetConstants(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> tmpl) {
    /* Getting GL parameter information */

    tmpl->Set(isolate, "READ_BUFFER", v8::Uint32::New(isolate, 0x0C02));

    tmpl->Set(isolate, "UNPACK_ROW_LENGTH", v8::Uint32::New(isolate, 0x0CF2));

    tmpl->Set(isolate, "UNPACK_SKIP_ROWS", v8::Uint32::New(isolate, 0x0CF3));

    tmpl->Set(isolate, "UNPACK_SKIP_PIXELS", v8::Uint32::New(isolate, 0x0CF4));

    tmpl->Set(isolate, "PACK_ROW_LENGTH", v8::Uint32::New(isolate, 0x0D02));

    tmpl->Set(isolate, "PACK_SKIP_ROWS", v8::Uint32::New(isolate, 0x0D03));

    tmpl->Set(isolate, "PACK_SKIP_PIXELS", v8::Uint32::New(isolate, 0x0D04));

    tmpl->Set(isolate, "TEXTURE_BINDING_3D", v8::Uint32::New(isolate, 0x806A));

    tmpl->Set(isolate, "UNPACK_SKIP_IMAGES", v8::Uint32::New(isolate, 0x806D));

    tmpl->Set(isolate, "UNPACK_IMAGE_HEIGHT", v8::Uint32::New(isolate, 0x806E));

    tmpl->Set(isolate, "MAX_3D_TEXTURE_SIZE", v8::Uint32::New(isolate, 0x8073));

    tmpl->Set(isolate, "MAX_ELEMENTS_VERTICES", v8::Uint32::New(isolate, 0x80E8));

    tmpl->Set(isolate, "MAX_ELEMENTS_INDICES", v8::Uint32::New(isolate, 0x80E9));

    tmpl->Set(isolate, "MAX_TEXTURE_LOD_BIAS", v8::Uint32::New(isolate, 0x84FD));

    tmpl->Set(isolate, "MAX_FRAGMENT_UNIFORM_COMPONENTS", v8::Uint32::New(isolate, 0x8B49));

    tmpl->Set(isolate, "MAX_VERTEX_UNIFORM_COMPONENTS", v8::Uint32::New(isolate, 0x8B4A));

    tmpl->Set(isolate, "MAX_ARRAY_TEXTURE_LAYERS", v8::Uint32::New(isolate, 0x88FF));

    tmpl->Set(isolate, "MIN_PROGRAM_TEXEL_OFFSET", v8::Uint32::New(isolate, 0x8904));

    tmpl->Set(isolate, "MAX_PROGRAM_TEXEL_OFFSET", v8::Uint32::New(isolate, 0x8905));

    tmpl->Set(isolate, "MAX_VARYING_COMPONENTS", v8::Uint32::New(isolate, 0x8B4B));

    tmpl->Set(isolate, "FRAGMENT_SHADER_DERIVATIVE_HINT", v8::Uint32::New(isolate, 0x8B8B));

    tmpl->Set(isolate, "RASTERIZER_DISCARD", v8::Uint32::New(isolate, 0x8C89));

    tmpl->Set(isolate, "VERTEX_ARRAY_BINDING", v8::Uint32::New(isolate, 0x85B5));
    tmpl->Set(isolate, "MAX_VERTEX_OUTPUT_COMPONENTS", v8::Uint32::New(isolate, 0x9122));
    tmpl->Set(isolate, "MAX_FRAGMENT_INPUT_COMPONENTS", v8::Uint32::New(isolate, 0x9125));
    tmpl->Set(isolate, "MAX_SERVER_WAIT_TIMEOUT", v8::Uint32::New(isolate, 0x9111));
    tmpl->Set(isolate, "MAX_ELEMENT_INDEX", v8::Uint32::New(isolate, 0x8D6B));

    tmpl->Set(isolate, "RED", v8::Uint32::New(isolate, 0x1903));
    tmpl->Set(isolate, "RGB8", v8::Uint32::New(isolate, 0x8051));
    tmpl->Set(isolate, "RGBA8", v8::Uint32::New(isolate, 0x8058));
    tmpl->Set(isolate, "RGB10_A2", v8::Uint32::New(isolate, 0x8059));
    tmpl->Set(isolate, "TEXTURE_3D", v8::Uint32::New(isolate, 0x806F));

    tmpl->Set(isolate, "TEXTURE_WRAP_R", v8::Uint32::New(isolate, 0x8072));
    tmpl->Set(isolate, "TEXTURE_MIN_LOD", v8::Uint32::New(isolate, 0x813A));
    tmpl->Set(isolate, "TEXTURE_MAX_LOD", v8::Uint32::New(isolate, 0x813B));
    tmpl->Set(isolate, "TEXTURE_BASE_LEVEL", v8::Uint32::New(isolate, 0x813C));
    tmpl->Set(isolate, "TEXTURE_MAX_LEVEL", v8::Uint32::New(isolate, 0x813D));


    tmpl->Set(isolate, "TEXTURE_COMPARE_MODE", v8::Uint32::New(isolate, 0x884C));
    tmpl->Set(isolate, "TEXTURE_COMPARE_FUNC", v8::Uint32::New(isolate, 0x884D));
    tmpl->Set(isolate, "SRGB", v8::Uint32::New(isolate, 0x8C40));
    tmpl->Set(isolate, "SRGB8", v8::Uint32::New(isolate, 0x8C41));
    tmpl->Set(isolate, "SRGB8_ALPHA8", v8::Uint32::New(isolate, 0x8C43));

    tmpl->Set(isolate, "COMPARE_REF_TO_TEXTURE", v8::Uint32::New(isolate, 0x884E));
    tmpl->Set(isolate, "RGBA32F", v8::Uint32::New(isolate, 0x8814));
    tmpl->Set(isolate, "RGB32F", v8::Uint32::New(isolate, 0x8815));
    tmpl->Set(isolate, "RGBA16F", v8::Uint32::New(isolate, 0x881A));
    tmpl->Set(isolate, "RGB16F", v8::Uint32::New(isolate, 0x881B));

    tmpl->Set(isolate, "TEXTURE_2D_ARRAY", v8::Uint32::New(isolate, 0x8C1A));
    tmpl->Set(isolate, "TEXTURE_BINDING_2D_ARRAY", v8::Uint32::New(isolate, 0x8C1D));
    tmpl->Set(isolate, "R11F_G11F_B10F", v8::Uint32::New(isolate, 0x8C3A));
    tmpl->Set(isolate, "RGB9_E5", v8::Uint32::New(isolate, 0x8C3D));
    tmpl->Set(isolate, "RGBA32UI", v8::Uint32::New(isolate, 0x8D70));


    tmpl->Set(isolate, "RGB32UI", v8::Uint32::New(isolate, 0x8D71));
    tmpl->Set(isolate, "RGBA16UI", v8::Uint32::New(isolate, 0x8D76));
    tmpl->Set(isolate, "RGB16UI", v8::Uint32::New(isolate, 0x8D77));
    tmpl->Set(isolate, "RGBA8UI", v8::Uint32::New(isolate, 0x8D7C));
    tmpl->Set(isolate, "RGB8UI", v8::Uint32::New(isolate, 0x8D7D));


    tmpl->Set(isolate, "RGBA32I", v8::Uint32::New(isolate, 0x8D82));
    tmpl->Set(isolate, "RGB32I", v8::Uint32::New(isolate, 0x8D83));
    tmpl->Set(isolate, "RGBA16I", v8::Uint32::New(isolate, 0x8D88));
    tmpl->Set(isolate, "RGB16I", v8::Uint32::New(isolate, 0x8D89));
    tmpl->Set(isolate, "RGBA8I", v8::Uint32::New(isolate, 0x8D8E));


    tmpl->Set(isolate, "RGB8I", v8::Uint32::New(isolate, 0x8D8F));
    tmpl->Set(isolate, "RED_INTEGER", v8::Uint32::New(isolate, 0x8D94));
    tmpl->Set(isolate, "RGB_INTEGER", v8::Uint32::New(isolate, 0x8D98));
    tmpl->Set(isolate, "RGBA_INTEGER", v8::Uint32::New(isolate, 0x8D99));
    tmpl->Set(isolate, "R8", v8::Uint32::New(isolate, 0x8229));


    tmpl->Set(isolate, "RG8", v8::Uint32::New(isolate, 0x822B));
    tmpl->Set(isolate, "R16F", v8::Uint32::New(isolate, 0x822D));
    tmpl->Set(isolate, "R32F", v8::Uint32::New(isolate, 0x822E));
    tmpl->Set(isolate, "RG16F", v8::Uint32::New(isolate, 0x822F));
    tmpl->Set(isolate, "RG32F", v8::Uint32::New(isolate, 0x8230));


    tmpl->Set(isolate, "R8I", v8::Uint32::New(isolate, 0x8231));
    tmpl->Set(isolate, "R8UI", v8::Uint32::New(isolate, 0x8232));
    tmpl->Set(isolate, "R16I", v8::Uint32::New(isolate, 0x8233));
    tmpl->Set(isolate, "R16UI", v8::Uint32::New(isolate, 0x8234));
    tmpl->Set(isolate, "R32I", v8::Uint32::New(isolate, 0x8235));


    tmpl->Set(isolate, "R32UI", v8::Uint32::New(isolate, 0x8236));
    tmpl->Set(isolate, "RG8I", v8::Uint32::New(isolate, 0x8237));
    tmpl->Set(isolate, "RG8UI", v8::Uint32::New(isolate, 0x8238));
    tmpl->Set(isolate, "RG16I", v8::Uint32::New(isolate, 0x8239));
    tmpl->Set(isolate, "RG16UI", v8::Uint32::New(isolate, 0x823A));

    tmpl->Set(isolate, "RG32I", v8::Uint32::New(isolate, 0x823B));
    tmpl->Set(isolate, "RG32UI", v8::Uint32::New(isolate, 0x823C));
    tmpl->Set(isolate, "R8_SNORM", v8::Uint32::New(isolate, 0x8F94));
    tmpl->Set(isolate, "RG8_SNORM", v8::Uint32::New(isolate, 0x8F95));
    tmpl->Set(isolate, "RGB8_SNORM", v8::Uint32::New(isolate, 0x8F96));


    tmpl->Set(isolate, "RGBA8_SNORM", v8::Uint32::New(isolate, 0x8F97));
    tmpl->Set(isolate, "RGB10_A2UI", v8::Uint32::New(isolate, 0x906F));
    tmpl->Set(isolate, "TEXTURE_IMMUTABLE_FORMAT", v8::Uint32::New(isolate, 0x912F));
    tmpl->Set(isolate, "TEXTURE_IMMUTABLE_LEVELS", v8::Uint32::New(isolate, 0x82DF));
    tmpl->Set(isolate, "UNSIGNED_INT_2_10_10_10_REV", v8::Uint32::New(isolate, 0x8368));


    tmpl->Set(isolate, "UNSIGNED_INT_10F_11F_11F_REV", v8::Uint32::New(isolate, 0x8C3B));
    tmpl->Set(isolate, "UNSIGNED_INT_5_9_9_9_REV", v8::Uint32::New(isolate, 0x8C3E));
    tmpl->Set(isolate, "FLOAT_32_UNSIGNED_INT_24_8_REV", v8::Uint32::New(isolate, 0x8DAD));
    tmpl->Set(isolate, "UNSIGNED_INT_24_8", v8::Uint32::New(isolate, 0x84FA));
    tmpl->Set(isolate, "HALF_FLOAT", v8::Uint32::New(isolate, 0x140B));


    tmpl->Set(isolate, "RG", v8::Uint32::New(isolate, 0x8227));
    tmpl->Set(isolate, "RG_INTEGER", v8::Uint32::New(isolate, 0x8228));
    tmpl->Set(isolate, "INT_2_10_10_10_REV", v8::Uint32::New(isolate, 0x8D9F));
    tmpl->Set(isolate, "QUERY_RESULT_AVAILABLE", v8::Uint32::New(isolate, 0x8865));
    tmpl->Set(isolate, "QUERY_RESULT", v8::Uint32::New(isolate, 0x8866));


    tmpl->Set(isolate, "CURRENT_QUERY", v8::Uint32::New(isolate, 0x8867));
    tmpl->Set(isolate, "ANY_SAMPLES_PASSED", v8::Uint32::New(isolate, 0x8C2F));
    tmpl->Set(isolate, "ANY_SAMPLES_PASSED_CONSERVATIVE", v8::Uint32::New(isolate, 0x8D6A));
    tmpl->Set(isolate, "MAX_DRAW_BUFFERS", v8::Uint32::New(isolate, 0x8824));

    tmpl->Set(isolate, "DRAW_BUFFER0", v8::Uint32::New(isolate, 0x8825));
    tmpl->Set(isolate, "DRAW_BUFFER1", v8::Uint32::New(isolate, 0x8826));
    tmpl->Set(isolate, "DRAW_BUFFER2", v8::Uint32::New(isolate, 0x8827));
    tmpl->Set(isolate, "DRAW_BUFFER3", v8::Uint32::New(isolate, 0x8828));
    tmpl->Set(isolate, "DRAW_BUFFER4", v8::Uint32::New(isolate, 0x8829));
    tmpl->Set(isolate, "DRAW_BUFFER5", v8::Uint32::New(isolate, 0x882A));
    tmpl->Set(isolate, "DRAW_BUFFER6", v8::Uint32::New(isolate, 0x882B));
    tmpl->Set(isolate, "DRAW_BUFFER7", v8::Uint32::New(isolate, 0x882C));
    tmpl->Set(isolate, "DRAW_BUFFER8", v8::Uint32::New(isolate, 0x882D));
    tmpl->Set(isolate, "DRAW_BUFFER9", v8::Uint32::New(isolate, 0x882E));
    tmpl->Set(isolate, "DRAW_BUFFER10", v8::Uint32::New(isolate, 0x882F));

    /* Getting GL parameter information */

    /* Textures */

    tmpl->Set(isolate, "DRAW_BUFFER11", v8::Uint32::New(isolate, 0x8830));
    tmpl->Set(isolate, "DRAW_BUFFER12", v8::Uint32::New(isolate, 0x8831));
    tmpl->Set(isolate, "DRAW_BUFFER13", v8::Uint32::New(isolate, 0x8832));
    tmpl->Set(isolate, "DRAW_BUFFER14", v8::Uint32::New(isolate, 0x8833));
    tmpl->Set(isolate, "DRAW_BUFFER15", v8::Uint32::New(isolate, 0x8834));

    tmpl->Set(isolate, "MAX_COLOR_ATTACHMENTS", v8::Uint32::New(isolate, 0x8CDF));
    tmpl->Set(isolate, "COLOR_ATTACHMENT1", v8::Uint32::New(isolate, 0x8CE1));
    tmpl->Set(isolate, "COLOR_ATTACHMENT2", v8::Uint32::New(isolate, 0x8CE2));
    tmpl->Set(isolate, "COLOR_ATTACHMENT3", v8::Uint32::New(isolate, 0x8CE3));
    tmpl->Set(isolate, "COLOR_ATTACHMENT4", v8::Uint32::New(isolate, 0x8CE4));
    tmpl->Set(isolate, "COLOR_ATTACHMENT5", v8::Uint32::New(isolate, 0x8CE5));
    tmpl->Set(isolate, "COLOR_ATTACHMENT6", v8::Uint32::New(isolate, 0x8CE6));
    tmpl->Set(isolate, "COLOR_ATTACHMENT7", v8::Uint32::New(isolate, 0x8CE7));
    tmpl->Set(isolate, "COLOR_ATTACHMENT8", v8::Uint32::New(isolate, 0x8CE8));
    tmpl->Set(isolate, "COLOR_ATTACHMENT9", v8::Uint32::New(isolate, 0x8CE9));
    tmpl->Set(isolate, "COLOR_ATTACHMENT10", v8::Uint32::New(isolate, 0x8CEA));
    tmpl->Set(isolate, "COLOR_ATTACHMENT11", v8::Uint32::New(isolate, 0x8CEB));
    tmpl->Set(isolate, "COLOR_ATTACHMENT12", v8::Uint32::New(isolate, 0x8CEC));
    tmpl->Set(isolate, "COLOR_ATTACHMENT13", v8::Uint32::New(isolate, 0x8CED));
    tmpl->Set(isolate, "COLOR_ATTACHMENT14", v8::Uint32::New(isolate, 0x8CEE));
    tmpl->Set(isolate, "COLOR_ATTACHMENT15", v8::Uint32::New(isolate, 0x8CEF));

    tmpl->Set(isolate, "SAMPLER_3D", v8::Uint32::New(isolate, 0x8B5F));
    tmpl->Set(isolate, "SAMPLER_2D_SHADOW", v8::Uint32::New(isolate, 0x8B62));
    tmpl->Set(isolate, "SAMPLER_2D_ARRAY", v8::Uint32::New(isolate, 0x8DC1));
    tmpl->Set(isolate, "SAMPLER_2D_ARRAY_SHADOW", v8::Uint32::New(isolate, 0x8DC4));
    tmpl->Set(isolate, "SAMPLER_CUBE_SHADOW", v8::Uint32::New(isolate, 0x8DC5));

    tmpl->Set(isolate, "INT_SAMPLER_2D", v8::Uint32::New(isolate, 0x8DCA));
    tmpl->Set(isolate, "INT_SAMPLER_3D", v8::Uint32::New(isolate, 0x8DCB));
    tmpl->Set(isolate, "INT_SAMPLER_CUBE", v8::Uint32::New(isolate, 0x8DCC));
    tmpl->Set(isolate, "INT_SAMPLER_2D_ARRAY", v8::Uint32::New(isolate, 0x8DCF));
    tmpl->Set(isolate, "UNSIGNED_INT_SAMPLER_2D", v8::Uint32::New(isolate, 0x8DD2));

    tmpl->Set(isolate, "UNSIGNED_INT_SAMPLER_3D", v8::Uint32::New(isolate, 0x8DD3));
    tmpl->Set(isolate, "UNSIGNED_INT_SAMPLER_CUBE", v8::Uint32::New(isolate, 0x8DD4));
    tmpl->Set(isolate, "UNSIGNED_INT_SAMPLER_2D_ARRAY", v8::Uint32::New(isolate, 0x8DD7));
    tmpl->Set(isolate, "MAX_SAMPLES", v8::Uint32::New(isolate, 0x8D57));
    tmpl->Set(isolate, "SAMPLER_BINDING", v8::Uint32::New(isolate, 0x8919));

    tmpl->Set(isolate, "PIXEL_PACK_BUFFER", v8::Uint32::New(isolate, 0x88EB));
    tmpl->Set(isolate, "PIXEL_UNPACK_BUFFER", v8::Uint32::New(isolate, 0x88EC));
    tmpl->Set(isolate, "PIXEL_PACK_BUFFER_BINDING", v8::Uint32::New(isolate, 0x88ED));
    tmpl->Set(isolate, "PIXEL_UNPACK_BUFFER_BINDING", v8::Uint32::New(isolate, 0x88EF));
    tmpl->Set(isolate, "COPY_READ_BUFFER", v8::Uint32::New(isolate, 0x8F36));

    tmpl->Set(isolate, "COPY_WRITE_BUFFER", v8::Uint32::New(isolate, 0x8F37));
    tmpl->Set(isolate, "COPY_READ_BUFFER_BINDING", v8::Uint32::New(isolate, 0x8F36));
    tmpl->Set(isolate, "COPY_WRITE_BUFFER_BINDING", v8::Uint32::New(isolate, 0x8F37));
    tmpl->Set(isolate, "FLOAT_MAT2x3", v8::Uint32::New(isolate, 0x8B65));
    tmpl->Set(isolate, "FLOAT_MAT2x4", v8::Uint32::New(isolate, 0x8B66));

    tmpl->Set(isolate, "FLOAT_MAT3x2", v8::Uint32::New(isolate, 0x8B67));
    tmpl->Set(isolate, "FLOAT_MAT3x4", v8::Uint32::New(isolate, 0x8B68));
    tmpl->Set(isolate, "FLOAT_MAT4x2", v8::Uint32::New(isolate, 0x8B69));
    tmpl->Set(isolate, "FLOAT_MAT4x3", v8::Uint32::New(isolate, 0x8B6A));
    tmpl->Set(isolate, "UNSIGNED_INT_VEC2", v8::Uint32::New(isolate, 0x8DC6));

    tmpl->Set(isolate, "UNSIGNED_INT_VEC3", v8::Uint32::New(isolate, 0x8DC7));
    tmpl->Set(isolate, "UNSIGNED_INT_VEC4", v8::Uint32::New(isolate, 0x8DC8));
    tmpl->Set(isolate, "UNSIGNED_NORMALIZED", v8::Uint32::New(isolate, 0x8C17));
    tmpl->Set(isolate, "SIGNED_NORMALIZED", v8::Uint32::New(isolate, 0x8F9C));

    /* Vertex attributes */

    tmpl->Set(isolate, "VERTEX_ATTRIB_ARRAY_INTEGER", v8::Uint32::New(isolate, 0x88FD));
    tmpl->Set(isolate, "VERTEX_ATTRIB_ARRAY_DIVISOR", v8::Uint32::New(isolate, 0x88FE));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BUFFER_MODE", v8::Uint32::New(isolate, 0x8C7F));
    tmpl->Set(isolate, "MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS", v8::Uint32::New(isolate, 0x8C80));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_VARYINGS", v8::Uint32::New(isolate, 0x8C83));

    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BUFFER_START", v8::Uint32::New(isolate, 0x8C84));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BUFFER_SIZE", v8::Uint32::New(isolate, 0x8C85));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN", v8::Uint32::New(isolate, 0x8C88));
    tmpl->Set(isolate, "MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS", v8::Uint32::New(isolate, 0x8C8A));

    /* Textures */

    /* Pixel types */

    tmpl->Set(isolate, "MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS", v8::Uint32::New(isolate, 0x8C8B));
    tmpl->Set(isolate, "INTERLEAVED_ATTRIBS", v8::Uint32::New(isolate, 0x8C8C));
    tmpl->Set(isolate, "SEPARATE_ATTRIBS", v8::Uint32::New(isolate, 0x8C8D));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BUFFER", v8::Uint32::New(isolate, 0x8C8E));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BUFFER_BINDING", v8::Uint32::New(isolate, 0x8C8F));

    tmpl->Set(isolate, "TRANSFORM_FEEDBACK", v8::Uint32::New(isolate, 0x8E22));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_PAUSED", v8::Uint32::New(isolate, 0x8E23));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_ACTIVE", v8::Uint32::New(isolate, 0x8E24));
    tmpl->Set(isolate, "TRANSFORM_FEEDBACK_BINDING", v8::Uint32::New(isolate, 0x8E25));

    /* Pixel types */

    /* Queries */

    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING", v8::Uint32::New(isolate, 0x8210));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE", v8::Uint32::New(isolate, 0x8211));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_RED_SIZE", v8::Uint32::New(isolate, 0x8212));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_GREEN_SIZE", v8::Uint32::New(isolate, 0x8213));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_BLUE_SIZE", v8::Uint32::New(isolate, 0x8214));

    /* Queries */

    /* Draw buffers */

    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE", v8::Uint32::New(isolate, 0x8215));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE", v8::Uint32::New(isolate, 0x8216));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE", v8::Uint32::New(isolate, 0x8217));
    tmpl->Set(isolate, "FRAMEBUFFER_DEFAULT", v8::Uint32::New(isolate, 0x8218));
    tmpl->Set(isolate, "DEPTH_STENCIL_ATTACHMENT", v8::Uint32::New(isolate, 0x821A));

    tmpl->Set(isolate, "DEPTH_STENCIL", v8::Uint32::New(isolate, 0x84F9));
    tmpl->Set(isolate, "DEPTH24_STENCIL8", v8::Uint32::New(isolate, 0x88F0));
    tmpl->Set(isolate, "DRAW_FRAMEBUFFER_BINDING", v8::Uint32::New(isolate, 0x8CA6));
    tmpl->Set(isolate, "READ_FRAMEBUFFER", v8::Uint32::New(isolate, 0x8CA8));
    tmpl->Set(isolate, "DRAW_FRAMEBUFFER", v8::Uint32::New(isolate, 0x8CA9));

    tmpl->Set(isolate, "READ_FRAMEBUFFER_BINDING", v8::Uint32::New(isolate, 0x8CAA));
    tmpl->Set(isolate, "RENDERBUFFER_SAMPLES", v8::Uint32::New(isolate, 0x8CAB));
    tmpl->Set(isolate, "FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER", v8::Uint32::New(isolate, 0x8CD4));
    tmpl->Set(isolate, "FRAMEBUFFER_INCOMPLETE_MULTISAMPLE", v8::Uint32::New(isolate, 0x8D56));
    tmpl->Set(isolate, "UNIFORM_BUFFER", v8::Uint32::New(isolate, 0x8A11));

    tmpl->Set(isolate, "UNIFORM_BUFFER_BINDING", v8::Uint32::New(isolate, 0x8A28));
    tmpl->Set(isolate, "UNIFORM_BUFFER_START", v8::Uint32::New(isolate, 0x8A29));
    tmpl->Set(isolate, "UNIFORM_BUFFER_SIZE", v8::Uint32::New(isolate, 0x8A2A));
    tmpl->Set(isolate, "MAX_VERTEX_UNIFORM_BLOCKS", v8::Uint32::New(isolate, 0x8A2B));
    tmpl->Set(isolate, "MAX_FRAGMENT_UNIFORM_BLOCKS", v8::Uint32::New(isolate, 0x8A2D));

    tmpl->Set(isolate, "MAX_COMBINED_UNIFORM_BLOCKS", v8::Uint32::New(isolate, 0x8A2E));
    tmpl->Set(isolate, "MAX_UNIFORM_BUFFER_BINDINGS", v8::Uint32::New(isolate, 0x8A2F));
    tmpl->Set(isolate, "MAX_UNIFORM_BLOCK_SIZE", v8::Uint32::New(isolate, 0x8A30));
    tmpl->Set(isolate, "MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS", v8::Uint32::New(isolate, 0x8A31));
    tmpl->Set(isolate, "MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS", v8::Uint32::New(isolate, 0x8A33));

    tmpl->Set(isolate, "UNIFORM_BUFFER_OFFSET_ALIGNMENT", v8::Uint32::New(isolate, 0x8A34));
    tmpl->Set(isolate, "ACTIVE_UNIFORM_BLOCKS", v8::Uint32::New(isolate, 0x8A36));
    tmpl->Set(isolate, "UNIFORM_TYPE", v8::Uint32::New(isolate, 0x8A37));
    tmpl->Set(isolate, "UNIFORM_SIZE", v8::Uint32::New(isolate, 0x8A38));
    tmpl->Set(isolate, "UNIFORM_BLOCK_INDEX", v8::Uint32::New(isolate, 0x8A3A));

    tmpl->Set(isolate, "UNIFORM_OFFSET", v8::Uint32::New(isolate, 0x8A3B));
    tmpl->Set(isolate, "UNIFORM_ARRAY_STRIDE", v8::Uint32::New(isolate, 0x8A3C));
    tmpl->Set(isolate, "UNIFORM_MATRIX_STRIDE", v8::Uint32::New(isolate, 0x8A3D));

    /* Draw buffers */

    /* Samplers */

    tmpl->Set(isolate, "UNIFORM_IS_ROW_MAJOR", v8::Uint32::New(isolate, 0x8A3E));
    tmpl->Set(isolate, "UNIFORM_BLOCK_BINDING", v8::Uint32::New(isolate, 0x8A3F));
    tmpl->Set(isolate, "UNIFORM_BLOCK_DATA_SIZE", v8::Uint32::New(isolate, 0x8A40));
    tmpl->Set(isolate, "UNIFORM_BLOCK_ACTIVE_UNIFORMS", v8::Uint32::New(isolate, 0x8A42));
    tmpl->Set(isolate, "UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES", v8::Uint32::New(isolate, 0x8A43));

    tmpl->Set(isolate, "UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER", v8::Uint32::New(isolate, 0x8A44));
    tmpl->Set(isolate, "UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER", v8::Uint32::New(isolate, 0x8A46));
    tmpl->Set(isolate, "OBJECT_TYPE", v8::Uint32::New(isolate, 0x9112));
    tmpl->Set(isolate, "SYNC_CONDITION", v8::Uint32::New(isolate, 0x9113));
    tmpl->Set(isolate, "SYNC_STATUS", v8::Uint32::New(isolate, 0x9114));

    tmpl->Set(isolate, "SYNC_FLAGS", v8::Uint32::New(isolate, 0x9115));
    tmpl->Set(isolate, "SYNC_FENCE", v8::Uint32::New(isolate, 0x9116));
    tmpl->Set(isolate, "SYNC_GPU_COMMANDS_COMPLETE", v8::Uint32::New(isolate, 0x9117));
    tmpl->Set(isolate, "UNSIGNALED", v8::Uint32::New(isolate, 0x9118));
    tmpl->Set(isolate, "SIGNALED", v8::Uint32::New(isolate, 0x9119));

    /* Samplers */

    /* Buffers */

    tmpl->Set(isolate, "ALREADY_SIGNALED", v8::Uint32::New(isolate, 0x911A));
    tmpl->Set(isolate, "TIMEOUT_EXPIRED", v8::Uint32::New(isolate, 0x911B));
    tmpl->Set(isolate, "CONDITION_SATISFIED", v8::Uint32::New(isolate, 0x911C));
    tmpl->Set(isolate, "WAIT_FAILED", v8::Uint32::New(isolate, 0x911D));
    tmpl->Set(isolate, "SYNC_FLUSH_COMMANDS_BIT", v8::Uint32::New(isolate, 0x00000001));

    tmpl->Set(isolate, "COLOR", v8::Uint32::New(isolate, 0x1800));
    tmpl->Set(isolate, "DEPTH", v8::Uint32::New(isolate, 0x1801));
    tmpl->Set(isolate, "STENCIL", v8::Uint32::New(isolate, 0x1802));

    /* Buffers */

    /* Data types */

    tmpl->Set(isolate, "MIN", v8::Uint32::New(isolate, 0x8007));
    tmpl->Set(isolate, "MAX", v8::Uint32::New(isolate, 0x8008));
    tmpl->Set(isolate, "DEPTH_COMPONENT24", v8::Uint32::New(isolate, 0x81A6));
    tmpl->Set(isolate, "STREAM_READ", v8::Uint32::New(isolate, 0x88E1));
    tmpl->Set(isolate, "STREAM_COPY", v8::Uint32::New(isolate, 0x88E2));

    tmpl->Set(isolate, "STATIC_READ", v8::Uint32::New(isolate, 0x88E5));
    tmpl->Set(isolate, "STATIC_COPY", v8::Uint32::New(isolate, 0x88E6));
    tmpl->Set(isolate, "DYNAMIC_READ", v8::Uint32::New(isolate, 0x88E9));
    tmpl->Set(isolate, "DYNAMIC_COPY", v8::Uint32::New(isolate, 0x88EA));
    tmpl->Set(isolate, "DEPTH_COMPONENT32F", v8::Uint32::New(isolate, 0x8CAC));
    tmpl->Set(isolate, "DEPTH32F_STENCIL8", v8::Uint32::New(isolate, 0x8CAD));

    /* Data types */

    tmpl->Set(isolate, "INVALID_INDEX", v8::Uint32::New(isolate, 0xFFFFFFFF));
    tmpl->Set(isolate, "TIMEOUT_IGNORED", v8::Int32::New(isolate, -1));

    /* Vertex attributes */

    /* Transform feedback */

    tmpl->Set(isolate, "MAX_CLIENT_WAIT_TIMEOUT_WEBGL", v8::Uint32::New(isolate, 0x9247));

    /* Transform feedback */

}

void WebGL2RenderingContext::SetProps(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> webgl2RenderingContextTpl) {}

void WebGL2RenderingContext::SetMethods(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> webgl2RenderingContextTpl) {

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "beginQuery"),
            v8::FunctionTemplate::New(isolate, &BeginQuery)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "beginTransformFeedback"),
            v8::FunctionTemplate::New(isolate, &BeginTransformFeedback)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "bindBufferBase"),
            v8::FunctionTemplate::New(isolate, &BindBufferBase)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "bindBufferRange"),
            v8::FunctionTemplate::New(isolate, &BindBufferRange)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "bindSampler"),
            v8::FunctionTemplate::New(isolate, &BindSampler)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "bindTransformFeedback"),
            v8::FunctionTemplate::New(isolate, &BindTransformFeedback)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "bindVertexArray"),
            v8::FunctionTemplate::New(isolate, &BindVertexArray)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "blitFramebuffer"),
            v8::FunctionTemplate::New(isolate, &BlitFramebuffer)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "clearBufferfi"),
            v8::FunctionTemplate::New(isolate, &ClearBufferfi)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "clearBufferfv"),
            v8::FunctionTemplate::New(isolate, &ClearBufferfv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "clearBufferiv"),
            v8::FunctionTemplate::New(isolate, &ClearBufferiv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "clearBufferuiv"),
            v8::FunctionTemplate::New(isolate, &ClearBufferuiv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "clientWaitSync"),
            v8::FunctionTemplate::New(isolate, &ClientWaitSync)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "compressedTexSubImage3D"),
            v8::FunctionTemplate::New(isolate, &CompressedTexSubImage3D)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "copyBufferSubData"),
            v8::FunctionTemplate::New(isolate, &CopyBufferSubData)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "copyTexSubImage3D"),
            v8::FunctionTemplate::New(isolate, &CopyTexSubImage3D)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "createQuery"),
            v8::FunctionTemplate::New(isolate, &CreateQuery)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "createSampler"),
            v8::FunctionTemplate::New(isolate, &CreateSampler)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "createTransformFeedback"),
            v8::FunctionTemplate::New(isolate, &CreateTransformFeedback)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "createVertexArray"),
            v8::FunctionTemplate::New(isolate, &CreateVertexArray)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "deleteQueryWithQuery"),
            v8::FunctionTemplate::New(isolate, &DeleteQueryWithQuery)
    );


    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "deleteSamplerWithSampler"),
            v8::FunctionTemplate::New(isolate, &DeleteSamplerWithSampler)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "deleteSyncWithSync"),
            v8::FunctionTemplate::New(isolate, &DeleteSyncWithSync)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "deleteTransformFeedback"),
            v8::FunctionTemplate::New(isolate, &DeleteTransformFeedback)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "deleteVertexArrayWithVertexArray"),
            v8::FunctionTemplate::New(isolate, &DeleteVertexArrayWithVertexArray)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "drawArraysInstanced"),
            v8::FunctionTemplate::New(isolate, &DrawArraysInstanced)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "drawBuffers"),
            v8::FunctionTemplate::New(isolate, &DrawBuffers)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "drawElementsInstanced"),
            v8::FunctionTemplate::New(isolate, &DrawElementsInstanced)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "drawRangeElements"),
            v8::FunctionTemplate::New(isolate, &DrawRangeElements)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "endQuery"),
            v8::FunctionTemplate::New(isolate, &EndQuery)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "endTransformFeedback"),
            v8::FunctionTemplate::New(isolate, &EndTransformFeedback)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "fenceSync"),
            v8::FunctionTemplate::New(isolate, &FenceSync)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "framebufferTextureLayer"),
            v8::FunctionTemplate::New(isolate, &FramebufferTextureLayer)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform1ui"),
            v8::FunctionTemplate::New(isolate, &Uniform1ui)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform1uiv"),
            v8::FunctionTemplate::New(isolate, &Uniform1uiv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform2ui"),
            v8::FunctionTemplate::New(isolate, &Uniform2ui)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform2uiv"),
            v8::FunctionTemplate::New(isolate, &Uniform2uiv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform3ui"),
            v8::FunctionTemplate::New(isolate, &Uniform3ui)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform3uiv"),
            v8::FunctionTemplate::New(isolate, &Uniform3uiv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform4ui"),
            v8::FunctionTemplate::New(isolate, &Uniform4ui)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniform4uiv"),
            v8::FunctionTemplate::New(isolate, &Uniform4uiv)
    );


    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformBlockBinding"),
            v8::FunctionTemplate::New(isolate, &UniformBlockBinding)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix2x3fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix2x3fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix2x4fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix2x4fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix3x2fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix3x2fv)
    );


    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix3x4fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix3x4fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix4x2fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix4x2fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix4x3fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix4x3fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "uniformMatrix4x3fv"),
            v8::FunctionTemplate::New(isolate, &UniformMatrix4x3fv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "vertexAttribDivisor"),
            v8::FunctionTemplate::New(isolate, &VertexAttribDivisor)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "vertexAttribI4i"),
            v8::FunctionTemplate::New(isolate, &VertexAttribI4i)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "vertexAttribI4iv"),
            v8::FunctionTemplate::New(isolate, &VertexAttribI4iv)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "vertexAttribI4ui"),
            v8::FunctionTemplate::New(isolate, &VertexAttribI4ui)
    );

    webgl2RenderingContextTpl->Set(
            Helpers::ConvertToV8String(isolate, "vertexAttribI4uiv"),
            v8::FunctionTemplate::New(isolate, &VertexAttribI4uiv)
    );

}

void WebGL2RenderingContext::GetActiveUniformBlockName(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, uniformBlockIndex: number
// string
}

void WebGL2RenderingContext::GetActiveUniformBlockParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, uniformBlockIndex: number, pname: number
// any
}

void WebGL2RenderingContext::GetActiveUniforms(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, uniformIndices: number[], pname: number
// any
}

void WebGL2RenderingContext::GetBufferSubData(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, srcByteOffset: number, dstData: ArrayBuffer, dstOffset?: number, length?: number
}

void WebGL2RenderingContext::GetFragDataLocation(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, name: string
//number
}

void WebGL2RenderingContext::GetIndexedParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, index: number
// any
}

void WebGL2RenderingContext::GetInternalformatParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, internalformat: number, pname: number
// any
}

void WebGL2RenderingContext::GetQueryParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// query: WebGLQuery, pname: number
// any
}

void WebGL2RenderingContext::GetQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, pname: number
// any
}

void WebGL2RenderingContext::GetSamplerParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sampler: WebGLSampler, pname: number
// any
}

void WebGL2RenderingContext::GetSyncParameter(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sync: WebGLSync, pname: number
// any
}

void WebGL2RenderingContext::GetTransformFeedbackVarying(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, index: number
// any
}

void WebGL2RenderingContext::GetUniformBlockIndex(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, uniformBlockName: string
// number
}

void WebGL2RenderingContext::GetUniformIndices(const v8::FunctionCallbackInfo<v8::Value> &args) {
// program: WebGLProgram, uniformNames: string[]
// number[]
}

void WebGL2RenderingContext::InvalidateFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, attachments: number[]
}

void WebGL2RenderingContext::InvalidateSubFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, attachments: number[], x: number, y: number, width: number, height: number
}

void WebGL2RenderingContext::IsQuery(const v8::FunctionCallbackInfo<v8::Value> &args) {
// query: WebGLQuery
// boolean
}

void WebGL2RenderingContext::IsSampler(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sampler: WebGLSampler
// boolean
}

void WebGL2RenderingContext::IsSync(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sync: WebGLSync
// boolean
}

void WebGL2RenderingContext::IsTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {
// transformFeedback: WebGLTransformFeedback
// boolean
}

void WebGL2RenderingContext::IsVertexArray(const v8::FunctionCallbackInfo<v8::Value> &arg) {
// vertexArray: WebGLVertexArrayObject
// boolean
}

void WebGL2RenderingContext::PauseTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {

}

void WebGL2RenderingContext::ReadBuffer(const v8::FunctionCallbackInfo<v8::Value> &args) {
// src: number
}

void WebGL2RenderingContext::RenderbufferStorageMultisample(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, samples: number, internalFormat: number, width: number, height: number
}

void WebGL2RenderingContext::ResumeTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args) {

}

void WebGL2RenderingContext::SamplerParameterf(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sampler: WebGLSampler, pname: number, param: number
}


void WebGL2RenderingContext::SamplerParameteri(const v8::FunctionCallbackInfo<v8::Value> &args) {
// sampler: WebGLSampler, pname: number, param: number
}

void WebGL2RenderingContext::TexImage3D(const v8::FunctionCallbackInfo<v8::Value> &args) {
// target: number, level: number, internalformat: number, width: number, height: number, depth: number, border: number, format: number, type: number, offset: any
// target, level, internalformat, width, height, depth, border, format, type, srcData, srcOffset
}

void WebGL2RenderingContext::TexStorage2D(const v8::FunctionCallbackInfo<v8::Value> &arg) {
//target: number, levels: number, internalformat: number, width: number, height: number
}

void WebGL2RenderingContext::TexStorage3D(const v8::FunctionCallbackInfo<v8::Value> &arg) {
// target: number, levels: number, internalformat: number, width: number, height: number, depth: number
}

void WebGL2RenderingContext::TexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &arg) {
// target: number, level: number, xoffset: number, yoffset: number, zoffset: number, width: number, height: number, depth: number, format: number, type: number, offset: any
// target: number, level: number, xoffset: number, yoffset: number, zoffset: number, width: number, height: number, depth: number, format: number, type: number, srcData: any, srcOffset
}

void WebGL2RenderingContext::TransformFeedbackVaryings(const v8::FunctionCallbackInfo<v8::Value> &arg) {
// program: WebGLProgram, varyings: string[], bufferMode: number
}

