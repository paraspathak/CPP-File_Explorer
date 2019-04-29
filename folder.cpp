#include "folder.h"

typedef std::vector<File>::iterator iterator;
typedef std::vector<File>::const_iterator const_iterator;
  

Folder::Folder(std::string filename, std::string path)
  : Data(filename, path)
  {
    DIR *dp;
    struct dirent *dirp;
    if((dp= opendir(path.c_str()))==NULL){
      std::cerr<<"No such path";
    }
    else{
      while((dirp= readdir(dp))!=NULL){
        files_inside.push_back(File{std::string(dirp->d_name), path});
      }
    }
    closedir(dp);
}

iterator Folder::begin(){
  return files_inside.begin();
}

iterator Folder::end(){
  return files_inside.end();
}

Folder::~Folder(){
  files_inside.clear();
}
