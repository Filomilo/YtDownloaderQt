//
// Created by fboro on 02/03/2024.
//

#ifndef YTDLPWRAPPER_LOGGER_H
#define YTDLPWRAPPER_LOGGER_H
#include <string>
#include <iostream>
#include "fstream"
class Logger {


private:
    static const std::string fileLog;

public:
    static void info(std::string info)
    {
        std::cout<<"\n\nLog info: "<<info<<std::endl;
        // std::ofstream f;
        // f.open(fileLog,std::ios_base::app);
        // f<<"\n\nLog info: "<<info<<std::endl;
        // f.close();
    }


    static void error(std::string info) {
        std::cerr<<"Log Error: "<<info<<std::endl;
    }
};


#endif //YTDLPWRAPPER_LOGGER_H
