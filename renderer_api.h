#ifndef RENDERER_API_H
#define RENDERER_API_H
#include <EGL/egl.h>
#include <GLES3/gl3.h>

struct EGLState {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
};

namespace RendererAPI {
    void Init(EGLState state);
    void Shutdown();
    void BeginFrame();
    void EndFrame();
    GLuint CreateShader(const char* vertex_source, const char* fragment_source);
    void DestroyShader(GLuint program);
    void BindShader(GLuint program);
}

#endif //RENDERER_API_H