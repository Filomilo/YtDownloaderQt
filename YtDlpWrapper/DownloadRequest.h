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
#include "Logger.h"
class DownloadRequest {
public:
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

    std::string &getLocation() ;

    void setLocation( std::string location) {
        Logger::info("location set: "+ location);
        this->location = location;
    }
    DownloadRequest(const YoutubeVideo* ytVideo, const std::string &location);

   
    void execute();

    void setVideoStart(std::string d);

    void setVideoStop(std::string d);
    void setFormat(std::string format)
    {
           Logger::info("set fOMrat : "+format);
        this->format=format;
    }


    DownloadRequest();

    virtual ~DownloadRequest();

    void setYtVideo(YoutubeVideo *ytVideo);

    DownloadRequest(YoutubeVideo *ytVideo, const std::string &location);

    YtDlmCommand getCommand();

    std::string toString() {
        std::ostringstream os;
        os << "ytVideo: " << this->ytVideo << " location: " << this->location << " timeStampStart: "
           << this->timeStampStart << " timeStampStop: " << this->timeStampStop << " format: " << this->format
           << " blocks: " << this->blocks.size() << " res: " << this->res;
        return os.str();
    }

        void setBlocks(const std::vector<std::string> &blocks);

    void setRes(int i);


    void executeWithFeeback(void (*param)(int,int));

    friend std::ostream &operator<<(std::ostream &os, const DownloadRequest &request);

    void setIsAudio(bool b);

    bool isAudio=false;

    bool getIsAudio() const;

    std::string getSaveLocation();

    void setOverwriteName(bool state);

    bool IsOverwriteName=false;
};


#endif //YTDLPWRAPPER_DOWNLOADREQUEST_H
