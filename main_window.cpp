#include "main_window.h"



//Constructor to create the GUI
Main_window::Main_window(bool initialize_bookmarks) {
    Dialogs::set_window(this);
    set_default_size(900, 600);
    set_title("CSE 1325 File Explorer");
    
    //Create a managed grid and add it to the main window
    grid = Gtk::manage(new Gtk::Grid()); //create a Grid
    add(*grid);

    /*
      Menu Bar here 
    */
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    menubar->set_hexpand(true);
    
    /*
      File Menu option
    */
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
          menuitem_properties->signal_activate().connect([this]{this->properties_click();});
          Gtk::MenuItem *menuitem_open_terminal = Gtk::manage(new Gtk::MenuItem("_Open in Terminal",true));
          filemenu->append(*menuitem_open_terminal);
          menuitem_open_terminal->signal_activate().connect([this]{this->open_terminal_click();});
          Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Save Layout",true));
          filemenu->append(*menuitem_quit);
          menuitem_quit->signal_activate().connect([this]{this->save();});

    /*
      View Menu
    */
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
          Gtk::MenuItem *menuitem_tablemode = Gtk::manage(new Gtk::MenuItem("_Table Mode",true));
          viewmenu->append(*menuitem_tablemode);
          Gtk::MenuItem *menuitem_iconmode = Gtk::manage(new Gtk::MenuItem("_Icon Mode",true));
          viewmenu->append(*menuitem_iconmode);

    /*
      Edit Menu
    */
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
      Gtk::MenuItem *menuitem_copy_edit = Gtk::manage(new Gtk::MenuItem("_Copy",true));
      editmenu->append(*menuitem_copy_edit);
      menuitem_copy_edit->signal_activate().connect([this]{copy_from = folder_path->get_path() + selected_data; copy_name = selected_data; copy_over_cut = true; update_status_bar("Item Copied!");});
      Gtk::MenuItem *menuitem_cut_edit = Gtk::manage(new Gtk::MenuItem("_Cut",true));
      editmenu->append(*menuitem_cut_edit);
      menuitem_cut_edit->signal_activate().connect([this]{copy_from = folder_path->get_path() + selected_data; copy_name = selected_data; copy_over_cut = false; update_status_bar("Item cut!");});
      Gtk::MenuItem *menuitem_paste_edit = Gtk::manage(new Gtk::MenuItem("_Paste",true));
      editmenu->append(*menuitem_paste_edit);
      menuitem_paste_edit->signal_activate().connect([this]{this->paste_click();});
      Gtk::MenuItem *menuitem_delete_edit = Gtk::manage(new Gtk::MenuItem("_Delete",true));
      editmenu->append(*menuitem_delete_edit);
      menuitem_delete_edit->signal_activate().connect([this]{this->delete_data();});
    
    /*
      Help Menu
    */
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    Gtk::MenuItem *menuitem_help_user = Gtk::manage(new Gtk::MenuItem("_Help",true));
    helpmenu->append(*menuitem_help_user);
	menuitem_help_user->signal_activate().connect([this] {Dialogs::help_dialog(this); });
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About",true));
	menuitem_about->signal_activate().connect([this] {this->about_dialog(); });
	helpmenu->append(*menuitem_about);

    /*
      Toolbar Here! contains actions like new file, folder
    */

    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar());
    toolbar->set_hexpand(true);

    //New File
    Gtk::Image *new_file_image = Gtk::manage(new Gtk::Image{"./icons/newfile.png"});
    Gtk::ToolButton *new_file_button = Gtk::manage(new Gtk::ToolButton(*new_file_image));
    new_file_button->set_tooltip_markup("Create a new File");
    new_file_button->signal_clicked().connect([this]{this->create_new_file_click();});
    toolbar->append(*new_file_button);
    
    //New Folder
    Gtk::Image *new_folder_image = Gtk::manage(new Gtk::Image{"./icons/newfolder.png"});
    Gtk::ToolButton *new_folder_button = Gtk::manage(new Gtk::ToolButton(*new_folder_image));
    new_folder_button->set_tooltip_markup("Create a new Folder");
    new_folder_button->signal_clicked().connect([this]{this->create_new_folder_click();});
    toolbar->append(*new_folder_button);
    
    //Back Button  
    Gtk::ToolButton * back_toolbutton = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::GO_BACK));
    back_toolbutton->set_tooltip_markup("Go back a step");
    back_toolbutton->signal_clicked().connect([this]{this->back_button();});
    toolbar->append(*back_toolbutton);

    //Table Layout
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

    Gtk::ToggleToolButton * search_toolbutton = Gtk::manage(new Gtk::ToggleToolButton(Gtk::Stock::FIND));
    search_toolbutton->set_tooltip_markup("Upcomming feature! Search for files and folder");
    search_toolbutton->signal_clicked().connect([this]{this->search();});
    toolbar->append(*search_toolbutton);


    /*
      Search Bar
    */
    //search_entry = Gtk::manage(new Gtk::Entry());
    //search_entry->set_text("Enter files and folders to search");

    /*
      Path Bar
    */
    //Display the Current path of the folder
    label = Gtk::manage(new Gtk::Entry());
    label->set_alignment(0.5);
    label->set_hexpand(true);
    label->signal_activate().connect([this]{this->update_to_a_path();});
    
    std::string name = "home"; std::string path="/home/";
    try
    {
      std::ifstream ist{"locale.txt"};
    if(ist){
      double version;
      ist >> version; ist.ignore();
      if(version==1.0) {
        std::getline(ist,name);
        std::getline(ist,path);
      int i; ist>>i; ist.ignore();
      std::string loaded_path;
      for(int j =0; j<i; j++){
        std::getline(ist,loaded_path);
        path_stack.push_back(loaded_path);
      }
      ist>>i; ist.ignore();
      std::string loaded_name;
      bookmarkbar = Gtk::manage(new Gtk::Toolbar());
      bookmarkbar->set_hexpand(true);
      for(int j=0; j<i;j++){
        std::getline(ist, loaded_name);
        std::getline(ist,loaded_path);
        bookmarks_path.push_back(loaded_path);
        Gtk::Image* icons; 
        if(j==0) {
          icons =Gtk::manage(new Gtk::Image{"./icons/documents.png"});
        }
        else if(Algorithm::is_a_folder(loaded_path)){
          icons = Gtk::manage(new Gtk::Image{"./icons/folder.png"});
        }
        else {
          icons = Gtk::manage(new Gtk::Image{"./icons/file.png"});
        }
        icons->set_tooltip_markup(loaded_path);
        Gtk::ToolButton *tb = Gtk::manage(new Gtk::ToolButton(*icons));
        tb->set_label(loaded_name);
        tb->signal_clicked().connect([this,tb,icons]{if(this->selected_bookmark_data==tb->get_label()) {this->empty_grid(); this->populate_grid(tb->get_label(),icons->get_tooltip_markup());}else {this->selected_bookmark_data=tb->get_label(); this->update_status_bar("Bookmarks item selected.");}});
        bookmarkbar->append(*tb);
        bookmarks_buttons.push_back(tb);
      }
      initialize_bookmarks=false;
      }
    }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    

    /*
      bookmarks Bar
    */
   if(initialize_bookmarks){
     bookmarkbar = Gtk::manage(new Gtk::Toolbar());
      bookmarkbar->set_hexpand(true);
      
      //Home by defaults is bookmarked
      Gtk::Image *documents_image = Gtk::manage(new Gtk::Image{"./icons/documents.png"});
      documents_image->set_tooltip_markup("/home/");
      Gtk::ToolButton *documents_button = Gtk::manage( new Gtk::ToolButton(*documents_image));
      documents_button->set_label("Home");
      bookmarks_path.push_back("/home/");
      bookmarks_buttons.push_back(documents_button);
      documents_button->signal_clicked().connect([this]{if(this->selected_bookmark_data=="home"){this->empty_grid();this->populate_grid("Home","/home/");}else {this->selected_bookmark_data="home";}});
      bookmarkbar->append(*documents_button);
    }
    //bookmarkbar->append(*trash_button);

    /*
      Attaching members to the grid
    */
    grid->attach(*menubar, 0, 0, get_width(), 10);
    grid->attach_next_to(*toolbar, *menubar, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    grid->attach_next_to(*label, *toolbar,Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    //grid->attach_next_to(*label, *search_entry, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    grid->attach_next_to(*bookmarkbar, *label, Gtk::PositionType::POS_BOTTOM, get_width(), 10);

    //Scrolled window which is used for displaying the files and folders
    scrolledwindow = Gtk::manage(new Gtk::ScrolledWindow());    
    scrolledwindow = Gtk::manage(new Gtk::ScrolledWindow());
    grid->attach_next_to(*scrolledwindow, *bookmarkbar, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    scrolledwindow->set_min_content_width(get_width());
    scrolledwindow->set_min_content_height(get_height());
    scrolledwindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    scrolledwindow->set_hexpand(false);
    scrolledwindow->set_vexpand(true);
   
   //Add a grid to add buttons representing icons
   grid_button = Gtk::manage(new Gtk::Grid());
   //grid_button->set_row_homogeneous(true);
   grid_button->set_column_homogeneous(true);
   scrolledwindow->add(*grid_button);
   
  /*
    Status Bar
  */
    status_bar= Gtk::manage(new Gtk::Label("Ready"));
    status_bar->set_hexpand(true);
    grid->attach_next_to(*status_bar, *scrolledwindow, Gtk::PositionType::POS_BOTTOM, get_width(), 10);
    
    /*Show all childrens*/
    show_all();

    //Default location is at home
    if(initialize_bookmarks){
      Main_window::path_stack.push_back("/");
      Main_window::path_stack.push_back("home");
      populate_grid("home","/home/");
    }
    populate_grid(name,path);
    
    edit_mode= false;
    selected_data="0";
    //signal_delete_event().connect([this]{this->on_quit_click();});
    //signal_delete_event().connect(sigc::mem_fun(&Main_window::on_quitclick));
}

//Destructor
Main_window::~Main_window(){

}

void Main_window::save(){
  std::ofstream ofs {"locale.txt"};
  ofs<<"1.0"<<'\n';
  ofs<<folder_path->get_name()<<'\n';
  ofs<<folder_path->get_path()<<'\n';
  ofs<<path_stack.size()<<'\n';
  for(auto e: path_stack){
    ofs<<e<<'\n';
  }
  ofs<<bookmarks_buttons.size()<<'\n';
  for(auto e: bookmarks_buttons){
    ofs<<e->get_label()<<'\n';
    auto* a = e->get_icon_widget();
    ofs<< a->get_tooltip_markup()<<'\n';
  }
}

void Main_window::search(){
  
}

void Main_window::on_grid_button_click(std::string name_of_clicked_object){
  std::cout  << name_of_clicked_object <<'\n';
  std::string new_name;
  std::string new_path ;
  try{
    for(auto e: *folder_path){
      if(name_of_clicked_object.compare(e.get_name())==0){
        new_name = e.get_name();
        new_path = e.get_path() + new_name + '/';
        if(is_a_file(new_path)){
          e.open();
          new_name = folder_path->get_name();
          new_path = folder_path->get_path();
          update_status_bar("Opened a file");
        }          
        else {
          path_stack.push_back(new_name);
          update_status_bar("Opened a folder");       
        } 
      }
    }
  }
  catch(std::exception& e){
    std::cout<<"Sometjing happened here"<<e.what();
    update_status_bar("Navigating to this folder encountered an error. Check privileges");
  }
  empty_grid();
  Main_window::populate_grid(new_name, new_path);
}

bool Main_window::is_a_folder(std::string filename){
  if(filename.find(".")!=std::string::npos) return false;
  else return true;
}

int Main_window::icons_type(std::string name){
  if(name.find(".txt")!=std::string::npos) return 1;  // 1 corresponds with text image
  else if(name.find(".pdf")!=std::string::npos) return 2;  // 2 corresponds with pdf image
  else if(name=="."|| name=="..") return 3;     // 3 corresponds with hidden image
  else if(name.find(".cpp")!=std::string::npos) return 4;  // 4 corresponds with cpp image
  else if(name.find(".h")!=std::string::npos) return 5;    // 5 corresponds with h image
  else return 6; //6 corresponds with rest of data icons
}

void Main_window::populate_grid(std::string name,std::string pathname){
  folder_path = new Folder{name,pathname};
  int row=1, column =1;
  for(auto e : *folder_path){    
    Gtk::Button* button_file = Gtk::manage(new Gtk::Button());
    if(is_a_folder(e.get_name())){
      Gtk::Image *fol = Gtk::manage(new Gtk::Image{"./icons/folder.png"});
      button_file->set_image(*fol);
      button_file->set_image_position(Gtk::PositionType::POS_TOP);
      button_file->set_always_show_image(true);
    } 
    else{
      int number = Main_window::icons_type(e.get_name());
      Gtk::Image * fil;
      switch (number)
      {
      case 1:
        fil = Gtk::manage(new Gtk::Image{"./icons/txt.png"});
        break;
      case 2:
        fil = Gtk::manage(new Gtk::Image{"./icons/pdf.png"});
        break;
      case 3:
        fil = Gtk::manage(new Gtk::Image{"./icons/hidden.png"});
        break;
      case 4:
        fil = Gtk::manage(new Gtk::Image{"./icons/cpp.png"});
        break;
      case 5:
        fil = Gtk::manage(new Gtk::Image{"./icons/h.png"});
        break;
      case 6:
        fil = Gtk::manage(new Gtk::Image{"./icons/data.png"});
        break;
      default:
        fil = Gtk::manage(new Gtk::Image{"./icons/data.png"});
        break;
      }
      //Gtk::Image *fil = Gtk::manage(new Gtk::Image{"./icons/file.png"});
      button_file->set_image(*fil);
      button_file->set_image_position(Gtk::PositionType::POS_TOP);
      button_file->set_always_show_image(true);
    } 
    button_file->set_label(e.get_name());
    button_file->set_focus_on_click(true);
    //button_file->add(*right_click_menu);
    grid_button->attach(*button_file,column,row,1,1 );
    button_file->add_events(Gdk::BUTTON_PRESS_MASK);
    //selected_data=e.name;
    //button_file->signal_button_press_event().connect_notify(sigc::slot(*this, &Main_window::on_icons_click));
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
  label->set_text(folder_path->get_path());
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
  selected_data = new_name;
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
      final_command = "cd "+ folder_path->get_path() + "&& " + final_command+ " " + filename;
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
  std::string new_name= folder_path->get_name();
  std::string new_path= folder_path->get_path();
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
      final_command = "cd "+ folder_path->get_path() + "&& " + final_command+ " " + filename;
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
  std::string new_name= folder_path->get_name();
  std::string new_path= folder_path->get_path();
  empty_grid();
  populate_grid(new_name,new_path );
}

void Main_window::update_status_bar(std::string msg){
  status_bar->set_text(msg);
}

void Main_window::open_terminal_click(){
  std::string command = folder_path->get_path();
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
  std::string new_name= folder_path->get_name();
  std::string new_path= folder_path->get_path();
  empty_grid();
  populate_grid(new_name,new_path);
}

void Main_window::duplicate_data(){
  Dialogs::set_window(this);
  std::string response = Dialogs::get_string("Please enter new filename", "Duplicate File");
  if(response=="0") update_status_bar("Rename cancelled");
  std::string final_cmd = "touch " + folder_path->get_path() + response;
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
  std::string new_name= folder_path->get_name();
  std::string new_path= folder_path->get_path();
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
    std::string new_path = folder_path->get_path() + selected_data +"/";
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

bool Main_window::is_a_file(std::string path_name){
  return !Algorithm::is_a_folder(path_name);
}

void Main_window::update_bookmarks_bar(){

}

void Main_window::on_icons_click(GdkEventButton* event){
  if(event->type == GDK_2BUTTON_PRESS){
    //on_grid_button_click(val->selected_data);
  }
  if(event->type == GDK_BUTTON_SECONDARY){
    std::cout<<"Right menu clicked";
  }
}

void Main_window::properties_click(){
  Dialogs::set_window(this);
  if(selected_data==folder_path->get_name()){
    Algorithm alg{folder_path->get_path()};
    Dialogs::properties_dialogue(folder_path->get_name(),folder_path->get_path(),alg.file_type(),std::to_string(alg.size_on_disk()),std::to_string(alg.number_of_folder()),std::to_string(alg.number_of_files()));  
  }
  else
  {
    std::string new_name = selected_data;
    std::string new_path = folder_path->get_path() + selected_data;
    Algorithm alg{new_path};
    Dialogs::properties_dialogue(new_name,new_path,alg.file_type(),std::to_string(alg.size_on_disk()),std::to_string(alg.number_of_folder()),std::to_string(alg.number_of_files()));
  } 
}

void Main_window::delete_data(){
  std::string c_name = folder_path->get_name();
  std::string c_path = folder_path->get_path();
  if(!(selected_data=="0")){
    std::string cmd = "rm -r " + c_path + "/" + selected_data;
    if(system(cmd.c_str())==0){
      update_status_bar("Deleted!");
    }
    else {
      update_status_bar("Cannot delete!");
    }
  }
  empty_grid();
  populate_grid(c_name, c_path);
}

void Main_window::paste_click(){
  std::string command; 
  std::string current_name= folder_path->get_name();
  std::string current_path= folder_path->get_path();
  if(copy_from != "0" && copy_over_cut) {
    command = "cp -R -b " + copy_from + " " + current_path ;
  }
  else if( copy_from !="0" && !copy_over_cut){
    command = "mv -b " + copy_from + " " + current_path ;
  }
  if(system(command.c_str())==0){
    update_status_bar("Paste Successful!");
  }
  //If the item is currenlty in the bookmarks bar, the item is removed
  //Need to write code to update the item
  for(auto e : bookmarks_buttons){
    if(e->get_label()==copy_name){
      //auto a = e->get_image(); //Maybe get_widget?
      bookmarkbar->remove(*e);
      //auto new_item = Gtk::manage(new Gtk::ToolButton(*a));
    }
  }
  copy_from="0";
  copy_over_cut = true;
  empty_grid();
  populate_grid(current_name, current_path);
}

void Main_window::about_dialog() {
	Gtk::AboutDialog dialog{};
	dialog.set_transient_for(*this);
	dialog.set_program_name("CPP File Explorer");
	auto logo = Gdk::Pixbuf::create_from_file("./icons/logo.png");
	dialog.set_logo(logo);
	dialog.set_version("Version 1.0.0");
	dialog.set_copyright("Copyright 2019");
	dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
	std::vector< Glib::ustring > authors = { "Paras Pathak" };
	dialog.set_authors(authors);
	std::vector< Glib::ustring > artists = { "Table::   https://www.iconfinder.com/search/?q=table   Free to use",
												"New Folder :: http://www.iconarchive.com/tag/new-folder GNU public",
												"Trash Icon:: http://www.iconarchive.com/show/vista-general-icons-by-iconshock/trash-icon.html Non comercial use",
												"Documents:: http://www.iconarchive.com/show/mac-folders-icons-by-hopstarter/Documents-icon.html Commerical allowed",
												"Folder Icon: http://www.iconarchive.com/show/small-n-flat-icons-by-paomedia/folder-icon.html Public domain license",
												"CPP icon: https://icons8.com/icons/set/.cpp",
												"h icon: https://www.iconfinder.com/icons/314546/document_file_h_icon",
												"pdf icon: adobe.com ",
												"txt: https://www.iconfinder.com/icons/314556/document_file_txt_icon" };
	dialog.set_artists(artists);
	dialog.run();
}