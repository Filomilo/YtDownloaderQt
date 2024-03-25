//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_EXECUTOR_H
#define YTDLPWRAPPER_EXECUTOR_H
#include <thread>
#include <chrono>
#include <string>
#include <array>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include "Logger.h"
#include<windows.h>
#include "ExecutionResult.h"
#include <stdio.h>
#include "nlohmann/json.hpp"
class Executor {
private:
    static const std::string tmpDir;
    static const std::string programTmpPath;
    static std::string getFilePath(std::string name)
    {
         std::wstring wideProgramTmpPath(programTmpPath.begin(), programTmpPath.end());
        CreateDirectoryW (wideProgramTmpPath.c_str(),NULL);
         std::string path=programTmpPath+name;
  //       Logger::info("path: "+path);
  // std::replace(path.begin(), path.end(), '\\', '/');
  // Logger::info("path: "+path);
        return path;
    }


    static std::ifstream openStreamToFile(std::string path)
    {
        std::ifstream infile;
        std::string line;
        while(!infile.is_open()|| !infile.good() || infile.eof() || line.length()==0 )
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            infile.close();
            infile.open(path);
            std::getline(infile, line);
            // Logger::error("line: "+ std::to_string(line.length()));
            // Logger::error("couldnt open stream for file "+ path);
        }

        infile.seekg(0);
        return infile;
    }

public:

    static std::ifstream  execute(std::string command,std::string fileOffset)
    {
          std::string file=getFilePath("result_"+fileOffset+".dat");
        command="cmd /c "+command;

        command+=" > "+file+"\n";
        // std::cout<<"command: "+ command;
        Logger::info("Executing: "+ command);
        int rc=WinExec(command.c_str(), SW_HIDE);
//        FILE * file=fopen("result.dat","r");

        // infile.getline()
        // Logger::info("infile open: "+ std::to_string(infile.is_open()));;        // std::string line;
        // while (std::getline(infile,line))
        // {
        //     // buffer+=line+"\n";
        //     Logger::info("line: " +buffer);
        // }

//        system("rm result.dat");

        std::ifstream infile=openStreamToFile(file);
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
    static nlohmann::json executeWithJson(std::string command,std::string fileOffset)
    {
        std::string file=getFilePath("result_"+fileOffset+".dat");
           command="cmd /c "+command;
        command+=" > "+file+"\n";
        // std::cout<<"command: "+ command;
        Logger::info("Executing for json: "+ command);
        int rc= WinExec(command.c_str(), SW_HIDE); //system(command.c_str());
           Logger::info("opening stream");
        std::ifstream infile=openStreamToFile(file);


               Logger::info("parisng json");
        nlohmann::json data= nlohmann::json::parse(infile);
                   Logger::info("closing stream");
        infile.close();
        Logger::info("json dump: "+data.dump());


        return data;
    }

    static void clearResut()
    {

            // for (const auto& entry : std::filesystem::directory_iterator(getFilePath("")))
            //     std::filesystem::remove_all(entry.path());

        // int res= std::remove(getFilePath("result.dat").c_str());
        // std::string command="cmd del "+ getFilePath("result.dat");
        // Logger::info("running : "+ command);
        // WinExec(command.c_str(), SW_HIDE);

        //     if (res<0){
        //       Logger::error("couldnt remove result dat: "+getFilePath("result.dat"));
        //     throw std::runtime_error("Couldnt remove result.dat");
        // }

        // std::string fileTOremove=getFilePath("result.dat");

        //       if(std::filesystem::exists(fileTOremove))
        // {
        //           std::cout << "file " << fileTOremove << " exist.\n";

        // }
        //       while(std::filesystem::exists(fileTOremove))
        // {
        //       std::cout << "removing " << fileTOremove << " \n";
        //     try {
        //         if (std::filesystem::remove(fileTOremove))
        //             std::cout << "file " << fileTOremove << " deleted.\n";
        //         else
        //             std::cout << "file " << fileTOremove << " not found.\n";
        //         std::this_thread::sleep_for(std::chrono::milliseconds(20000));
        //     }
        //     catch(const std::exception& e) {
        //         std::cout << "filesystem error: " << e.what() << '\n';
        //         break;
        //     }
        }



static void executeWithFeedBack(std::string basicString,std::string fileOffset, void (*pFunction)(std::string))
    {
       std::string file=getFilePath("result_"+fileOffset+".dat");
        std::string command="cmd.exe /c "+basicString;
        Logger::info("Executor with feedback");
        std::array<char, 1024*1024> buffer;
        std::string result;
        Logger::info("running: "+ command);
        std::unique_ptr<FILE, decltype(&_pclose)> pipe( _popen(command.c_str(), "r"), _pclose);
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
