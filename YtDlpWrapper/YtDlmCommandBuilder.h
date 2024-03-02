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
    this->ytDlmCommand.addToCommand("--flat-playlist -j \""+playlistLink+"\" -o \"%(title)s\"");
    return this;
}



};


#endif //YTDLPWRAPPER_YTDLMCOMMANDBUILDER_H
