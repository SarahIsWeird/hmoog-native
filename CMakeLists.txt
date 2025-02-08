# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# DO NOT USE TO BUILD THE PROJECT!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# This is only here for IDE autocompletes!

cmake_minimum_required(VERSION 3.30)
project(hmoog_native)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

if(WIN32)
    include_directories(
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/include/node"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/src"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/deps/openssl/config"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/deps/openssl/openssl/include"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/deps/uv/include"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/deps/zlib"
            "$ENV{LOCALAPPDATA}/node-gyp/Cache/22.13.0/deps/v8/include")

    add_compile_definitions(
            WIN32
            HOST_BINARY=node.exe
    )

    set(target win32)
endif()

add_compile_definitions(
        NODE_GYP_MODULE_NAME=hmoog-native
        USING_UV_SHARED=1
        USING_V8_SHARED=1
        V8_DEPRECATION_WARNINGS=1
        _GLIBCXX_USE_CXX11_ABI=1
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE
        _HAS_EXCEPTIONS=0
        NOMINMAX
        OPENSSL_NO_PINSHARED
        OPENSSL_THREADS
        BUILDING_NODE_EXTENSION
        DEBUG
        _DEBUG)

add_executable(hmoog_native
        src/native-${target}.cpp
        src/native.cpp
        src/native.hpp)
