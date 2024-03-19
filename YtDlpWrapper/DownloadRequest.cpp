//
// Created by fboro on 05/03/2024.
//

#include "DownloadRequest.h"
#include "sstream"
const YoutubeVideo* DownloadRequest::getYtVideo() const {
    return ytVideo;
}


const std::string &DownloadRequest::getLocation() const {
    return location;
}



void DownloadRequest::setVideoStart(std::string st) {
    this->timeStampStart=st;
}

void DownloadRequest::setVideoStop(std::string d) {
    this->timeStampStop=d;
}



DownloadRequest::DownloadRequest() {}

DownloadRequest::~DownloadRequest() {
}

void DownloadRequest::setYtVideo(YoutubeVideo *ytVideo) {
    DownloadRequest::ytVideo = ytVideo;
}



std::ostream &operator<<(std::ostream &os, const DownloadRequest &request) {
    os << "ytVideo: " << request.ytVideo << " location: " << request.location << " timeStampStart: "
       << request.timeStampStart << " timeStampStop: " << request.timeStampStop;
    return os;
}

DownloadRequest::DownloadRequest(YoutubeVideo *ytVideo, const std::string &location) : ytVideo(ytVideo),
                                                                                       location(location) {}

void DownloadRequest::setBlocks(const std::vector<std::string> &blocks) {
    DownloadRequest::blocks = blocks;
}

void DownloadRequest::setRes(int res) {
    this->res = res;
}

YtDlmCommand DownloadRequest::getCommand()
{
    YtDlmCommandBuilder* ytDlmCommandBuilder= (new YtDlmCommandBuilder())
            ->addLocation(this->getLocation())
            ->addFormat("mp4")
            ->addLink(getYtVideo()
                              ->getUrl())
            ->addSection(timeStampStart,timeStampStop)
            ->setSponsrBlock(blocks);
    if(res>0)
    {
        ytDlmCommandBuilder->setRes(res);
    }

    YtDlmCommand ytDlmCommand=ytDlmCommandBuilder->build();
    return ytDlmCommand;
}

void DownloadRequest::execute()
{
    YtDlmCommand ytDlmCommand=this->getCommand();
    Logger::info("executing Download Request: "+ytDlmCommand.getCommand());
    ytDlmCommand.execute();

}

void DownloadRequest::executeWithFeeback(void (*param)(std::string)) {


    YtDlmCommand ytDlmCommand=this->getCommand();
    Logger::info("executing Download Request: "+ytDlmCommand.getCommand());
    ytDlmCommand.executeWithFeedback(param);
}



