//
// Created by fboro on 10/03/2024.
//

#ifndef YTDLPWRAPPER_DONWLOADREQUESTBUILDER_H
#define YTDLPWRAPPER_DONWLOADREQUESTBUILDER_H
#include "DownloadRequest.h"
#include "Logger.h"
class DonwloadRequestBuilder {

private:
    DownloadRequest* downloadRequest;
public:
    DonwloadRequestBuilder() {
        downloadRequest=new DownloadRequest;
    }

    DonwloadRequestBuilder* setDownloaVideo(YoutubeVideo* vid)
    {
        Logger::info("setDownloaVideo: "+ vid->toString());
        downloadRequest->setYtVideo(vid);
    }

    DonwloadRequestBuilder* setVideoSectionStart(std::string timestamp){
        Logger::info("setDownloaVideo: "+timestamp);
        downloadRequest->setVideoStart(timestamp);
    }
    DonwloadRequestBuilder* setVideoSectionStop(std::string timestamp){
        Logger::info("setDownloaVideo: "+timestamp);
        downloadRequest->setVideoStop(timestamp);
    }

    DonwloadRequestBuilder* setDownloadLocation(std::string dir)
    {
        Logger::info("setDownloadLocation: "+ dir);
        downloadRequest->setLocation(dir);
    }


            DownloadRequest* build(){
                Logger::info("build: "+downloadRequest->toString());

                return downloadRequest;
    }




};


#endif //YTDLPWRAPPER_DONWLOADREQUESTBUILDER_H
