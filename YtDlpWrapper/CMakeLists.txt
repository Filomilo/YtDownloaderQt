cmake_minimum_required(VERSION 3.25)
project(YtDlpWrapper)

set(CMAKE_CXX_STANDARD 17)

add_executable(YtDlpWrapper main.cpp    YoutubeDownloader.cpp Executor.cpp DownloadRequest.cpp DownloadRequest.h DownloadRequest.h DownloadRequest.cpp)
set(SOURCE_FILES
        main.cpp
        YoutubeDownloader.cpp
        )