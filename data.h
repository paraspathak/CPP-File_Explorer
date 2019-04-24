#ifndef DATA_H
#define DATA_H

#include <string>
#include <unistd.h>

class Data {
public:
  Data(std::string file_name, std::string path_to_file);
  std::string name;
  std::string path;
private:
protected:

};

#endif
