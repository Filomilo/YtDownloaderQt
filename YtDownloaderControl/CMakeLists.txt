cmake_minimum_required(VERSION 3.27)
project(YtDlpWrapper)

set(CMAKE_CXX_STANDARD 17)

add_library(YtDlpWrapper STATIC library.cpp)
add_library(YoutubeDownloader YoutubeDownloader.cpp YoutubeDownloader.h)
target_link_libraries(YoutubeDownloader)