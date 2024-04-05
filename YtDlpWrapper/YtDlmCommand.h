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
        command="yt-dlp --newline  ";
    }

    void addToCommand(std::string command)
    {
        Logger::info("adding to comamnd: " + command);
        Logger::info("a this->command: " +  this->command);
        this->command+=command+" ";
    }

    std::string getCommand()
    {
        return this->command;
    }

    std::ifstream execute(std::string fileOFfset)
    {
        return Executor::execute(this->getCommand(),fileOFfset);
    }


    void executeWithFeedback(std::string fileOFfset,void (*pFunction)(int,int)) {
        Executor::executeWithFeedBack(this->getCommand(),fileOFfset,pFunction);
    }
};


#endif //YTDLPWRAPPER_YTDLMCOMMAND_H
