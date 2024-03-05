#include <iostream>
#include "ExecutionResult.h"
//#include "Executor.h"
//#include "YtDlmCommand.h"
//#include "YtDlmCommandBuilder.h"
//#include <vector>
//#include "YoutubeVideo.h"
//#include "JsonParser.h"
#include "DownloadRequest.h"
#include "YoutubeDownloader.h"
void listVideosSignle()
{
    YoutubeDownloader* ytDownloader=YoutubeDownloader::getInstance();
    ytDownloader->loadFiles("https://youtu.be/tWYsfOSY9vY?si=AE1dt_Y-4WzBzvcV");
    Logger::info("Loaded videos data: ");
    int i=0;
    for (YoutubeVideo yt: ytDownloader->getVideos()) {
        std::cout<<"video["<<i++<<"]= "<<yt<<std::endl;
        DownloadRequest downloadRequest(yt,"D:\\temp\\donwald");
        downloadRequest.execute();

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


int main(){
    std::cout<<"test\n";

    listVideosSignle();
//    listVideosPlaylist();
    return 0;
}