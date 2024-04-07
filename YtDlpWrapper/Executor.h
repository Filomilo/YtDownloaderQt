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
<<<<<<< HEAD
        return programTmpPath+name;
=======
         std::string path=programTmpPath+name;
  //       Logger::info("path: "+path);
  std::replace(path.begin(), path.end(), '\"', ' ');
  // Logger::info("path: "+path);
        return path;
>>>>>>> playlist-download
    }


    static std::ifstream openStreamToFile(std::string path)
    {
<<<<<<< HEAD
        command+=" > "+getFilePath("result.dat")+"\n";
        // std::cout<<"command: "+ command;
        Logger::info("Executing: "+ command);
        int rc=system(command.c_str());
//        FILE * file=fopen("result.dat","r");
        std::ifstream infile(getFilePath("result.dat"));
        std::string buffer;

=======
        std::ifstream infile;
>>>>>>> playlist-download
        std::string line;
        while(!infile.is_open()|| !infile.good() || infile.eof() || line.length()==0 )
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

        command+=" > \""+file+"\"\n";
        Logger::info("Executing: "+ command);


        Logger::info(" STARTUPINFO  si;");
        STARTUPINFO  si;
        Logger::info("   PROCESS_INFORMATION pi;");
        PROCESS_INFORMATION pi;
        Logger::info("      ZeroMemory(&si, sizeof(si));");
        ZeroMemory(&si, sizeof(si));
        Logger::info("    ZeroMemory(&si, sizeof(si));");
        si.cb= sizeof(si);
        Logger::info("    ZeroMemory(&pi,sizeof(pi));");
        ZeroMemory(&pi,sizeof(pi));
        Logger::info(   "     std::wstring wcommand = std::wstring(command.begin(), command.end());");
        std::wstring wcommand = std::wstring(command.begin(), command.end());
        Logger::info(   "          wchar_t* toExecute= const_cast<wchar_t *>(wcommand.c_str());");
        wchar_t* toExecute= const_cast<wchar_t *>(wcommand.c_str());
        Logger::info("Create precess");
        if (!CreateProcess(NULL, toExecute, NULL, NULL, FALSE, CREATE_NO_WINDOW , NULL, NULL, &si, &pi)) {
       Logger::error("CreateProcess failed");
            exit(1);
        }
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);







        int rc=WinExec(command.c_str(), SW_HIDE);


        std::ifstream infile=openStreamToFile(file);
        return infile;

    }
    static nlohmann::json executeWithJson(std::string command,std::string fileOffset)
    {
<<<<<<< HEAD
        command+=" > "+getFilePath("result.dat")+"\n";
=======
       
        std::string file=getFilePath("result_"+fileOffset+".dat");
           command="cmd /c "+command;
        command+=" > \""+file+"\"\n";
>>>>>>> playlist-download
        // std::cout<<"command: "+ command;
        Logger::info("Executing for json: "+ command);
        int rc= WinExec(command.c_str(), SW_HIDE); //system(command.c_str());
           Logger::info("opening stream");
        std::ifstream infile=openStreamToFile(file);


               Logger::info("parisng json");
        nlohmann::json data= nlohmann::json::parse(infile);
                   Logger::info("closing stream");
        infile.close();
//        Logger::info("json dump: "+data.dump());


        return data;
    }

    static void clearResut()
    {

            for (const auto& entry : std::filesystem::directory_iterator(getFilePath("")))
                std::filesystem::remove_all(entry.path());

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



static void executeWithFeedBack(std::string basicString,std::string fileOffset, void (*pFunction)(int,int))
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

        }
        return;
    }
};


#endif //YTDLPWRAPPER_EXECUTOR_H
