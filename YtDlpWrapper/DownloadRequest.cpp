//
// Created by fboro on 05/03/2024.
//

#include "DownloadRequest.h"
#include "sstream"
const YoutubeVideo* DownloadRequest::getYtVideo() const {
    return ytVideo;
}


std::string &DownloadRequest::getLocation()  {
    return this->location;
}

std::string DownloadRequest::getSaveLocation()
{
    Logger::info("this->getIsAudio(");
    std::string fromat=this->getIsAudio()?"mp3":"mp4";
    Logger::info("getLocation()++ytVideo->getName()++fromat;");

     std::string saveLocation=getLocation()+"\\"+ytVideo->getName()+"."+fromat;
//   std::string saveLocation=getLocation()+"/%(title)s_%(id)s.%(ext)s";
      Logger::info("  return  saveLocation;");
      if(this->IsOverwriteName)
          saveLocation=getLocation()+"."+fromat;
    return  saveLocation;
}

void DownloadRequest::setVideoStart(std::string st) {
    Logger::info("setting setVideoStart: "+ st);

    this->timeStampStart=st;
}

void DownloadRequest::setVideoStop(std::string d) {
        Logger::info("setting setVideoStop: "+ d);
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
    Logger::info("set blocks : "+std::to_string(blocks.size()));
    DownloadRequest::blocks = blocks;
}

void DownloadRequest::setRes(int res) {

    Logger::info("setting rsolution: "+ std::to_string(res));
    this->res = res;
}

YtDlmCommand DownloadRequest::getCommand()
{

    std::string locatioNSave=this->getSaveLocation();
        Logger::info("maxString: "+std::to_string(locatioNSave.max_size()) );
    Logger::info("ytDlmCommandBuilder");
        YtDlmCommandBuilder* ytDlmCommandBuilder= (new YtDlmCommandBuilder());
    ytDlmCommandBuilder->addLocation(locatioNSave);
        ytDlmCommandBuilder->setIsAudio(this->getIsAudio());
    ytDlmCommandBuilder->addFormat(this->getIsAudio()?"mp3":"mp4");
        Logger::info("link: ");
    Logger::info("getl ink: url: "+ this->getYtVideo()->getUrl());
        ytDlmCommandBuilder ->addLink(this->getYtVideo()->getUrl());
           ytDlmCommandBuilder ->addSection(timeStampStart,timeStampStop);
            if(this->blocks.size()>0)
            ytDlmCommandBuilder->setSponsrBlock(blocks);
    if(res>0)
    {
                ytDlmCommandBuilder->addRes(res);
    }

    YtDlmCommand ytDlmCommand=ytDlmCommandBuilder->build();
    delete ytDlmCommandBuilder;
    return ytDlmCommand;
}

void DownloadRequest::execute()
{
        Logger::info("this->getCommand(); ");
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
    os << "ytVideo: " << request.ytVideo << " location: " << request.location << " timeStampStart: "
       << request.timeStampStart << " timeStampStop: " << request.timeStampStop << " format: " << request.format
       << " blocks: " << request.blocks.size() << " res: " << request.res;
    return os;
}

void DownloadRequest::setIsAudio(bool b) {
this->isAudio=b;
}

bool  DownloadRequest::getIsAudio() const {
    return this->isAudio;
}


void DownloadRequest::setOverwriteName(bool state)
{
    this->IsOverwriteName=state;
}



