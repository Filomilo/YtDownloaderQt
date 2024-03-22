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
#include "Logger.h"
#include<windows.h>
#include "ExecutionResult.h"
#include "nlohmann/json.hpp"
class Executor {
private:
    static const std::string tmpDir;
    static const std::string programTmpPath;
    static std::string getFilePath(std::string name)
    {
         std::wstring wideProgramTmpPath(programTmpPath.begin(), programTmpPath.end());
        CreateDirectoryW (wideProgramTmpPath.c_str(),NULL);
        return programTmpPath+name;
    }


public:
    static std::ifstream  execute(std::string command)
    {
        command+=" > "+getFilePath("result.dat")+"\n";
        // std::cout<<"command: "+ command;
        Logger::info("Executing: "+ command);
        int rc=system(command.c_str());
//        FILE * file=fopen("result.dat","r");
        std::ifstream infile(getFilePath("result.dat"));
        std::string buffer;

        std::string line;
        while (std::getline(infile,line))
        {
            buffer+=line+"\n";
        }

//        system("rm result.dat");
        return infile;

////        int rc=fclose(file);
////        if (rc<0)
////            throw std::runtime_error("Couldnt close result.dat");
//        int res= std::remove(getFilePath("result.dat").c_str());
////
//        if (res<0)
//            throw std::runtime_error("Couldnt remove result.dat");
//        return ExecutionResult(rc,buffer,"");
    }
    static nlohmann::json executeWithJson(std::string command)
    {
        command+=" > "+getFilePath("result.dat")+"\n";
        // std::cout<<"command: "+ command;
        Logger::info("Executing for json: "+ command);
        int rc=system(command.c_str());
        std::ifstream infile(getFilePath("result.dat"));
        nlohmann::json data= nlohmann::json::parse(infile);
        infile.close();
        Logger::info("json dump: "+data.dump());


        return data;
    }

    static void clearResut()
    {
        int res= std::remove(getFilePath("result.dat").c_str());
//
        if (res<0)
            throw std::runtime_error("Couldnt remove result.dat");
    }

    static void executeWithFeedBack(std::string basicString, void (*pFunction)(std::string))
    {
        Logger::info("Executor with feedback");
        std::array<char, 1024*1024> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(basicString.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            result = buffer.data();
            pFunction(result);
        }
        return;
    }
};


#endif //YTDLPWRAPPER_EXECUTOR_H
