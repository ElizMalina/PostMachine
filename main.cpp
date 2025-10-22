#include <fstream>
#include "postmachine.h"

std::string add_zero_ribbon(const std::string& Ribbon, int size_rib);

int main(int argc, char* argv[]){
  if(argc!=4){
    throw std::invalid_argument("Incorrect number of command line arguments");
  }

  const char* programmFileName=argv[1];
  const char* inputFileName=argv[2];
  const char* outputFileName=argv[3];

  
  std::ifstream inFile(inputFileName);

  
  int size_ribbon=0;
  int max_tact=0;
  std::string ribbon;

  inFile>>size_ribbon>>max_tact>>ribbon;

  if(!inFile.is_open()){ 
    throw std::invalid_argument("infile open error");
  }

  if(size_ribbon<0 || max_tact<0){
    throw std::invalid_argument("Error argument size_ribbon or max_tact");
  }
  

  Program Pr={programmFileName};
  postmachine PM={size_ribbon,Pr.get_program()};
  std::string itog_type;
  try{
    itog_type=PM.calc(add_zero_ribbon(ribbon,size_ribbon),max_tact);
  } 
  catch(...){
    itog_type="Error";
  }
  
  std::ofstream outFile(outputFileName);
  if(!outFile.is_open()){
    throw std::invalid_argument("outfile open error");
  }

  outFile<<itog_type;

  outFile.close();
  return 0;
}

//функция удаления лишних нулей с ленты
std::string add_zero_ribbon(const std::string& Ribbon, int size_rib){
    std::string result = Ribbon;
    
    if (result.size() < size_rib) {
        result.append(size_rib - Ribbon.size(), '0');
    }
    
    if (result.size() > size_rib) {
        result.resize(size_rib);
    }
    
    return result;
  }
