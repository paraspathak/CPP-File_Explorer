#include "algorithm.h"

Algorithm::Algorithm(std::string path) : _path{path} 
{
    DIR *dp;
    struct dirent *dirp;
    if((dp= opendir(path.c_str()))==NULL){
      //std::cerr<<"No such path";
    }
    else{
      while((dirp= readdir(dp))!=NULL){
        std::string current_name = std::string(dirp->d_name);
        std::string new_path = path + "/" + current_name;
        if(!Algorithm::is_a_folder(new_path)){
            number_files.push_back(current_name);
        }
        else {
            number_folder.push_back(current_name);
        }
        }
    }
    closedir(dp); 
}

int Algorithm::number_of_files(){
    return number_files.size();
}

int Algorithm::number_of_folder(){
    return number_folder.size();
}

int Algorithm::size_on_disk(){
  Algorithm::update_file_size();
  return Algorithm::size;
}
/*
std::string Algorithm::breadth_first_search_whole(std::string file_name, std::string path_name){
  for(const auto& entry: std::filesystem::recursive_directory_iterator(path_name)){
    if(entry.path().filename()==file_name) return entry.path();
  }
  return "0";
}
*/
std::string Algorithm::file_type(){
  if(is_a_folder(_path)) return "Folder";
  else return "File";
}

std::string Algorithm::last_modified(){
  return Algorithm::date_last_modified;
}
void Algorithm::update_file_size(){
  struct stat s;
  if(stat(_path.c_str(),&s)==0){
    Algorithm::size = s.st_size;
  }
}

bool Algorithm::is_a_folder(std::string path){
  struct stat s;
  if(stat(path.c_str(),&s)==0){
    if(s.st_mode & S_IFDIR){
      return true;
    }
    else return false;
  }
  return false;
}