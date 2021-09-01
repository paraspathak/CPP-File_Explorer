#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "folder.h"
#include <string>
#include "dialogs.h"
#include "algorithm.h"
#include <stdlib.h>
#include <cstdio>
#include <fstream>

class Main_window : public Gtk::Window
{
public:
    Main_window(bool initialize_bookmarks);
    virtual ~Main_window();

protected:
    // Handling data
    void rename_data();
    void paste_click();
    void duplicate_data();
    void create_new_file_click();

    //Handling bookmarks
    void delete_bookmarks();
    void add_to_bookmarks();
    void update_bookmarks_bar();
    void create_new_folder_click();
    
    //Populating and tracking elements in the grid
    void on_grid_button_click(std::string name_of_clicked_object);
    void populate_grid(std::string name, std::string pathname);
    void empty_grid();
    
    //GDK signal handlers, Not implemented. Need help!
    void on_icons_click(GdkEventButton* event);
    bool on_quitclick(GdkEventAny* event);

    //Features with dedicated GUI buttons
    void update_path(); 
    void update_to_a_path();  
    void update_status_bar(std::string msg); 
    void back_button();
    
    //Helper functions
    bool is_a_file(std::string filename);
    bool is_a_folder(std::string pathname);
    int icons_type(std::string name);
    
    //Additional features
    void open_terminal_click();    
    void properties_click();    
    void delete_data();    
    void search();
    void save();

	void about_dialog();

private:
    bool edit_mode;         //to distinguish if edited or not
    bool copy_over_cut;     //to know copy vs cut

    std::string copy_from;      //path to be copied from 
    std::string copy_name;      //item's name
    std::string selected_data;  //data currently selected
    std::string selected_bookmark_data;  //bookmarks data currently selected
    
    std::vector <Gtk::Button*> buttons; //store pointers to buttons in the grid
    std::vector <Gtk::ToolButton*> bookmarks_buttons; //store buttons pointers in the bookmarks bar
    std::vector <std::string> path_stack;  //for back button 
    std::vector <std::string> bookmarks_path; //to know the bookmarks paths (Only used in delete bookmarks. Need to remove it!)
    
    Folder *folder_path; //To store the refernce to the folder
    
    // Gtk elements for quick and easy access and update
    Gtk::Toolbar *bookmarkbar; 
    //Gtk::Menu *right_click_menu;
    Gtk::Label *status_bar;
    Gtk::ToggleToolButton *table_view;
    Gtk::ScrolledWindow *scrolledwindow;
    Gtk::Entry *label;                  //to show the current working directory
    Gtk::Grid *grid_button;             //to easily add buttons to the grid (files and folders)
    Gtk::Entry *search_entry;           //to get the search entry
    Gtk::Grid *grid;                    //to attach and remove widgets as needed
    
};
#endif
