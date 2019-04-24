#ifndef _FOLDER_H
#define _FOLDER_H

#include <vector>
#include <dirent.h>
#include <exception>
#include <iostream>
#include "data.h"
#include "file.h"

class Folder : public Data {
public:
  Folder (std::string filename, std::string path);
  std::vector <File> list_files();
  void open (std::string name, std::string path);
  void rename();
  void delete_folder();
  void copy();
  void cut();
  ~Folder();
  std::vector <File>    files_inside;
  std::vector <std::string>  folder_inside; //to store the name of the folders
private:
  //std::vector <File> files_inside;

};

#endif
