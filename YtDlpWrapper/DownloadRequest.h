//
// Created by fboro on 05/03/2024.
//

#ifndef YTDLPWRAPPER_DOWNLOADREQUEST_H
#define YTDLPWRAPPER_DOWNLOADREQUEST_H

#include <ostream>
#include "YoutubeVideo.h"
#include "Logger.h"
#include "YtDlmCommandBuilder.h"
#include "YtDlmCommand.h"
class DownloadRequest {
private:
    YoutubeVideo* ytVideo;
    std::string location;
    std::string timeStampStart="0";
    std::string timeStampStop="inf";
    std::vector<std::string> blocks;
    int res=-1;
public:
    const YoutubeVideo* getYtVideo() const;

    const std::string &getLocation() const;

    void setLocation( std::string location) {
        Logger::info("location");
        this->location = "location";
        Logger::info("location ens");
    }
    DownloadRequest(const YoutubeVideo* ytVideo, const std::string &location);

    void addLocation(const std::string &basicString);

    void execute();

    void setVideoStart(std::string d);

    void setVideoStop(std::string d);

    DownloadRequest();

    virtual ~DownloadRequest();

    void setYtVideo(YoutubeVideo *ytVideo);

    DownloadRequest(YoutubeVideo *ytVideo, const std::string &location);

    YtDlmCommand getCommand();

    std::string toString() {
        std::ostringstream os;
        os << "ytVideo: " << ytVideo << " location: " << location << " timeStampStart: "
           << timeStampStart << " timeStampStop: " << timeStampStop;
        os.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const DownloadRequest &request);

    void setBlocks(const std::vector<std::string> &blocks);

    void setRes(int i);


    void executeWithFeeback(void (*param)(std::string));
};


#endif //YTDLPWRAPPER_DOWNLOADREQUEST_H
