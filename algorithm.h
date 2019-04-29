#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <filesystem>

class Algorithm{
public:
    Algorithm(std::string path);
    std::string return_path_of_search(std::string path);
    int number_of_files();
    int number_of_folder();
    int size_on_disk();
    std::string last_modified();
    std::string file_type();
    static bool is_a_folder(std::string path);
    //Works with newer version of g++ compiler (version > 8.3.0 in ubuntu)    
    static std::string breadth_first_search_whole(std::string file_name, std::string path_name); 
private:
    std::string _path;
    std::string name;
    int size;
    std::string date_last_modified;
    std::vector<std::string> number_files;
    std::vector<std::string> number_folder;
    void update_file_size();
};