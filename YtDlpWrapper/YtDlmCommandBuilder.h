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
        this->ytDlmCommand.addToCommand(" -o \""+location+"/%(title)s.%(ext)s\"");
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

};


#endif //YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
