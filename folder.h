#ifndef _FOLDER_H
#define _FOLDER_H

#include <vector>
#include <dirent.h>
#include <exception>
#include <iostream>
#include "data.h"
#include "file.h"

//include typedefs
typedef std::vector<File>::iterator iterator;
typedef std::vector<File>::const_iterator const_iterator;

//class description
class Folder : public Data {
public:
  Folder (std::string filename, std::string path);
  ~Folder();
  iterator begin();
  iterator end();
private:
  std::vector <File> files_inside;

};

#endif
