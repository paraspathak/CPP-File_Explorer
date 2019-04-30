#ifndef _DIALOGS_H
#define _DIALOGS_H

#include <gtkmm.h>
#include <string>


class Dialogs {
    public:
        static std::string get_string(std::string dialog_name, std::string title);
        static void properties_dialogue(std::string name, std::string path, std::string file_type, std::string file_size, std::string no_folder, std::string no_files);
        static void set_window(Gtk::Window* window);
		static void help_dialog(Gtk::Window* window);
    private:
        static Gtk::Window* _window;
};

#endif