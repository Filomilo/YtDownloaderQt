//
// Created by fboro on 02/03/2024.
//

#ifndef YTDLPWRAPPER_LOGGER_H
#define YTDLPWRAPPER_LOGGER_H
#include <string>
#include <iostream>

class Logger {

public:
    static void info(std::string info)
    {
        std::cout<<"Log info: "<<info<<std::endl;
    }


    static void error(std::basic_string<char, std::char_traits<char>, std::allocator<char>> basicString) {
        std::cerr<<"Log Error: "<<info<<std::endl;
    }
};


#endif //YTDLPWRAPPER_LOGGER_H
