pub mod bridges;
pub mod gl_context;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("canvas-android-v8/src/Bridge.h");
        pub(crate) type V8FunctionCallbackInfo;
        pub(crate) fn Init(args: &V8FunctionCallbackInfo);
    }
}

#[no_mangle]
extern "C" fn NSMain(args: &ffi::V8FunctionCallbackInfo) {
    unsafe {
        ffi::Init(args);
    }
}