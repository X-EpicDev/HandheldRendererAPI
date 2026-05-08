#include "renderer_api.h"
#include "threads/renderer_thread.h"
#include <cstdio>

namespace RendererAPI {

    static EGLState render_state;

    void Init(EGLState state) {
        render_state = state;
        RendererThread::Start(state);
    }

    void Shutdown() {
        RendererThread::Stop();
    }

    void BeginFrame() {
        glViewport(0, 0, 480, 272);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void EndFrame() {
        eglSwapBuffers(render_state.display, render_state.surface);
    }

    GLuint CreateShader(const char* vertex_source, const char* fragment_source) {
        // vertex shader
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
        glCompileShader(vertex_shader);

        GLint success;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
            printf("Vertex Shader Error: %s\n", info_log);
            glDeleteShader(vertex_shader);
            return 0;
        }

        // fragment shader
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
            printf("Fragment Shader Error: %s\n", info_log);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            return 0;
        }

        // shader program
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetProgramInfoLog(program, 512, nullptr, info_log);
            printf("Program Link Error: %s\n", info_log);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            glDeleteProgram(program);
            return 0;
        }

        // cleanup
        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

    void DestroyShader(GLuint program) {
        glDeleteProgram(program);
    }

    void BindShader(GLuint program) {
        glUseProgram(program);
    }
}