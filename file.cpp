#include "file.h"

File::File(std::string filename, std::string path_name)
: Data{filename, path_name}
{}

void File::open(){
  std ::string final_command = "xdg-open";
  final_command = final_command+ " "+ get_path() + "/" + get_name();
  const char * cmd = final_command.c_str();
  system(cmd);
}

void File::set_date_modified(std::string date){
  date_modified=date;
}

std::string File::get_date_modified(std::string date){
  return date_modified;
}
File::~File(){}

