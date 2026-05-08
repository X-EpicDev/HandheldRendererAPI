#include "renderer_thread.h"
#include <cstdio>

namespace RendererThread {

    static std::atomic<bool> running(false);
    static std::thread thread;
    static EGLState eglState;

    static void loop() {
        printf("RendererThread: running\n");
        eglMakeCurrent(eglState.display, eglState.surface, eglState.surface, eglState.context);

        while (running) {
            // drain render command queue
            // execute GLES calls
        }

        eglMakeCurrent(eglState.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        printf("RendererThread: stopped\n");
    }

    void Start(EGLState state) {
        printf("RendererThread: starting\n");
        eglState = state;
        running = true;
        thread = std::thread(loop);
    }

    void Stop() {
        printf("RendererThread: stopping\n");
        running = false;
        thread.join();
    }
}