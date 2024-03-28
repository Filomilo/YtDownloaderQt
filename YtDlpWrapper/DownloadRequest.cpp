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
            ->addFormat(this->format)
            ->addLink(getYtVideo()
            ->getUrl())
            ->addSection(timeStampStart,timeStampStop);
            if(this->blocks.size()>0)
            ytDlmCommandBuilder->setSponsrBlock(blocks);
    if(res>0)
    {
                ytDlmCommandBuilder->addRes(res);
    }

    YtDlmCommand ytDlmCommand=ytDlmCommandBuilder->build();
    return ytDlmCommand;
}

void DownloadRequest::execute()
{
    YtDlmCommand ytDlmCommand=this->getCommand();
    Logger::info("executing Download Request: "+ytDlmCommand.getCommand());
    ytDlmCommand.execute(this->getYtVideo()->getName());

}

void DownloadRequest::executeWithFeeback(void (*param)(int,int)) {


    YtDlmCommand ytDlmCommand=this->getCommand();
    Logger::info("executing Download Request: "+ytDlmCommand.getCommand());
    ytDlmCommand.executeWithFeedback(this->getYtVideo()->getName(),param);
}

std::ostream &operator<<(std::ostream &os, const DownloadRequest &request) {
    os << "ytVideo: " << *request.ytVideo << " location: " << request.location << " timeStampStart: "
       << request.timeStampStart << " timeStampStop: " << request.timeStampStop << " blocks: " << request.blocks.size()
       << " res: " << request.res;
    return os;
}



