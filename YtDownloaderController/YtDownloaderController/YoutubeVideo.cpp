//
// Created by fboro on 01/03/2024.
//

#include "YoutubeVideo.h"

 YoutubeDownloader* YoutubeDownloader::getInstance(){
    if( YoutubeDownloader::instance== nullptr)
    {
        YoutubeDownloader::instance=new YoutubeDownloader;
    }
    return  YoutubeDownloader::instance;
}