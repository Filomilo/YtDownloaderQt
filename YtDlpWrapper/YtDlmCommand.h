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
        this->command+=command+" ";
    }

    std::string getCommand()
    {
        return this->command;
    }

    std::ifstream execute()
    {
        return Executor::execute(this->getCommand());
    }


    void executeWithFeedback(void (*pFunction)(std::string)) {
        Executor::executeWithFeedBack(this->getCommand(),pFunction);
    }
};


#endif //YTDLPWRAPPER_YTDLMCOMMAND_H
