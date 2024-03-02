#include <iostream>
#include "ExecutionResult.h"
#include "Executor.h"
#include "YtDlmCommand.h"
#include "YtDlmCommandBuilder.h"
#include <vector>
#include "YoutubeVideo.h"
#include "JsonParser.h"
#include "YoutubeDownloader.h"
//void executorTest()
//{
//    ExecutionResult res= Executor::execute("dir");
//    std::cout<<"Result: "<<res<<std::endl;
//}
//void listPlaylisGetTEtst()
//{
//    YtDlmCommand commad= (new YtDlmCommandBuilder())
//            ->listPlaylistVideo("https://www.youtube.com/watch?v=FmYXsAp8Tu0&list=PLtST4K3U6x9ICNYQ3D3_pHpcIbPjpf_7Y&index=49")
//            ->build();
//
//    ExecutionResult res=commad.execute();
//    std::cout<<"result of commad:"<<commad.getCommand()<<" : "<<res<<"\n";
//
//}
//void getListOfYt()
//{
//    YtDlmCommand commad= (new YtDlmCommandBuilder())
//            ->listPlaylistVideo("https://www.youtube.com/watch?v=OLbWB1R095s")
//            ->build();
//
//    ExecutionResult res=commad.execute();
////    std::cout<<"result of commad:"<<commad.getCommand()<<" : "<<res<<"\n";
//
//    std::vector<YoutubeVideo> listYoutuebvideos=JsonParser::parseJsonPlaylist(res.out);
//}

void listVideosSignle()
{
    YoutubeDownloader* ytDownloader=YoutubeDownloader::getInstance();
//    ytDownloader->loadFiles("https://www.youtube.com/watch?v=OLbWB1R095s");
}

int main(){
    std::cout<<"test\n";
//    executorTest();
//    listPlaylisGetTEtst();
//    getListOfYt();
    listVideosSignle();
    return 0;
}