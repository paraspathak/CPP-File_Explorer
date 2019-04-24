#include "folder.h"


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
        //std::cout<<std::string(dirp->d_name)<<"\n";
        files_inside.push_back(File{std::string(dirp->d_name), path});
          /*
        std::string test_path = path + "/" + std::string(dirp->d_name)+ "/";
        const char * cmd = test_path.c_str();
        if(chdir(cmd)){
          folder_inside.push_back(std::string(dirp->d_name));
        }
        else{
          
        }
        */
        
    }
    }

    closedir(dp);
  }

  void Folder::open (std::string _name, std::string _path){
    name = _name;
    path = _path;
  }

  Folder::~Folder(){
    files_inside.clear();
  }
