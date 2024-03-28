//
// Created by fboro on 05/03/2024.
//
#pragma once
#ifndef YTDLPWRAPPER_DOWNLOADREQUEST_H
#define YTDLPWRAPPER_DOWNLOADREQUEST_H

#include <ostream>
#include "YoutubeVideo.h"
#include "Logger.h"
#include "YtDlmCommandBuilder.h"
#include "YtDlmCommand.h"
class DownloadRequest {
public:
    friend std::ostream &operator<<(std::ostream &os, const DownloadRequest &request);

private:
    YoutubeVideo* ytVideo;
    std::string location;
    std::string timeStampStart="0";
    std::string timeStampStop="inf";
     std::string format="";
    std::vector<std::string> blocks;
    int res=-1;
     void addLocation(const std::string &basicString);
void addRes(const std::string &basicString);
public:
    const YoutubeVideo* getYtVideo() const;

    const std::string &getLocation() const;

    void setLocation( std::string location) {
        Logger::info("location");
        this->location = location;
        Logger::info("location ens");
    }
    DownloadRequest(const YoutubeVideo* ytVideo, const std::string &location);

   
    void execute();

    void setVideoStart(std::string d);

    void setVideoStop(std::string d);
    void setFormat(std::string format)
    {
        this->format=format;
    }


    DownloadRequest();

    virtual ~DownloadRequest();

    void setYtVideo(YoutubeVideo *ytVideo);

    DownloadRequest(YoutubeVideo *ytVideo, const std::string &location);

    YtDlmCommand getCommand();

    std::string toString() {
        std::ostringstream os;
        os << "ytVideo: " << *this->ytVideo << " location: " << this->location << " timeStampStart: "
           << this->timeStampStart << " timeStampStop: " << this->timeStampStop << " blocks: " << this->blocks.size()
           << " res: " << this->res;
        return os.str();
    }

        void setBlocks(const std::vector<std::string> &blocks);

    void setRes(int i);


    void executeWithFeeback(void (*param)(int,int));
};


#endif //YTDLPWRAPPER_DOWNLOADREQUEST_H
