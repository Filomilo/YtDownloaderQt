//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
#define YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
#include "YtDlmCommand.h"

class YtDlmCommandBuilder {
private:
    YtDlmCommand ytDlmCommand;
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
        this->ytDlmCommand.addToCommand(" -o \""+location+"/%(title)s_%(id)s.%(ext)s\"");
        return this;
    }

            YtDlmCommandBuilder* addFormat(std::string format)
    {
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

    void setRes(int res) {
        this->ytDlmCommand.addToCommand("-S res:"+ std::to_string(res));
    }
};


#endif //YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
