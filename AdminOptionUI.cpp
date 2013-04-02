//////////////////////////////////////////////////////////////////////////
// ADMINISTRATION OPTION UI
// Prompts user to select and administrator feature

#include "AdminOptionUI.h"
#include "SelectCrsUI.h"
#include "AllPendingUI.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
AdminOptionUI::AdminOptionUI(Manager* aManager) 
: aTable(3, 2, false),
  aLabel("Please select an option:"),
  nextButton("Next"),
  backButton("Back")
{
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  add(aTable);

  adminCombo.append("View an application");
  adminCombo.append("Assign succesful applicant");
  adminCombo.append("View summary of pending applications");
  adminCombo.append("View a summary of assigned application");
  adminCombo.append("View and edit a TA evaluation");
  adminCombo.set_active(0);

  aCombo.append("By application number");
  aCombo.append("By applicants student number");
  aCombo.append("By applicants name");

  bCombo.append("For one course, sorted by Major GPA and Research Area");
  bCombo.append("For all courses, sorted by course #, then Major GPA and Research Area");

  aTable.attach(aLabel, 0, 1, 0, 1,Gtk::FILL,Gtk::FILL,20,40);
  aTable.attach(adminCombo, 1, 2, 0, 1, Gtk::FILL,Gtk::FILL,25,60);
  aTable.attach(aCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(bCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(cCombo, 0, 2, 1, 2, Gtk::FILL,Gtk::FILL,20,60);
  aTable.attach(backButton, 0, 1, 2, 3, Gtk::FILL,Gtk::FILL,30,56);
  aTable.attach(nextButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,90,56);

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AdminOptionUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AdminOptionUI::on_backButton), "Back") );
  adminCombo.signal_changed().connect(
    sigc::mem_fun(*this, &AdminOptionUI::on_combo_change) );

  show_all_children();
  //cout << "CONSTRUCT AdminOptionUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
AdminOptionUI::~AdminOptionUI() {
  //cout << "DESTRUCT AdminOptionUI" << endl;
}


//////////////////////////////////////////////////////////////////////////
// Event handler for the combobox
void AdminOptionUI::on_combo_change(){
  if(adminCombo.get_active_text() == "View an application")
     aCombo.show();
  else aCombo.hide();
  if(adminCombo.get_active_text() == "View summary of pending applications")
     bCombo.show();
  else bCombo.hide();

}

//////////////////////////////////////////////////////////////////////////
// Event handler for the next button
void AdminOptionUI::on_nextButton(const Glib::ustring& data){
  if(bCombo.get_active_text() == "For one course, sorted by Major GPA and Research Area"){
    SelectCrsUI* selectWin = new SelectCrsUI(manager); 
    selectWin->show();  
    delete this;
  }
  else if(bCombo.get_active_text() == "For all courses, sorted by course #, then Major GPA and Research Area"){
    AllPendingUI* allPending = new AllPendingUI(manager);
    allPending->show();
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void AdminOptionUI::on_backButton(const Glib::ustring& data){
  delete this;
}
