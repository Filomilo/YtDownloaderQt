//
// Created by fboro on 01/03/2024.
//

#include "YoutubeDownloader.h"
YoutubeDownloader* YoutubeDownloader::instance = nullptr;

std::vector<YoutubeVideo> YoutubeDownloader::getVideos() {
    return this->videosList;
}
