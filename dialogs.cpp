#include "dialogs.h"

void Dialogs::set_window(Gtk::Window* window) {_window = window;}


Gtk::Window* Dialogs::_window;

std::string Dialogs::get_string(std::string dialog_name, std::string title){
    Gtk::Dialog *dialog = (new Gtk::Dialog());
    dialog->set_title(title);

    Gtk::Grid *grid = (new Gtk::Grid());
    dialog->get_content_area()->pack_start(*grid);

    Gtk::Label *label = (new Gtk::Label(dialog_name));
    label->show();

    Gtk::Entry *entry = (new Gtk::Entry());
    entry->set_vexpand(true);
    entry->set_text(dialog_name);

    grid->attach(*label,0,0,45,10);
    grid->attach_next_to(*entry,*label, Gtk::PositionType::POS_RIGHT, 45, 5);

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->set_default_response(1);
    grid->show_all();
    int result = dialog->run();
    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();
    std::string return_value;
    if(result){
        return_value = entry->get_text();
    }
    else {
        return_value = "0";
    }
    delete entry;
    delete label;
    delete grid;
    delete dialog;
    return return_value;

}

void Dialogs::properties_dialogue(std::string name, std::string path, std::string file_type, std::string file_size, std::string no_folder, std::string no_files){
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog());
    dialog->set_title("Properties of "+name);
    dialog->set_default_size(300,300);
    dialog->set_transient_for(*_window);
    Gtk::Grid* main_layout = Gtk::manage(new Gtk::Grid());
    dialog->get_content_area()->pack_start(*main_layout);
    std::string label_format_start="<span fgcolor='#ff0000'><b><big>";
    std::string label_format_end="</big></b></span>";
    std::string entry_format_start="<i>";
    std::string entry_format_end="</i>";
    auto s1 = Gtk::manage(new Gtk::Separator(Gtk::Orientation::ORIENTATION_HORIZONTAL));
    auto s2 = Gtk::manage(new Gtk::Separator(Gtk::Orientation::ORIENTATION_HORIZONTAL));
    Gtk::Label * name_label = Gtk::manage(new Gtk::Label(label_format_start + "Name = " + label_format_end));
    name_label->set_hexpand(true);
    name_label->set_use_markup(true);
    Gtk::Label * name_entry = Gtk::manage(new Gtk::Label(entry_format_start + name + entry_format_end));
    main_layout->attach(*name_label, 0, 0, 50, 5);
    name_entry->set_hexpand(true);
    name_entry->set_use_markup(true);
    main_layout->attach_next_to(*name_entry, *name_label, Gtk::PositionType::POS_RIGHT,50,5);
    Gtk::Label * path_label = Gtk::manage(new Gtk::Label(label_format_start + "Path = " + label_format_end));
     path_label->set_hexpand(true);
     path_label->set_use_markup(true);
    Gtk::Label * path_entry = Gtk::manage(new Gtk::Label(entry_format_start + path + entry_format_end));
     path_entry->set_hexpand(true);
     path_entry->set_use_markup(true);
    main_layout->attach_next_to(*path_label, *name_label, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*path_entry, *name_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    
    main_layout->attach_next_to(*s1, *path_label, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*s2, *path_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    s1->set_hexpand(true);  s2->set_hexpand(true);
    s1->set_vexpand(true);  s2->set_vexpand(true);


    Gtk::Label * filetype_label = Gtk::manage(new Gtk::Label(label_format_start + "File Type = " + label_format_end));
     filetype_label->set_hexpand(true);
     filetype_label->set_use_markup(true);
    Gtk::Label * filetype_entry = Gtk::manage(new Gtk::Label(entry_format_start + file_type + entry_format_end));
     filetype_entry->set_hexpand(true);
     filetype_entry->set_use_markup(true);
    main_layout->attach_next_to(*filetype_label, *s1, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*filetype_entry, *s2, Gtk::PositionType::POS_BOTTOM,50,5);
    Gtk::Label * filesize_label = Gtk::manage(new Gtk::Label(label_format_start + "File Size (in Test) = " + label_format_end));
     filesize_label->set_hexpand(true);
     filesize_label->set_use_markup(true);
    Gtk::Label * filesize_entry = Gtk::manage(new Gtk::Label(entry_format_start + file_size + entry_format_end));
     filesize_entry->set_hexpand(true);
     filesize_entry->set_use_markup(true);
    main_layout->attach_next_to(*filesize_label, *filetype_label, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*filesize_entry, *filetype_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    Gtk::Label * nofolder_label = Gtk::manage(new Gtk::Label(label_format_start + "No of folder = " + label_format_end));
     nofolder_label->set_hexpand(true);
     nofolder_label->set_use_markup(true);
    Gtk::Label * nofolder_entry = Gtk::manage(new Gtk::Label(entry_format_start + no_folder + entry_format_end));
     nofolder_entry->set_hexpand(true);
     nofolder_entry->set_use_markup(true);
    main_layout->attach_next_to(*nofolder_label, *filesize_label, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*nofolder_entry, *filesize_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    Gtk::Label * nofiles_label = Gtk::manage(new Gtk::Label(label_format_start + "No of files = " + label_format_end));
     nofiles_label->set_hexpand(true);
     nofiles_label->set_use_markup(true);
    Gtk::Label * nofiles_entry = Gtk::manage(new Gtk::Label(entry_format_start + no_files + entry_format_end));
     nofiles_entry->set_hexpand(true);
     nofiles_entry->set_use_markup(true);
    main_layout->attach_next_to(*nofiles_label, *nofolder_label, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*nofiles_entry, *nofolder_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    auto s3 = Gtk::manage(new Gtk::Separator(Gtk::Orientation::ORIENTATION_HORIZONTAL));
    auto s4 = Gtk::manage(new Gtk::Separator(Gtk::Orientation::ORIENTATION_HORIZONTAL));
    main_layout->attach_next_to(*s3, *nofiles_entry, Gtk::PositionType::POS_BOTTOM,50,5);
    main_layout->attach_next_to(*s4, *nofiles_label, Gtk::PositionType::POS_BOTTOM,50,5);
    s3->set_hexpand(true);  s4->set_hexpand(true);
    s3->set_vexpand(true);  s4->set_vexpand(true);


    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->set_default_response(1);
    main_layout->show_all();
   
    int result = dialog->run();
    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();
}

void Dialogs::help_dialog(Gtk::Window* window) {
	std::string msg = R"( 
						Double click twice to open a file
						Click once to select a file
						Go to edit menu to view options available
						Add items to bookmarks bar
						click save layout to remember your layout and bookmarks bar
						)";
	Gtk::MessageDialog* dialog = new Gtk::MessageDialog("Help");
	dialog->set_transient_for(*window);
	dialog->set_secondary_text(msg, true);
	dialog->run();

	dialog->close();
	while (Gtk::Main::events_pending())  Gtk::Main::iteration();

	delete dialog;
}