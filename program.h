#ifndef PROGRAM_
#define PROGRAM_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct Command{
        int num_cmd=0;  //номер команды
        char cmd;       //тип команды X,V,R,L,?,!
        int j1=-1;      //переход
        int j2=-1;      //переход j2 для '?'
    }; 

class Program{
private:
    std::vector<Command> program;
public:
    Program()=default;

    Program(const char* file): program({}){
        read_programFile(file);
    }

    void read_programFile(const char* programmFileName){
        std::ifstream progFile(programmFileName);
        if(!progFile.is_open()){
            throw std::invalid_argument("progFile open error");
        }

        program.clear();

        std::string line;

        while (std::getline(progFile,line)){
            //убираем комментарий
            size_t pos = line.find('%');
            if(pos!=std::string::npos){
                line=line.substr(0,pos);
            }

            for(auto& ch:line){
                if(ch=='.'){
                    ch=' ';
                }
            }

            if(line.empty()){
                continue;
            }

            Command cmd;
            std::stringstream ss(line); 

            ss>>cmd.num_cmd>>cmd.cmd;

            if(ss.fail()){
                continue;
            }

            if(cmd.cmd=='?' || cmd.cmd=='V' || cmd.cmd=='X' || cmd.cmd=='R' || cmd.cmd=='L'){
                ss>>cmd.j1;
                if(cmd.cmd=='?'){
                    ss>>cmd.j2;
                }
            }

            program.push_back(cmd);
        }

        if(program.empty()){
            throw std::runtime_error("Error empty program");
        }

        progFile.close();
    }

    const std::vector<Command>& get_program() const {
        return program;
    }

    void clear_program(){
        program.clear();
    }

    ~Program(){
        clear_program();
    }
};

#endif