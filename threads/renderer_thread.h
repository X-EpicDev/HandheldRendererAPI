#ifndef RENDERER_THREAD_H
#define RENDERER_THREAD_H

#include <atomic>
#include <thread>
#include "../renderer_api.h"

namespace RendererThread {
    void Start(EGLState state);
    void Stop();
}

#endif //RENDERER_THREAD_H