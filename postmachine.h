#ifndef POST_MACHINE_
#define POST_MACHINE_

#include <string>
#include <vector>
#include "program.h"


class postmachine{
private:
    int size_ribbon;                      //размер ленты
    std::string ribbon;                   //лента
    int number_command;                   //текущая команда 
    int index;                            //позиция головки
    int current_tact;                     //текущий такт
    std::vector<Command> program;         //программа машины
public:
    //конструктор для создания машины
    postmachine(int sizeRibbon,  const std::vector<Command>& Prog): size_ribbon(sizeRibbon),program(Prog),
    ribbon(size_ribbon,'0'), current_tact(0),index(0){
        number_command=20000000;
        for(int i=0;i<program.size();++i){
            number_command=std::min(number_command,program[i].num_cmd);
        }
    }
    
    std::string get_result()const {
        int last=-1;
        if(index==size_ribbon-1){
            for(int i=size_ribbon-2;i>=0;--i){
                if(ribbon[i]=='1'){
                    last=i;
                    break;
                }
            }
        }else if(index==0){
            for(int i=size_ribbon-1;i>=0;--i){
                if(ribbon[i]=='1'){
                    last=i;
                    break;
                }
            }
        }else{
            for(int i=index-1;i>=0;--i){
                if(ribbon[i]=='1'){
                    last=i;
                    break;
                }
            }
            if(last==-1){
                for(int i=size_ribbon-1;i>=index;--i){
                    if(ribbon[i]=='1'){
                        last=i;
                        break;
                    }
                }
            }
        }

        if(last==-1){
            return std::string(1,ribbon[index]);
        }

        std::string result;
        if(index>last){
            result = (ribbon.substr(index)+ribbon.substr(0,last+1));
        }else{
            result = ribbon.substr(index,last-index+1);
        }

        return result;
    }

    std::string calc(std::string const& init,int maxsteps){
        if(init.size()>size_ribbon){
            throw std::invalid_argument("Error size ribbon");
        }

        ribbon=init; 
        int count_steps=0;              

        while(count_steps<maxsteps){
            const Command* cmd=nullptr;
            bool found = false;

            for(const auto& c: program){
                if(c.num_cmd==number_command){
                    cmd=&c;
                    found = true;
                    break;
                }
            }

            if(!found){
                throw std::runtime_error("Error");
            }

            if(cmd==nullptr){
                throw std::runtime_error("Unknown command number");
            }

            switch (cmd->cmd){
            case 'V': ribbon[index]='1';
                      number_command=cmd->j1;
                      break;
            case 'X': ribbon[index]='0';
                      number_command=cmd->j1;
                      break;
            case 'L': if(index==0){
                        index=size_ribbon-1;
                      }else{
                        --index;
                      };
                      number_command=cmd->j1;
                      break;
            case 'R': if(index==size_ribbon-1){
                        index=0;
                      }else{
                        ++index;
                      };
                      number_command=cmd->j1;
                      break;
            case '?': if(ribbon[index]=='0'){
                        number_command=cmd->j1;
                      }else{
                        number_command=cmd->j2;
                      };
                      break;
            case '!':
                      return get_result();
            default:throw std::runtime_error("Unknown command");
            }

            ++count_steps;
        }
        
        return "Not applicable";
    }
};


#endif