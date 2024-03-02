//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_EXECUTOR_H
#define YTDLPWRAPPER_EXECUTOR_H

#include <string>
#include <array>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include "ExecutionResult.h"
class Executor {

public:
    static ExecutionResult  execute(std::string command)
    {
        command+=" > result.dat\n";
        std::cout<<"command: "+ command;
        int rc=system(command.c_str());
//        FILE * file=fopen("result.dat","r");
        std::ifstream infile("result.dat");
        std::string buffer;

        std::string line;
        while (infile >> line)
        {
            buffer+=line;
        }

//        system("rm result.dat");
        infile.close();

//        int rc=fclose(file);
//        if (rc<0)
//            throw std::runtime_error("Couldnt close result.dat");
        int res= std::remove("result.dat");
//
        if (res<0)
            throw std::runtime_error("Couldnt remove result.dat");
        return ExecutionResult(rc,buffer,"");
    }




};


#endif //YTDLPWRAPPER_EXECUTOR_H
