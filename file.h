#ifndef _FILE_H
#define _FILE_H
#include <cstdlib>
#include <string>

#include "data.h"

class File : public Data {
public:
  File(std::string filename, std::string path_name);
  ~File();
  void open();
  void set_date_modified(std::string date);
  std::string get_date_modified(std::string date);
private:
  std::string date_modified;
};

#endif
