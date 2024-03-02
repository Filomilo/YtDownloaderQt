//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
#define YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
#include <vector>
#include "YoutubeVideo.h"
#include <future>
#include "Logger.h"
class YoutubeDownloader {
private:
    std::vector<YoutubeVideo> videosList;
    static YoutubeDownloader* instance;
    YoutubeDownloader(){
    }

public:
    static YoutubeDownloader* getInstance(){
        if( YoutubeDownloader::instance== nullptr)
        {
            YoutubeDownloader::instance=new YoutubeDownloader;
        }
        return  YoutubeDownloader::instance;
    }

    bool loadFiles(std::string link)
    {
        try {
            Logger::info("Loaing files form link: " + link);
        }
        catch (std::exception ex)
        {
            Logger::error("errror while loading files from link: "+std::string(ex.what()));
            return false;
        }

        return true;
    }



};






#endif //YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
