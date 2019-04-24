#include "file.h"

File::File(std::string filename, std::string path_name)
: Data{filename, path_name}
{}

  void File::open(){
    std ::string final_command = "xdg-open";
    final_command = final_command+ " "+ path + "/" + name;
    const char * cmd = final_command.c_str();
    system(cmd);
  }
