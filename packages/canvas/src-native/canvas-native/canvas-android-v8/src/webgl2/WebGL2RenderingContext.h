//
// Created by Osei Fortune on 22/03/2022.
//

#pragma once

#include <cmath>
#include "../Common.h"
#include "../Caches.h"
#include "../Helpers.h"
#include "../webgl/WebGLRenderingContext.h"
#include "WebGLQuery.h"
#include "WebGLSampler.h"
#include "WebGLSyncImpl.h"
#include "WebGLTransformFeedback.h"
#include "WebGLVertexArrayObject.h"

#include "../webgl/WebGLRenderingContextBase.h"


class WebGL2RenderingContext : WebGLRenderingContextBase {
public:
    static void Init(v8::Isolate *isolate);

    WebGL2RenderingContext(rust::Box<WebGLState> state);

    ~WebGL2RenderingContext();

    static void Create(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void InstanceFromPointer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void SetConstants(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> tmpl);

    static void SetProps(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> webgl2RenderingContextTpl);

    static void SetMethods(v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> webgl2RenderingContextTpl);

    static void BeginQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BeginTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BindBufferBase(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BindBufferRange(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BindSampler(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BindTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BindVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void BlitFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ClearBufferfi(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ClearBufferfv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ClearBufferiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ClearBufferuiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ClientWaitSync(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CompressedTexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CopyBufferSubData(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CopyTexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CreateQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CreateSampler(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CreateTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void CreateVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DeleteQueryWithQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DeleteSamplerWithSampler(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DeleteSyncWithSync(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DeleteTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DeleteVertexArrayWithVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DrawArraysInstanced(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DrawBuffers(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DrawElementsInstanced(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void DrawRangeElements(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void EndQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void EndTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void FenceSync(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void FramebufferTextureLayer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetActiveUniformBlockName(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetActiveUniformBlockParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetActiveUniforms(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetBufferSubData(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetFragDataLocation(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetIndexedParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetInternalformatParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetQueryParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetSamplerParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetSyncParameter(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetTransformFeedbackVarying(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetUniformBlockIndex(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void GetUniformIndices(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void InvalidateFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void InvalidateSubFramebuffer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void IsQuery(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void IsSampler(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void IsSync(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void IsTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void IsVertexArray(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void PauseTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ReadBuffer(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void RenderbufferStorageMultisample(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void ResumeTransformFeedback(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void SamplerParameterf(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void SamplerParameteri(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void TexImage3D(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void TexStorage2D(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void TexStorage3D(const v8::FunctionCallbackInfo<v8::Value> &arg);

    static void TexSubImage3D(const v8::FunctionCallbackInfo<v8::Value> &arg);

    static void TransformFeedbackVaryings(const v8::FunctionCallbackInfo<v8::Value> &arg);

    static void Uniform1ui(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform1uiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform2ui(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform2uiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform3ui(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform3uiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform4ui(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Uniform4uiv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformBlockBinding(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix2x3fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix2x4fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix3x2fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix3x4fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix4x2fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void UniformMatrix4x3fv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void VertexAttribDivisor(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void VertexAttribI4i(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void VertexAttribI4iv(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void VertexAttribI4ui(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void VertexAttribI4uiv(const v8::FunctionCallbackInfo<v8::Value> &args);

private:

    static WebGL2RenderingContext *GetPointer(v8::Local<v8::Object> object);

    static WebGL2RenderingContextBase *GetPointerBase(v8::Local<v8::Object> object);

    static v8::Local<v8::FunctionTemplate> GetCtor(v8::Isolate *isolate);
};
