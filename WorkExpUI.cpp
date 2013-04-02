//////////////////////////////////////////////////////////////////////////
// CREATE WORK EXPERIENCE WINDOW
// Prompts user to give more information about related work experience 

#include <fstream>

#include "WorkExpUI.h"
#include "AcceptAppUI.h"
#include "CourseInfoUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "WorkExpQueue.h"
#include "TACourseQueue.h"


//////////////////////////////////////////////////////////////////////////
// Default constructor
WorkExpUI::WorkExpUI(Manager* aManager, WorkExp* work) 
: createTable(7, 3, false),
  aLabel("Please fill in the information about your work experience"),
  respLabel("Responsibilities:"), 
  durationLabel("Duration (# Months): "), 
  startLabel("Start (dd/mm/year): "),
  endLabel("End (dd/mm/year): "),
  nextButton("Next"),
  backButton("Back"),
  skipButton("Skip"),
  otherButton("Other Work")
{
  manager = aManager;
  workExp = work;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  add(createTable);


  //Read from file using getline function
  string date[MAX_BUF];
  int    count = 0;

  ifstream infile("date.txt", ios::in);

  if (!infile) {
    cout << "Could not open file" << endl;
  }
  while (!infile.eof()) {
    getline(infile, date[count]);
    count++;
  }

  //Fill the combo
  int i;
  for (i=0; i<(count-1); i++){
   if(date[i] != "~"){
       day1Combo.append(date[i]);
       day2Combo.append(date[i]);
   }else break;
  }
  for( i= i+1; i <(count -1); i++){
    if(date[i] != "~"){
        month1Combo.append(date[i]);
        month2Combo.append(date[i]);
   }else break;
  }
  for(i= i+1; i <(count -1); i++){
    if(date[i] != "~")
       monthCombo.append(date[i]);
    else break;
  }
  for( i= i+1; i <(count -1); i++){
     year1Combo.append(date[i]);
     year2Combo.append(date[i]);
  }

  day1Combo.set_active(0);
  day2Combo.set_active(0);
  monthCombo.set_active(0);
  month1Combo.set_active(0); 
  month2Combo.set_active(0);
  year1Combo.set_active(0); 
  year2Combo.set_active(0);


  createTable.attach(aLabel, 0, 4, 0, 1, Gtk::FILL,Gtk::FILL,20, 30);
  createTable.attach(respLabel, 0, 1, 1, 2);
  createTable.attach(respEntry, 1, 4, 1, 3);

  createTable.attach(durationLabel, 0, 1, 3, 4);
  createTable.attach(monthCombo, 1, 2, 3, 4, Gtk::FILL,Gtk::FILL,20, 20);

  createTable.attach(startLabel, 0, 1, 4, 5);
  createTable.attach(day1Combo, 1, 2, 4, 5, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(month1Combo, 2, 3, 4, 5, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(year1Combo, 3, 4 ,4, 5, Gtk::FILL,Gtk::FILL,20, 20);

  createTable.attach(endLabel, 0, 1, 5, 6);
  createTable.attach(day2Combo, 1, 2, 5, 6, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(month2Combo, 2, 3, 5, 6, Gtk::FILL,Gtk::FILL,20, 20);
  createTable.attach(year2Combo, 3, 4 ,5, 6, Gtk::FILL,Gtk::FILL,20, 20);

  createTable.attach(backButton, 0, 1, 6, 7, Gtk::FILL,Gtk::FILL,7, 50);
  createTable.attach(skipButton, 1, 2, 6, 7, Gtk::FILL,Gtk::FILL,5, 50);
  createTable.attach(otherButton, 2, 3, 6, 7, Gtk::FILL,Gtk::FILL,5, 50);
  createTable.attach(nextButton, 3, 4, 6, 7,Gtk::FILL,Gtk::FILL,5, 50);

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_nextOrOtherButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_backButton), "Back") );
  skipButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_skipButton), "Skip") );
  otherButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &WorkExpUI::on_nextOrOtherButton), "Other Work") );

  show_all_children();
  //cout << "CONSTRUCT WorkExpUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
WorkExpUI::~WorkExpUI() {
  //cout << "DESTRUCT WorkExpUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of next or other button
void WorkExpUI::on_nextOrOtherButton(const Glib::ustring& data){
  // If the Responsibility entry is empty
  if ((respEntry.get_text()).find_first_not_of(' ')  == string::npos) {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text(
       "Please enter a responsibility."); 
    dialog.run();
  }
  
  // If the Responsibility entry is NOT empty
  else {
    workExp->setResp(respEntry.get_text());
    workExp->setDataMembers(
      monthCombo.get_active_text(),
      day1Combo.get_active_text() + "/" + month1Combo.get_active_text() + "/" + year1Combo.get_active_text(),
      day2Combo.get_active_text() + "/" + month2Combo.get_active_text() + "/" + year2Combo.get_active_text() );
    if (manager->getCurrUGradApp() != 0)
      manager->getCurrUGradApp()->getWorkExpQueue()->pushBack(workExp);
    else
      manager->getCurrGradApp()->getWorkExpQueue()->pushBack(workExp);

    if (data == "Next") {
      AcceptAppUI* acceptWin = new AcceptAppUI(manager);
      acceptWin->show();
    }
    else if (data == "Other Work") {
      WorkExpUI* workWin = new WorkExpUI(manager, new WorkExp(manager)); 
      workWin->show();
    }
    delete this;
  }
}

//////////////////////////////////////////////////////////////////////////
// Event handler for skip button
void WorkExpUI::on_skipButton(const Glib::ustring& data){ 
  AcceptAppUI* acceptWin = new AcceptAppUI(manager);
  acceptWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void WorkExpUI::on_backButton(const Glib::ustring& data){
  if (manager->getCurrUGradApp() != 0) {
    if (!(manager->getCurrUGradApp()->getTACrsQueue()->empty()));
      manager->getCurrUGradApp()->getTACrsQueue()->clear();
  }
  else {
    if (!(manager->getCurrGradApp()->getTACrsQueue()->empty()));
      manager->getCurrGradApp()->getTACrsQueue()->clear();
  }
  CourseInfoUI* crsInfoWin = new CourseInfoUI(manager, 1); 
  crsInfoWin->show();  
  delete this;
}
