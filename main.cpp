#include "main_window.h"
#include <gtkmm.h>
#include <fstream>

int main(int argc, char *argv[]){
  auto app = Gtk::Application::create(argc, argv, "cse1325.fileexplorer");
  Main_window win{true};
  return app->run(win);
}
