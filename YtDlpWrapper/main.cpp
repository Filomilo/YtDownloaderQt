#include <iostream>
#include "ExecutionResult.h"
//#include "Executor.h"
//#include "YtDlmCommand.h"
//#include "YtDlmCommandBuilder.h"
//#include <vector>
#include "YoutubeVideo.h"
//#include "JsonParser.h"
#include "DownloadRequest.h"
#include "YoutubeDownloader.h"
#include "DonwloadRequestBuilder.h"
#include "Logger.h"

void outputFeedBack(int a , int b)
{
//    Logger::info("lINE: \n"+"\n\n");
}

void listVideosSignle()
{
    YoutubeDownloader* ytDownloader=YoutubeDownloader::getInstance();
    ytDownloader->loadFilesWithCallBack("https://www.youtube.com/watch?v=f1A7SdVTlok",[](int a, int b){Logger::info("Test");});
    Logger::info("Loaded videos data: ");
    int i=0;
    std::vector<std::string> blocks;
    blocks.push_back("sponsor");
    blocks.push_back("selfpromo");
    for (YoutubeVideo yt: ytDownloader->getVideos()) {
        std::cout<<"video["<<i++<<"]= "<<yt<<std::endl;
        DownloadRequest downloadRequest(&yt,"D:\\temp\\donwald");
//        downloadRequest.setVideoStart("10:00");
//        downloadRequest.setVideoStop("12:00");
//        downloadRequest.setRes(480);
        downloadRequest.setBlocks(blocks);
Logger::info("attepting to create request");
//try {

    Logger::info("builded rquest");
    downloadRequest.executeWithFeeback(outputFeedBack);
//}
//catch (std::exception ex)
//{
//    std::cout<<"ex: "<<ex.what()<<std::endl;
//}



    }
//    std::cout<<"tmp: "<<std::getenv("TMP");
}

void listVideosPlaylist()
{
    YoutubeDownloader* ytDownloader=YoutubeDownloader::getInstance();
    ytDownloader->loadFiles("https://www.youtube.com/playlist?list=PL7VmhWGNRxKjkg6647cFu_KymlouyikR4");
    Logger::info("Loaded videos data: ");
    int i=0;
    for (YoutubeVideo yt: ytDownloader->getVideos()) {
        std::cout<<"video["<<i++<<"]= "<<yt<<std::endl;
    }
//    std::cout<<"tmp: "<<std::getenv("TMP");
}
void donwloadVideo()
{
    YoutubeDownloader* ytDownloader=YoutubeDownloader::getInstance();
    ytDownloader->loadFiles("https://youtu.be/VGvj6bj4Sog?si=mtuLA1EfCmVfQSyA");
    Logger::info("Loaded videos data: ");
    int i=0;
    for (YoutubeVideo yt: ytDownloader->getVideos()) {
        std::cout<<"video["<<i++<<"]= "<<yt<<std::endl;
        DownloadRequest* request=new DownloadRequest();
        request->setYtVideo(&yt);
        request->setVideoStart("01:00");
        request->setVideoStop("02:00");
        request->setLocation("D:\\temp\\New folder (4)");
        request->setIsAudio(false);
//        request->setFormat("flac");
//        request->setRes(480);

        request->execute();
    }
//    std::cout<<"tmp: "<<std::getenv("TMP");
}

int main(){
    // std::cout<<"test\n";

    // listVideosSignle();
//   listVideosPlaylist();
    donwloadVideo();
    return 0;
}