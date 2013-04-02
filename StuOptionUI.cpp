//////////////////////////////////////////////////////////////////////////
// STUDENT OPTION WINDOW
// Prompts user to select if they want to CREATE or EDIT an application

#include "StuOptionUI.h"
#include "StuAppFormUI.h"
#include "WelcomeUI.h"
#include "GradAppFormUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
StuOptionUI::StuOptionUI(Manager* aManager) 
: stuTable(4, 2, false),
  stuLabel("Please select an option"),
  createButton("Create application"),
  editButton("Edit application"),
  backButton("Back")
{
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  add(stuTable);

  m_Combo.append("Undergraduate");
  m_Combo.append("Graduate");

  m_Combo.set_active(0);

  stuTable.attach(stuLabel, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,120);
  stuTable.attach(m_Combo, 0, 2 , 1, 2,Gtk::FILL,Gtk::FILL,80,10);
  stuTable.attach(createButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,10);
  stuTable.attach(editButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,10);
  stuTable.attach(backButton, 0, 2, 3, 4,Gtk::FILL,Gtk::FILL,175,20);

  createButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuOptionUI::on_createButton), "Create") );
  editButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuOptionUI::on_editButton), "Edit") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &StuOptionUI::on_backButton), "Back") );


  
  show_all_children();
  createButton.set_sensitive(true);
  //cout << "CONSTRUCT StuOptionUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
StuOptionUI::~StuOptionUI() {
  //cout << "DESTRUCT StuOptionUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void StuOptionUI::on_backButton(const Glib::ustring& data){  
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the create button
void StuOptionUI::on_createButton(const Glib::ustring& data){
  if (m_Combo.get_active_text() == "Undergraduate"){
    createButton.set_sensitive(false);
    manager->makeNewUGradApp();
    StuAppFormUI* stuFormWin = new StuAppFormUI(manager, 0);
    stuFormWin->show();  
    delete this;
  }
  else if (m_Combo.get_active_text() == "Graduate"){
    createButton.set_sensitive(false);
    manager->makeNewGradApp();
    GradAppFormUI* gradFormWin = new GradAppFormUI(manager, 0);
    gradFormWin->show();  
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the edit button
void StuOptionUI::on_editButton(const Glib::ustring& data){
  createButton.set_sensitive(true);
  cout << "StuOptionUI window -- Edit button was pressed" << endl;
}
