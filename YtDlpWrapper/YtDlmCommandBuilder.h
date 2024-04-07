//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
#define YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
#include "YtDlmCommand.h"

class YtDlmCommandBuilder {
private:
    YtDlmCommand ytDlmCommand;
    bool isAudio=false;
public:
YtDlmCommandBuilder()
{}

YtDlmCommand build()
{
    return this->ytDlmCommand;
}

    YtDlmCommandBuilder* listPlaylistVideo(std::string playlistLink)
{
    this->ytDlmCommand.addToCommand("--flat-playlist -j --no-warnings  \""+playlistLink+"\"");
    return this;
}
    YtDlmCommandBuilder* addLocation(std::string location)
    {
        Logger::info("additnig lcoaiotn: ");
        this->ytDlmCommand.addToCommand(" -o \""+location+"\"");
        return this;
    }

            YtDlmCommandBuilder* addFormat(std::string format)
    {
    if(this->isAudio)
        this->ytDlmCommand.addToCommand(" --audio-format "+format+" --extract-audio ");
    else
        this->ytDlmCommand.addToCommand(" -f "+format);
    return this;
    }
    YtDlmCommandBuilder* addLink(std::string link)
    {
        this->ytDlmCommand.addToCommand(" \""+link+"\"");
        return this;
    }
    YtDlmCommandBuilder* setSponsrBlock(std::vector<std::string> blocks)
    {
        Logger::info("set sponsor lbokcs: "+std::to_string(blocks.size()));
    std::string toAdd="--sponsorblock-remove ";
    for(int i=0;i<blocks.size();i++)
    {
        toAdd+=blocks.at(i);
        if(i<blocks.size()-1)
            toAdd+=",";
    }
        this->ytDlmCommand.addToCommand(toAdd);
        return this;
    }


    YtDlmCommandBuilder* addSection(std::string start, std::string end) {
        this->ytDlmCommand.addToCommand("--download-sections \"*"+start+"-"+end+"\"");
        return this;
    }

    void addRes(int res) {
        this->ytDlmCommand.addToCommand("-S res:"+ std::to_string(res));
    }

    YtDlmCommandBuilder* setIsAudio(bool b) {
        isAudio=b;

        return this;
    }
};


#endif //YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
