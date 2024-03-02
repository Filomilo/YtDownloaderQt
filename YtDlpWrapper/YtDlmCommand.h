//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YTDLMCOMMAND_H
#define YTDLPWRAPPER_YTDLMCOMMAND_H
#include <string>
#include "Executor.h"
#include "ExecutionResult.h"
class YtDlmCommand {
private:
    std::string command;


public:
    YtDlmCommand()
    {
        command="yt-dlp ";
    }

    void addToCommand(std::string command)
    {
        this->command+=command+" ";
    }

    std::string getCommand()
    {
        return this->command;
    }

    ExecutionResult execute()
    {
        return Executor::execute(this->getCommand());
    }



};


#endif //YTDLPWRAPPER_YTDLMCOMMAND_H
