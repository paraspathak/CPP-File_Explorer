#include "folder.h"
#include "file.h"


int main()
{
  std::string filename = "Documents";
  Path asd= "~/Documents";
    Folder folder{filename, asd};

    return 0;
}
