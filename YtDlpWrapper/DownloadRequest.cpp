//
// Created by fboro on 05/03/2024.
//

#include "DownloadRequest.h"

const YoutubeVideo &DownloadRequest::getYtVideo() const {
    return ytVideo;
}

void DownloadRequest::setYtVideo(const YoutubeVideo &ytVideo) {
    DownloadRequest::ytVideo = ytVideo;
}

const std::string &DownloadRequest::getLocation() const {
    return location;
}

void DownloadRequest::setLocation(const std::string &location) {
    DownloadRequest::location = location;
}

DownloadRequest::DownloadRequest(const YoutubeVideo &ytVideo, const std::string &location) : ytVideo(ytVideo),
                                                                                             location(location) {}


