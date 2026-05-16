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

/*
- DO FIRST -
Init() - starts up the rendering stuff and the thread - DONE
Shutdown() - safely shutdown the thread and any other data is safely destroyed - DONE

=====================================================================================================================
- SETUP BEFORE QUEUE -
EGLState Struct - DONE

BeginFrame() - Starts a new frame (clear screen, reset state) - DONE
EndFrame() - Ends frame (right now would swap buffers, later just “finish queue frame”) - MOSTLY DONE (swaps buffers)
IsInitialized() - Checks if renderer is ready (useful for safety/debug)
SetViewport() - Tells GPU what area of screen to draw to
SetClearColor() - Sets background color when clearing screen

CreateShader() - Makes a GPU program (vertex + fragment shader) - DONE
BindShader() - IDK what this does, claude said i needed it (I do not know how to do GPU stuff lol, but im learning) - DONE
CreateVertexBuffer() - Creates memory on GPU for vertex data
UploadVertexBufferData() - Fills vertex buffer with data
CreateIndexBuffer() - Creates buffer for triangle indices
UploadIndexBufferData() - Fills index buffer
CreateTexture2D() - Creates an image/texture on GPU
UploadTextureData() - Uploads pixels into a texture

WaitForGPU() - Stops CPU until GPU finishes rendering (debug)

(cleanup)
DestroyShader() - Destroys GPU program (vertex + fragment shader) - DONE
DestroyVertexBuffer() - Destroys VBOs
DestroyIndexBuffer() - Destroys IBOs
DestroyTexture() - Destroys Texture

=====================================================================================================================
- SETUP ALONGSIDE QUEUE SYSTEM -
DrawCommand Struct

SubmitRenderCommand() - Adds a “draw instruction” into the frame queue
FlushRenderQueue() - Forces all queued commands to run immediately (debug)
DrawArrays() - Add a command to draw vertices in order
DrawIndexed() - Add a command to draw using indices (more efficient)

=====================================================================================================================
- POST QUEUE SYSTEM -
SetUniformMat4() - Sends matrix (like camera or transform) to shader
SetUniformVec4() - Sends 4-number values (color, etc.)
SetUniformFloat() - Sends single float value
SetUniformInt() - Sends integer value
*/

#endif //RENDERER_API_H