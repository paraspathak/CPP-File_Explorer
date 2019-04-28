#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "folder.h"
#include <string>
#include "dialogs.h"
#include "algorithm.h"
#include <stdlib.h>
#include <cstdio>

class Main_window : public Gtk::Window
{
    public:
        Main_window();
        virtual ~Main_window();

    protected:

    private:
    int row, column;
    bool edit_mode;
    Gtk::Entry *search_entry;
    bool copy_over_cut;
    Gtk::Image* folder_image;
    std::string copy_from;
    std::string copy_name;
    Gtk::Image* file_image;
    std::string selected_data;
    std::string selected_bookmark_data;
    std::vector <Gtk::Button*> buttons;
    std::vector <Gtk::ToolButton*> bookmarks_buttons;
    std::vector <std::string> path_stack;
    std::vector <std::string> bookmarks_path;
    Gtk::Grid *grid;
    Folder *folder_path;
    Gtk::Toolbar *bookmarkbar;
    Gtk::Menu *right_click_menu;
    Gtk::Label *status_bar;
    Gtk::ToggleToolButton *table_view;
    Gtk::ScrolledWindow *scrolledwindow;
    Gtk::Entry *label;  //to show the current working directory
    Gtk::Grid *grid_button;   //to easily add buttons to the grid (files and folders)
    void rename_data();
    void paste_click();
    void duplicate_data();
    void delete_bookmarks();
    void add_to_bookmarks();
    void update_bookmarks_bar();
    void on_grid_button_click(std::string name_of_clicked_object);
    void populate_grid(std::string name, std::string pathname);
    void update_path();
    void back_button();
    void empty_grid();
    bool is_a_file(std::string path_name);
    bool is_a_folder(std::string filename);
    void create_new_file_click();
    void on_icons_click(GdkEventButton* event);
    void create_new_folder_click();
    void open_terminal_click();
    void update_status_bar(std::string msg);
    void update_to_a_path();
    void properties_click();
    int icons_type(std::string name);

};
#endif
