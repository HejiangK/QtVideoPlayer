cmake_minimum_required(VERSION 3.7)

project(QtVideoPlayer)

set(CMAKE_CXX_STANDARD 11)

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
endif(${FFMPEG_FOUND})

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED QUIET)

set(
        SRC_HEADERS

        src/video_player.h
        src/main_window.h
)

set(
        SRC_CPPS

        src/main.cpp
        src/video_player.cpp
        src/main_window.cpp
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