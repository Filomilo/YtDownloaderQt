//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_JSONPARSER_H
#define YTDLPWRAPPER_JSONPARSER_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "YoutubeVideo.h"
#include "nlohmann/json.hpp"
class JsonParser {
public:
private:
    static std::string getStringAttribute(std::string attribute, std::string& Json)
    {

        std::string toFind="\""+attribute+"\": \"";
        std::cout<<"to find: "<<toFind<<"\n\n";
        int start= Json.find(toFind);
        if(start<0)
        {
             toFind="\""+attribute+"\":\"";
            start= Json.find(toFind);
        }

        std::cout<<"start: "<<start<<"\n\n";
        std::cout<<"aprt json: "<<Json<<"\n\n";
        Json=Json.substr(start+toFind.size());
        std::cout<<"aprt json: "<<Json<<"\n\n";
        start= Json.find_first_of('"');
        std::cout<<"start: "<<start<<"\n\n";
        std::string out= Json.substr(0,start);
        std::cout<<"out: "<<out<<"\n\n";
        return out;
    }
public:

    static std::vector<YoutubeVideo> parseJsonPlaylist(std::string json)
    {
        std::vector<YoutubeVideo> list;
        std::istringstream is=std::istringstream (json);
        while(!is.eof())
        {
            std::string line;
            std::getline(is,line);
//            std::cout<<"\n\n\ntest: "<<line<<"\n\n";
            if(line.size()>0) {
                YoutubeVideo ytV = parseJsonVideo(line);
                list.push_back(ytV);
            }
        }

        for (YoutubeVideo ytV: list) {
//            std::cout<<"list leemtn: "<<ytV<<std::endl;
        }
        return list;

    }

    static YoutubeVideo parseJsonVideo(nlohmann::json jsonData)
    {
    try {
        Logger::info("Parsing json: " + to_string(jsonData));
        YoutubeVideo ytV;

        Logger::info("parsed json: " + jsonData.size());
        Logger::info("auto subs");
        Logger::info("Auto subs: "+  std::to_string(jsonData["automatic_captions"].size()));
        for (auto it=jsonData["automatic_captions"].begin() ;it!=jsonData["automatic_captions"].end();it++ ) {
//            std::cout<<"key: "<<it.key()<<std::endl;
            ytV.addAutoSubtitle(it.key());
        }
        for (auto it=jsonData["subtitles"].begin() ;it!=jsonData["subtitles"].end();it++ ) {
//            std::cout<<"key: "<<it.key()<<std::endl;
            ytV.addSubtitle(it.key());
        }

      ytV.setName(jsonData["title"]);
      ytV.setThumbnail(jsonData["thumbnail"]);
      ytV.setDuration(jsonData["duration_string"]);
        return ytV;
    }
    catch (std::exception ex)
    {
        std::string err="Couldnt parse json: ";
        err+=ex.what();
        Logger::error(err);
        throw new std::runtime_error(err);
    }

    }
};


#endif //YTDLPWRAPPER_JSONPARSER_H
