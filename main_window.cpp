#include "main_window.h"




Main_window::Main_window() {
    set_default_size(900, 600);
    set_title("CSE 1325 File Explorer");
    //Create a managed grid and add it to the main window
    grid = Gtk::manage(new Gtk::Grid()); //create a Grid
    add(*grid);

    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    menubar->set_hexpand(true);

    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

          Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New",true));
          filemenu->append(*menuitem_new);
          Gtk::Menu *new_submenu = Gtk::manage(new Gtk::Menu());
          menuitem_new->set_submenu(*new_submenu);
              Gtk::MenuItem *menuitem_new_file = Gtk::manage(new Gtk::MenuItem("_New File",true));
              new_submenu->append(*menuitem_new_file);
              menuitem_new_file->signal_activate().connect([this]{this->create_new_file_click();});
              Gtk::MenuItem *menuitem_new_folder = Gtk::manage(new Gtk::MenuItem("_New Folder",true));
              new_submenu->append(*menuitem_new_folder);
              menuitem_new_folder->signal_activate().connect([this]{this->create_new_folder_click();});

          Gtk::MenuItem *menuitem_properties = Gtk::manage(new Gtk::MenuItem("_Properties",true));
          filemenu->append(*menuitem_properties);
          menuitem_properties->signal_activate().connect([this]{Dialogs::set_window(this); Dialogs::properties_dialogue("home","/home/","Folder","55","10","100");});
           Gtk::MenuItem *menuitem_open_terminal = Gtk::manage(new Gtk::MenuItem("_Open in Terminal",true));
          filemenu->append(*menuitem_open_terminal);
          menuitem_open_terminal->signal_activate().connect([this]{this->open_terminal_click();});
          Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit",true));
          filemenu->append(*menuitem_quit);


    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
          Gtk::MenuItem *menuitem_tablemode = Gtk::manage(new Gtk::MenuItem("_Table Mode",true));
          viewmenu->append(*menuitem_tablemode);
          Gtk::MenuItem *menuitem_iconmode = Gtk::manage(new Gtk::MenuItem("_Icon Mode",true));
          viewmenu->append(*menuitem_iconmode);

    Gtk::MenuItem *menuitem_edit = Gtk::manage(new Gtk::MenuItem("_Edit", true));
    menubar->append(*menuitem_edit);
    Gtk::Menu *editmenu = Gtk::manage(new Gtk::Menu());
    menuitem_edit->set_submenu(*editmenu);

    Gtk::MenuItem *menuitem_new_file_edit = Gtk::manage(new Gtk::MenuItem("_New File",true));
    editmenu->append(*menuitem_new_file_edit);
    menuitem_new_file_edit->signal_activate().connect([this]{this->create_new_file_click();});
    Gtk::MenuItem *menuitem_new_folder_edit = Gtk::manage(new Gtk::MenuItem("_New Folder",true));
    editmenu->append(*menuitem_new_folder_edit);
    menuitem_new_folder_edit->signal_activate().connect([this]{this->create_new_folder_click();});
    Gtk::MenuItem *menuitem_rename_edit = Gtk::manage(new Gtk::MenuItem("_Rename",true));
    editmenu->append(*menuitem_rename_edit);
    menuitem_rename_edit->signal_activate().connect([this]{edit_mode =true; this->rename_data();});
    Gtk::MenuItem *menuitem_duplicate_edit = Gtk::manage(new Gtk::MenuItem("_Duplicate",true));
    editmenu->append(*menuitem_duplicate_edit);
    menuitem_duplicate_edit->signal_activate().connect([this]{edit_mode =true; this->duplicate_data();});
    Gtk::MenuItem *menuitem_add_to_bookmarks_edit = Gtk::manage(new Gtk::MenuItem("_Add to Bookmarks",true));
    editmenu->append(*menuitem_add_to_bookmarks_edit);
    menuitem_add_to_bookmarks_edit->signal_activate().connect([this]{edit_mode =true; this->add_to_bookmarks();});
    Gtk::MenuItem *menuitem_remove_from_bookmarks_edit = Gtk::manage(new Gtk::MenuItem("_Remove from Bookmarks",true));
    editmenu->append(*menuitem_remove_from_bookmarks_edit);
    menuitem_remove_from_bookmarks_edit->signal_activate().connect([this]{edit_mode =true; this->delete_bookmarks();});



    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    Gtk::MenuItem *menuitem_help_user = Gtk::manage(new Gtk::MenuItem("_Help",true));
    helpmenu->append(*menuitem_help_user);
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About",true));
    helpmenu->append(*menuitem_about);

    /*
      Toolbar Here! contains actions like new file, folder
    */

    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar());
    toolbar->set_hexpand(true);

    Gtk::Image *new_file_image = Gtk::manage(new Gtk::Image{"./icons/newfile.png"});
    Gtk::ToolButton *new_file_button = Gtk::manage(new Gtk::ToolButton(*new_file_image));
    new_file_button->set_tooltip_markup("Create a new File");
    new_file_button->signal_clicked().connect([this]{this->create_new_file_click();});
    toolbar->append(*new_file_button);

    Gtk::Image *new_folder_image = Gtk::manage(new Gtk::Image{"./icons/newfolder.png"});
    Gtk::ToolButton *new_folder_button = Gtk::manage(new Gtk::ToolButton(*new_folder_image));
    new_folder_button->set_tooltip_markup("Create a new Folder");
    new_folder_button->signal_clicked().connect([this]{this->create_new_folder_click();});
    toolbar->append(*new_folder_button);

    Gtk::ToolButton * back_toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::GO_BACK));
    back_toolbutton->set_tooltip_markup("Go back a step");
    back_toolbutton->signal_clicked().connect([this]{this->back_button();});
    toolbar->append(*back_toolbutton);


    Gtk::Image *table_image = Gtk::manage(new Gtk::Image{"./icons/table.png"});
    table_view = Gtk::manage(new Gtk::ToggleToolButton(*table_image));
    table_view->set_tooltip_markup("Enable Table View");
    //table_view->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_table_view_click));

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    sep1->set_expand(true);
    toolbar->append(*sep1);
    toolbar->append(*table_view);

    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    sep2->set_expand(true);
    toolbar->append(*sep2);


    //Display the Current path of the folder
    label = Gtk::manage(new Gtk::Entry());
    label->set_alignment(0.5);
    //label->set_lines(2);
    label->set_hexpand(true);
    //label->set_icon_from_icon_name("Open",Gtk::EntryIconPosition::ENTRY_ICON_SECONDARY);
    label->signal_activate().connect([this]{this->update_to_a_path();});
  


    /*
      bookmarks Bar
    */
    bookmarkbar = Gtk::manage(new Gtk::Toolbar());
    bookmarkbar->set_hexpand(true);

    //Gtk::Image *trash_image = Gtk::manage(new Gtk::Image{"./icons/trashicon.png"});
    //Gtk::ToolButton *trash_button = Gtk::manage(new Gtk::ToolButton(*trash_image));
    //trash_button->set_tooltip_markup("Trash");
    //trash_button->signal_clicked().connect([this]{this->empty_grid();this->populate_grid("Trash","/home/$USER/.local/share/Trash/");});

    Gtk::Image *documents_image = Gtk::manage(new Gtk::Image{"./icons/documents.png"});
    Gtk::ToolButton *documents_button = Gtk::manage( new Gtk::ToolButton(*documents_image));
    documents_button->set_tooltip_markup("Home");
    bookmarks_path.push_back("/home/");
    bookmarks_buttons.push_back(documents_button);
    documents_button->signal_clicked().connect([this]{if(this->selected_bookmark_data=="home"){this->empty_grid();this->populate_grid("Home","/home/");}else {this->selected_bookmark_data="home";}});
    bookmarkbar->append(*documents_button);
    //bookmarkbar->append(*trash_button);


    grid->attach(*menubar, 0, 0, get_width(), 10);
    grid->attach_next_to(*toolbar, *menubar, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    grid->attach_next_to(*label, *toolbar, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    grid->attach_next_to(*bookmarkbar, *label, Gtk::PositionType::POS_BOTTOM, get_width(), 10);

    scrolledwindow = Gtk::manage(new Gtk::ScrolledWindow());
   
    
    scrolledwindow = Gtk::manage(new Gtk::ScrolledWindow());
    grid->attach_next_to(*scrolledwindow, *bookmarkbar, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    scrolledwindow->set_min_content_width(get_width());
    scrolledwindow->set_min_content_height(get_height());
    scrolledwindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    scrolledwindow->set_hexpand(false);
    scrolledwindow->set_vexpand(true);
   
   grid_button = Gtk::manage(new Gtk::Grid());
   //grid_button->set_row_homogeneous(true);
   grid_button->set_column_homogeneous(true);
   scrolledwindow->add(*grid_button);
   
    status_bar= Gtk::manage(new Gtk::Label("Ready"));
    status_bar->set_hexpand(true);
    grid->attach_next_to(*status_bar, *scrolledwindow, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    folder_image = Gtk::manage(new Gtk::Image{"./icons/folder.png"});
    file_image= Gtk::manage(new Gtk::Image{"./icons/file.png"});
    show_all();
    Main_window::path_stack.push_back("/");
    Main_window::path_stack.push_back("home");
    populate_grid("home","/home/");
    edit_mode= false;
    selected_data="0";
}

Main_window::~Main_window(){

}

void Main_window::on_grid_button_click(std::string name_of_clicked_object){
  std::cout  << name_of_clicked_object <<'\n';
  std::string new_name;
  std::string new_path ;
  try{
    for(auto e: folder_path->files_inside){
      if(name_of_clicked_object.compare(e.name)==0){
        new_name = e.name;
        new_path = e.path + new_name + '/';
        path_stack.push_back(new_name);
        std::cout<<"Match found";
        std ::string final_command = "cd";
        final_command = final_command+ " "+ new_path;
        const char * cmd = final_command.c_str();
        if(system(cmd)==0){
          std::cout<<"came here"<<e.name<<'\n';
          //empty_grid();
          //Main_window::populate_grid(new_name, new_path);
          //update_status_bar("Opened a folder"); 
        }          
      else{
        e.open();
        new_name = folder_path->name;
        new_path = folder_path->path;
        update_status_bar("Opened a file");
        }      
      }
    }
  }
  catch(std::exception& e){
    std::cout<<"Sometjing happened here"<<e.what();
    //update_status_bar("Navigating to this folder encountered an error. Check privileeges");
  }
  empty_grid();
  Main_window::populate_grid(new_name, new_path);
  update_status_bar("Opened a folder"); 
}

bool Main_window::is_a_folder(std::string filename){
  if(filename.find(".")!=std::string::npos) return false;
  else return true;
}

void Main_window::populate_grid(std::string name,std::string pathname){
  folder_path = new Folder{name,pathname};
  row=1, column =1;
  for(auto e : folder_path->files_inside){    
    Gtk::Button* button_file = Gtk::manage(new Gtk::Button());
    if(is_a_folder(e.name)){
      button_file->set_image(*folder_image);
      button_file->set_image_position(Gtk::PositionType::POS_TOP);
      button_file->set_always_show_image(true);
    } 
    else{
      button_file->set_image(*file_image);
      button_file->set_image_position(Gtk::PositionType::POS_TOP);
      button_file->set_always_show_image(true);
    } 
    button_file->set_label(e.name);
    button_file->set_focus_on_click(true);
    //button_file->add_submenu(*right_click_menu);
    grid_button->attach(*button_file,column,row,1,1 );
    button_file->add_events(Gdk::BUTTON_PRESS_MASK);
    //selected_data=e.name;
    //button_file->signal_button_press_event().connect_notify(sigc::slot(button_file, &Main_window::on_icons_click,this));
    button_file->signal_clicked().connect([this,button_file]{if(selected_data==button_file->get_label())this->on_grid_button_click(button_file->get_label());else{selected_data= button_file->get_label(); this->update_status_bar(button_file->get_label()+" Selected");} });
    Main_window::buttons.push_back(button_file);
    //std::cout<<"Grid population here:"<<e.name<<'\n';  
    column++;
    if(column>3) {
      column =1;
      row++;
    }
  }
  grid->show_all();
  update_path();
}
void Main_window::update_path(){
  label->set_text(folder_path->path);
}
void Main_window::empty_grid(){
  delete folder_path;
  for(auto e : Main_window::buttons){
    grid_button->remove(*e);
  }
  buttons.clear();  //to clear the vector.
}

void Main_window::back_button(){
  if(path_stack.back()!="/"){
  //delete folder_path; //moved to empty grid
  path_stack.pop_back();
  std::string new_path;
  for(int i=0; i<path_stack.size();++i){
    if(path_stack.size()>1)
      new_path = new_path + path_stack.at(i) + '/';
    else
      new_path = new_path + path_stack.at(i) ;
  }
  std::string new_name = path_stack.back();
  update_status_bar("Directory changed back to parent"); 
  empty_grid();
  populate_grid(new_name,new_path);
  }
}

void Main_window::create_new_file_click(){
  try
  {
    Dialogs::set_window(this);
    std::string filename = Dialogs::get_string("Please enter the filename", "New File");
    std::cout<<filename;
    if(!(filename=="0")){
      std ::string final_command = "touch";
      final_command = "cd "+ folder_path->path + "&& " + final_command+ " " + filename;
      const char * cmd = final_command.c_str();
      system(cmd) ;
      update_status_bar("New file created");
    }
    else
    {
      update_status_bar("New File Creation Cancelled");
    }
    
    
    std::cout<<filename<<'\n';
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    update_status_bar("New File Creation encountered an error. Check privileeges");
  }
  std::string new_name= folder_path->name;
  std::string new_path= folder_path->path;
  //delete folder_path;
  empty_grid();
  populate_grid(new_name,new_path );
}

void Main_window::create_new_folder_click(){
  try
  {
    Dialogs::set_window(this);
    std::string filename = Dialogs::get_string("Please enter the foldername", "New Folder");
    std::cout<<filename;
    if(!(filename=="0")){
      std ::string final_command = "mkdir";
      final_command = "cd "+ folder_path->path + "&& " + final_command+ " " + filename;
      const char * cmd = final_command.c_str();
      system(cmd); 
      update_status_bar("New folder created");
    }
    else
    {
      update_status_bar("New Folder Creation Cancelled");
    }
    
    std::cout<<filename<<'\n';
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    update_status_bar("New Folder Creation encountered an error. Check privileeges");
  }
  std::string new_name= folder_path->name;
  std::string new_path= folder_path->path;
  //delete folder_path;
  empty_grid();
  populate_grid(new_name,new_path );
}

void Main_window::update_status_bar(std::string msg){
  status_bar->set_text(msg);
}

void Main_window::open_terminal_click(){
  std::string command = folder_path->path;
  command = "cd " + command + " && gnome-terminal";
  const char *cmd = command.c_str();
  if(system(cmd)==0) update_status_bar("Terminal opened");
  else update_status_bar("Terminal open faield");
}

void Main_window::update_to_a_path(){
  std::string item_;
  std::string new_path = label->get_text();
  std ::string final_command = "cd";
  std::string new_name; 
  final_command = final_command+ " "+ new_path;
  const char * cmd = final_command.c_str();
  if(new_path.back()=='/'){
    if(system(cmd)==0){
    std::cout<<"came here"<<new_path<<'\n';
    //change the path_stack to the new string if path is possible
    path_stack.clear();
    std::stringstream ss{new_path};
    
    path_stack.push_back("/");
    while (std::getline(ss,item_, '/'))
    {
      std::cout<<item_<<'\n';
      path_stack.push_back(item_);
    }
    empty_grid();
    Main_window::populate_grid(path_stack.back(), new_path);
    update_status_bar("Successfully navigated to a folder"); 
  }
  else{
    update_status_bar("No such folder exists!");
  }
  }
  else
  {
    update_status_bar("No such folder! Maybe you forgot '/' at the end?");
  }
  
}

void Main_window::rename_data(){
 try
 {
  Dialogs::set_window(this);
  int exit_value=1;
  while(exit_value){
    exit_value=0;
    std::string new_name = Dialogs::get_string("Please enter the new file name","Rename a file");
    if(new_name=="0") update_status_bar("Rename cancelled");
    else{
      std::string directory_path= label->get_text();  
      std::string final_command = "mv " + directory_path + selected_data + " " + directory_path + new_name;
      const char * cmd = final_command.c_str();
      system(cmd); 
      update_status_bar("Renamed");
      edit_mode = false;
      selected_data="0";
      }
  }
 }
 catch(const std::exception& e)
 {
   std::cerr << e.what() << '\n';
 }
  std::string new_name= folder_path->name;
  std::string new_path= folder_path->path;
  empty_grid();
  populate_grid(new_name,new_path);
}

void Main_window::duplicate_data(){
  Dialogs::set_window(this);
  std::string response = Dialogs::get_string("Please enter new filename", "Duplicate File");
  if(response=="0") update_status_bar("Rename cancelled");
  std::string final_cmd = "touch " + folder_path->path + response;
  try
  {
    const char * cmd= final_cmd.c_str();
    if(system(cmd)==0) update_status_bar("Duplicated!");
    else update_status_bar("Failure"); 
    edit_mode = false;
    selected_data="0"; 
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }  
  std::string new_name= folder_path->name;
  std::string new_path= folder_path->path;
  empty_grid();
  populate_grid(new_name,new_path);
}

void Main_window::delete_bookmarks(){
  if(selected_bookmark_data== "0"){
    update_status_bar("Nothing selected");
  }
  else{
    if(!(bookmarks_path.empty())){
      for(auto e: bookmarks_buttons){
        if(e->get_label()==selected_bookmark_data){
          bookmarkbar->remove(*e);
          break;
        }
      }
      bookmarks_path.pop_back();
      bookmarks_buttons.pop_back();
      bookmarkbar->show_all();
      update_status_bar("Successfully deleted member from bookmarks bar");
    }
  }
  
}

void Main_window::add_to_bookmarks(){
  if(selected_data== "0"){
    update_status_bar("Nothing selected");
  }
  else
  {
    std::string new_path = folder_path->path + selected_data +"/";
    bookmarks_path.push_back(new_path);
    Gtk::Image* img;
    if(is_a_file(new_path)){
      img = Gtk::manage(new Gtk::Image{"./icons/file.png"});
    }
    else{
      img = Gtk::manage(new Gtk::Image{"./icons/folder.png"});
    }
    Gtk::ToolButton* new_toolbutton = Gtk::manage(new Gtk::ToolButton(*img));
    bookmarks_buttons.push_back(new_toolbutton);
    new_toolbutton->set_label(selected_data);
    img->set_tooltip_markup(new_path);
    new_toolbutton->signal_clicked().connect([this,new_toolbutton,img]{if(this->selected_bookmark_data==new_toolbutton->get_label()) {this->empty_grid(); this->populate_grid(new_toolbutton->get_label(),img->get_tooltip_markup());}else {this->selected_bookmark_data=new_toolbutton->get_label(); this->update_status_bar("Bookmarks item selected.");}});
    bookmarkbar->append(*new_toolbutton);
    bookmarkbar->show_all();
    update_status_bar("New item added to bookmars bar");
  }
  
}

int Main_window::is_a_file(std::string path_name){
try
{
  path_name = "cd " + path_name;
  const char* cmd = path_name.c_str();
  if(system(cmd)==0){
    return 0;
  } 
  else {
    return 1;
  }
}
catch(const std::exception& e)
{
  std::cerr << e.what() << '\n';
}
return 0;
}

void Main_window::update_bookmarks_bar(){

}

void on_icons_click(Gtk::Button* button,GdkEventButton* event, Main_window* val){
  if(event->type == GDK_2BUTTON_PRESS){
    //on_grid_button_click(val->selected_data);
  }
  if(event->type == GDK_BUTTON_SECONDARY){
    std::cout<<"Right menu clicked";
  }
}
