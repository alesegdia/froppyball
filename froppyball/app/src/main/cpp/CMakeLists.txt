cmake_minimum_required(VERSION 3.4.1)

set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# SIMPLE ANDROID GAMEDEV LIBRARY
add_library(sagl STATIC
    sagl/application.cpp
    sagl/core.cpp
    sagl/input.cpp
    sagl/math.cpp
    sagl/shader.cpp
    sagl/renderer.cpp
    sagl/gpubuffer.cpp
    sagl/renderableprimitive.cpp
    sagl/camera.cpp)

target_include_directories(sagl PUBLIC
    ${ANDROID_NDK}/sources/android/native_app_glue)

target_link_libraries(sagl PUBLIC
    android
    native_app_glue
    EGL
    GLESv2
    log)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(froppyball SHARED
    main.cpp
    froppyballapplication.cpp
    stage.cpp
    entities.cpp)

target_link_libraries(froppyball
    sagl)