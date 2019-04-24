#ifndef _FILE_H
#define _FILE_H
#include <cstdlib>
#include <string>

#include "data.h"

class File : public Data {
public:
  File(std::string filename, std::string path_name);
  void open();
  void rename();
  void delete_file();
  void copy();
  void cut();
private:
  std::string date_modified;
};

#endif
