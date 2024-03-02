//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_EXECUTIONRESULT_H
#define YTDLPWRAPPER_EXECUTIONRESULT_H

#include <string>
#include <ostream>

class ExecutionResult {
public:
    int code;
    std::string out="";
    std::string err="";

    ExecutionResult(int code, const std::string &out, const std::string &err) : code(code), out(out),
                                                                                                 err(err) {}

    explicit ExecutionResult(int code) : code(code) {}




    friend std::ostream &operator<<(std::ostream &os, const ExecutionResult &result){
        os << "code: " << result.code << " out: " << result.out << " err: " << result.err;
        return os;
    }
};


#endif //YTDLPWRAPPER_EXECUTIONRESULT_H
