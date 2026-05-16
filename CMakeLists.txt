cmake_minimum_required(VERSION 3.20)
project(HandheldRendererAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ── External libs ─────────────────────────────────────────────────────────────
# find_library searches CMAKE_SYSROOT/usr/lib automatically via the toolchain file.
# No external/ directory or hardcoded paths needed.
find_library(EGL_LIB    NAMES EGL    REQUIRED)
find_library(GLESV2_LIB NAMES GLESv2 REQUIRED)
find_library(MALI_LIB   NAMES Mali   REQUIRED)

find_path(EGL_INCLUDE_DIR  NAMES EGL/egl.h   REQUIRED)
find_path(GLES_INCLUDE_DIR NAMES GLES3/gl3.h REQUIRED)

# ── RendererAPI ───────────────────────────────────────────────────────────────
add_library(RendererAPI SHARED
        renderer_api.cpp
        threads/renderer_thread.cpp
)

target_include_directories(RendererAPI
        PUBLIC  ${CMAKE_SOURCE_DIR}        # renderer_api.h — consumers get this automatically
        PRIVATE ${EGL_INCLUDE_DIR}
        ${GLES_INCLUDE_DIR}
)

target_link_libraries(RendererAPI PRIVATE
        ${EGL_LIB}
        ${GLESV2_LIB}
        ${MALI_LIB}
)

# ── Install (cmake --install, or use as reference for manual scp paths) ───────
install(TARGETS RendererAPI LIBRARY DESTINATION /usr/lib)
install(FILES   renderer_api.h      DESTINATION /usr/include)
