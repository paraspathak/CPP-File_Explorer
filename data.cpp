#include "data.h"

Data::Data(std::string file_name, std::string path_to_file)
  : name{file_name}, path{path_to_file}
{
  if(path_to_file==" "){
    path = "~/";
  }
}
