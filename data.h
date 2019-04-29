#ifndef DATA_H
#define DATA_H

#include <string>

class Data {
public:
  Data(std::string file_name, std::string path_to_file);
  virtual ~Data();
  std::string get_name();
  std::string get_path();
private:
  std::string name;
  std::string path;
};

#endif
