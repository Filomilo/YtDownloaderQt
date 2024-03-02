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

    static YoutubeVideo parseJsonVideo(std::string json)
    {
//        std::cout<<"------------------------------\n\n";
//        std::cout<<json<<std::endl<<std::endl;
std::string copy=json;
        std::string title=JsonParser::getStringAttribute("title",copy);
std::string url=JsonParser::getStringAttribute("url",json);
//        std::cout<<"url: "<<std::endl<<std::endl;

//        std::string thumbnail=JsonParser::getStringAttribute("url",json);
//        std::string duration=JsonParser::getStringAttribute("duration_string",json);
        YoutubeVideo ytV;
//        ytV.setUrl(url);
//        ytV.setName(title);
//        ytV.setThumbnail(thumbnail);
//        ytV.setDuration(duration);
        return ytV;
    }
};


#endif //YTDLPWRAPPER_JSONPARSER_H
