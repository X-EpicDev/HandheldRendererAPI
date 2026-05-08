cmake_minimum_required(VERSION 3.20)
project(RendererAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# ── Imported libs ────────────────────────────────────────
add_library(libEGL SHARED IMPORTED)
set_target_properties(libEGL PROPERTIES
        IMPORTED_LOCATION ${EXTERNAL_DIR}/lib/libEGL.so
)

add_library(libGLESv2 SHARED IMPORTED)
set_target_properties(libGLESv2 PROPERTIES
        IMPORTED_LOCATION ${EXTERNAL_DIR}/lib/libGLESv2.so
)

add_library(libMali SHARED IMPORTED)
set_target_properties(libMali PROPERTIES
        IMPORTED_LOCATION ${EXTERNAL_DIR}/lib/libMali.so
)

# ── Renderer API ─────────────────────────────────────────
add_library(RendererAPI SHARED
        renderer_api.cpp
        threads/renderer_thread.cpp
)

target_include_directories(RendererAPI PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${EXTERNAL_DIR}/include
)

target_link_libraries(RendererAPI
        PRIVATE libEGL
        PRIVATE libGLESv2
        PRIVATE libMali
)