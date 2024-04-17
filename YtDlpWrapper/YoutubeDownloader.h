//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
#define YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
#include <vector>
#include "YoutubeVideo.h"
#include <future>
#include "Logger.h"
#include "YtDlmCommand.h"
#include "YtDlmCommandBuilder.h"
#include "Executor.h"
#include "ExecutionResult.h"
#include "JsonParser.h"
#include <sstream>
class YoutubeDownloader {
private:
    std::vector<YoutubeVideo> videosList;
    static YoutubeDownloader* instance;
    YoutubeDownloader(){
        srand(time(0));
    }

   void loadSingleVideo(std::string link,std::function<void(int,int)> callback, int numb)
    {

        Logger::info("Loading single video from data from data: " + link);

        YtDlmCommand ytDlmCommand=(new YtDlmCommandBuilder)->listPlaylistVideo(link)->build();
        nlohmann::json data=Executor::executeWithJson(ytDlmCommand.getCommand(),std::to_string(numb));
 Logger::info("data  " );
        std::vector<YoutubeVideo> tmp;
        YoutubeVideo video=JsonParser::parseJsonVideo(data);
         Logger::info("video:   "+video.getName() );
        video.setUrl(link);
        this->videosList.push_back(video);

        Logger::info("finshed loading single file");
        // callback(video);
    }

    std::string getUrlFromPlaylsitEntry(std::string line)
    {
        std::string toFind="url\": \"";
        std::cout<<"to get link: "<<line<<std::endl;
        int start=line.find(toFind);
        std::cout<<"\nstart: "<<start<<std::endl;
        if(start<0)
            return "";
        line=line.substr(start+toFind.size());
       std::cout<<"\nfrom sart: "<<line<<std::endl;
        int end=line.find("\"");
       std::cout<<"\nend: "<<end<<std::endl;
       line= line.substr(0,end);
        std::cout<<"\nfrom end: "<<line<<std::endl;
        return line;
    }


    void loadPlaylist(std::string link,std::function<void(int,int)> callback)
    {
        Logger::info("Loading playlsit data from data: " + link);
        YtDlmCommand ytDlmCommand=(new YtDlmCommandBuilder)->listPlaylistVideo(link)->build();
        std::ifstream ss=Executor::execute(ytDlmCommand.getCommand(),std::to_string(rand()*10000));
       // Logger::info("Json data: "+ss..length());
       // std::istringstream ss(data.out);
        Logger::info("\n\n\n\n\n\nline by line: ");
        std::vector<std::string> urls;
        while(!ss.eof())
        {
              Logger::info("start line");
            std::string line;
            std::getline(ss,line);
            Logger::info("curr line: "+ line);

            std::string url=this->getUrlFromPlaylsitEntry(line);
            if(url.length()==0)
                break;
            std::cout<<"url: "<<url<<std::endl<<std::endl<<std::endl;
            urls.push_back(url);
          //  this->loadSingleVideo(url,callback);
        }
        Logger::info("stop line by line : "+  std::to_string(urls.size()) );
        std::vector<YoutubeVideo> tmp;
            Logger::info("test 1" );
        ss.close();
        // Executor::clearResut();
               Logger::info("test 2" );
       callback(0,urls.size()+1);
           Logger::info("start iteraiont" );
        for (int var = 0; var < urls.size(); ++var) {
            Logger::info("loading vidoe: + "+urls[var]);
             this->loadSingleVideo(urls[var],callback,var);
            callback(var,urls.size()+1);
        }
        Executor::clearResut();

      // this->videosList=tmp;
    }

 void addVideo(std::string link)
    {

    }


public:
    static YoutubeDownloader* getInstance(){
        if( instance== nullptr)
        {
            YoutubeDownloader::instance=new YoutubeDownloader();
        }
        return  YoutubeDownloader::instance;
    }

    bool loadFiles(std::string link)
    {
        srand(time(0));
        this->videosList.clear();
        try {
            Logger::info("Loaing files form link: " + link);
            std::vector<YoutubeVideo> list;

            if (link.find("list") != std::string::npos) {
                loadPlaylist(link,nullptr);
            }
            else {
                loadSingleVideo(link,nullptr,rand());
            }
            Logger::info("size; "+ list.size());
//            Logger::info("Execution Result " + executionResult.out);
        }
        catch (std::exception ex)
        {
            Logger::error("errror while loading files from link: "+std::string(ex.what()));
            return false;
        }
        Executor::clearResut();

        return true;
    }

    bool loadFilesWithCallBack(std::string link,const std::function<void(int, int)> callback)
    {
          srand(time(0));
        this->videosList.clear();
        try {
            Logger::info("Loaing files form link: " + link);
            std::vector<YoutubeVideo> list;

            if (link.find("list") != std::string::npos) {
                loadPlaylist(link,callback);
            }
            else {
                loadSingleVideo(link,callback,rand());
            }
            Logger::info("size; "+ list.size());
            // callback(this->getVideos().at(0)s);
//            Logger::info("Execution Result " + executionResult.out);
        }
        catch (std::exception ex)
        {
            Logger::error("errror while loading files from link: "+std::string(ex.what()));
            return false;
        }

        return true;
    }



    std::vector<YoutubeVideo> getVideos();
};






#endif //YTDLPWRAPPER_YOUTUBEDOWNLOADER_H
