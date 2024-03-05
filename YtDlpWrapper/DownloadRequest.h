//
// Created by fboro on 05/03/2024.
//

#ifndef YTDLPWRAPPER_DOWNLOADREQUEST_H
#define YTDLPWRAPPER_DOWNLOADREQUEST_H

#include "YoutubeVideo.h"
#include "Logger.h"
#include "YtDlmCommandBuilder.h"
#include "YtDlmCommand.h"
class DownloadRequest {
private:
    YoutubeVideo ytVideo;
    std::string location;
public:
    const YoutubeVideo &getYtVideo() const;

    void setYtVideo(const YoutubeVideo &ytVideo);

    const std::string &getLocation() const;

    void setLocation(const std::string &location);

    DownloadRequest(const YoutubeVideo &ytVideo, const std::string &location);

    void addLocation(const std::string &basicString);

    void execute()
    {
        YtDlmCommand ytDlmCommand= (new YtDlmCommandBuilder())->addLocation(this->getLocation())->addFormat("mp4")->addLink(getYtVideo().getUrl())->build();
        Logger::info("executing Download Request: "+ytDlmCommand.getCommand());
        ytDlmCommand.execute();

    }
};


#endif //YTDLPWRAPPER_DOWNLOADREQUEST_H
