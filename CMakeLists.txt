cmake_minimum_required(VERSION 3.7)

project(QtVideoPlayer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(
        FFmpeg
        REQUIRED
        COMPONENTS
        avformat
        avutil
        swscale
        swresample
        avfilter
        avdevice
        avcodec)

if(${FFMPEG_FOUND})
    include_directories(${FFMPEG_INCLUDE_DIRS})
    message(${FFMPEG_INCLUDE_DIRS})
endif(${FFMPEG_FOUND})

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED QUIET)

set(
        SRC_HEADERS

        video/video_player.h
        video/main_window.h

        video/data/data_context.h
        video/data/audio_cvt.h
        video/data/image_cvt.h

        video/input/input_format.h
        video/input/input_thread.h

        video/render/audio_thread.h
        video/render/video_thread.h
        video/render/audio_render.h
        video/render/video_render.h
)

set(
        SRC_CPPS

        video/main.cpp

        video/video_player.cpp
        video/main_window.cpp

        video/data/data_context.cpp
        video/data/audio_cvt.cpp
        video/data/image_cvt.cpp

        video/input/input_format.cpp
        video/input/input_thread.cpp

        video/render/audio_thread.cpp
        video/render/video_thread.cpp
        video/render/audio_render.cpp
        video/render/video_render.cpp
)

add_executable(
        QtVideoPlayer
        ${SRC_HEADERS}
        ${SRC_CPPS}
        )

target_link_libraries(
        QtVideoPlayer
        Qt5::Widgets
        Qt5::Multimedia
        ${FFMPEG_LIBRARIES}
)