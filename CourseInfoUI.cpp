//////////////////////////////////////////////////////////////////////////
// CREATE COURSES INFORMATION UI
// Prompts user to give more information about related courses

#include <fstream>

#include "CourseInfoUI.h"
#include "StuAppFormUI.h"
#include "GradAppFormUI.h"
#include "WorkExpUI.h"
#include "CourseQueue.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "TACourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Constructor
CourseInfoUI::CourseInfoUI(Manager* aManager, int i) 
: createTable(5, 3, false),
  termLabel("Term: "), 
  yearLabel("Year: "),
  nextButton("Next"),
  courseButton("New Course"),
  backButton("Back")
{
  whichCourse = i;
  initWindow(aManager);
}

//////////////////////////////////////////////////////////////////////////
// Makes the window according to whichCourse
void CourseInfoUI::initWindow(Manager* aManager) {
  manager = aManager;

  set_default_size(500, 350);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);
  add(createTable);


  if (whichCourse == 0) {
    aLabel.set_text("Select a related course taken:");
    finalLabel.set_text("Final Grade: ");
  } 
  else {
    aLabel.set_text("Select a course TA'd for:");
    finalLabel.set_text("Supervisor: ");
    courseCombo.append("None");
  }

  //Read from file using getline function
  string info[MAX_BUF];
  int    count = 0;

  ifstream infile("info.txt", ios::in);

  if (!infile) {
    cout << "Could not open file" << endl;
  }
  while (!infile.eof()) {
    getline(infile, info[count]);
    count++;
  }

  //Fill in courses combo
  // Iterate through course queue and put names into comboBox
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();

  while (currNode != 0){ 
    courseCombo.append(currNode->data->getName());
    currNode = currNode->next;
  }
  courseCombo.set_active(0);

  //Fill the combo
  int i;
  for (i=0; i<(count-1); i++){
   if(info[i] != "~")
       termCombo.append(info[i]);
   else break;
  }
  for( i= i+1; i <(count -1); i++){
    if(info[i] != "~")
	yearCombo.append(info[i]);
    else break;
  }
  if (whichCourse ==0){
    for( i= i+1; i <(count -1); i++)
       finalCombo.append(info[i]);
  }
  else {
    //Read from faculty file using getline function
    string faculty[MAX_BUF];
    count = 0; 

    ifstream infile2("faculty.txt", ios::in);
    if (!infile2) {
      cout << "Could not open file" << endl;
    }
    while (!infile2.eof()) {
      getline(infile2, faculty[count]);
      count++;
    }
    for (i=0; i<(count); i++) 
      finalCombo.append(faculty[i]);
  }

  termCombo.set_active(0);
  yearCombo.set_active(0);
  finalCombo.set_active(0);

  createTable.attach(aLabel, 0, 2, 0, 1, Gtk::FILL,Gtk::FILL, 0, 42);
  createTable.attach(courseCombo, 2, 3, 0, 1, Gtk::FILL,Gtk::FILL, 10, 30);

  createTable.attach(termLabel, 0, 1, 1, 2);
  createTable.attach(termCombo, 1, 3, 1, 2, Gtk::FILL,Gtk::FILL,75, 20); 
  createTable.attach(yearLabel, 0, 1, 2, 3);
  createTable.attach(yearCombo, 1, 3, 2, 3, Gtk::FILL,Gtk::FILL,75, 20); 
  createTable.attach(finalLabel, 0, 1, 3, 4);
  createTable.attach(finalCombo, 1, 3, 3, 4, Gtk::FILL,Gtk::FILL,75, 20); 
  createTable.attach(backButton, 0, 1, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 
  createTable.attach(courseButton, 1, 2, 4, 5,Gtk::FILL,Gtk::FILL,8, 50);
  createTable.attach(nextButton, 2, 3, 4, 5, Gtk::FILL,Gtk::FILL,5, 50); 

  nextButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &CourseInfoUI::on_nextButton), "Next") );
  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &CourseInfoUI::on_backButton), "Back") );
  courseButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &CourseInfoUI::on_courseButton), "New Course") );

  show_all_children();

  //cout << "CONSTRUCT CourseInfoUI" << endl;
}


//////////////////////////////////////////////////////////////////////////
// Destructor
CourseInfoUI::~CourseInfoUI() {
  //cout << "DESTRUCT CourseInfoUI" << endl;
}


//////////////////////////////////////////////////////////////////////////
// Event handler of next button
void CourseInfoUI::on_nextButton(const Glib::ustring& data){
  if (whichCourse == 0) {
    TakenCourse* takenCourse = new TakenCourse(courseCombo.get_active_text(), manager);
    takenCourse->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());
    manager->getCurrUGradApp()->getTakenCrsQueue()->pushBack(takenCourse);    
    CourseInfoUI* crsInfoWin = new CourseInfoUI(manager, 1); 
    crsInfoWin->show();
  }
  else {
    if (courseCombo.get_active_text() == "None") {}
    else {
      TACourse* tACourse = new TACourse(courseCombo.get_active_text(), manager);
      tACourse->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text()); 
      if (manager->getCurrUGradApp() != 0)
        manager->getCurrUGradApp()->getTACrsQueue()->pushBack(tACourse);
      else
        manager->getCurrGradApp()->getTACrsQueue()->pushBack(tACourse);      
    }
    WorkExpUI* workExpWin = new WorkExpUI(manager, new WorkExp("", manager));
    workExpWin->show();
  }

  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of back button
void CourseInfoUI::on_backButton(const Glib::ustring& data){  
  // Clear taken/TAcourse queues
  if (manager->getCurrUGradApp() != 0) { 
    if (whichCourse == 0) {
      if (!(manager->getCurrUGradApp()->getTakenCrsQueue()->empty()));
        manager->getCurrUGradApp()->getTakenCrsQueue()->clear();
      StuAppFormUI* stuFormWin = new StuAppFormUI(manager, 0);
      stuFormWin->show();
    }
    else {
      if (!(manager->getCurrUGradApp()->getTACrsQueue()->empty()));
        manager->getCurrUGradApp()->getTACrsQueue()->clear();
      CourseInfoUI* crsInfoWin = new CourseInfoUI(manager, 0); 
      crsInfoWin->show();
    }
  }
  else {
    if (!(manager->getCurrGradApp()->getTACrsQueue()->empty()));
      manager->getCurrGradApp()->getTACrsQueue()->clear();
    GradAppFormUI* gradFormWin = new GradAppFormUI(manager, 0);
    gradFormWin->show();
  }

  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler of course button
void CourseInfoUI::on_courseButton(const Glib::ustring& data){ 
  if (courseCombo.get_active_text() == "None") {
    Gtk::MessageDialog dialog(*this, "ERROR!"); 
    dialog.set_secondary_text("Please select a course"); 
    dialog.run();
    return;
  }

  if (whichCourse == 0) {
    TakenCourse* takenCourse = new TakenCourse(courseCombo.get_active_text(), manager);
    takenCourse->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());
    manager->getCurrUGradApp()->getTakenCrsQueue()->pushBack(takenCourse);
  }
  else {
    TACourse* tACourse = new TACourse(courseCombo.get_active_text(), manager);
    tACourse->setDataMembers(termCombo.get_active_text(), yearCombo.get_active_text(), finalCombo.get_active_text());  
    if (manager->getCurrUGradApp() != 0)
      manager->getCurrUGradApp()->getTACrsQueue()->pushBack(tACourse);
    else
      manager->getCurrGradApp()->getTACrsQueue()->pushBack(tACourse);
  }

  if (whichCourse == 0) {
    CourseInfoUI* crsInfoWin = new CourseInfoUI(manager, 0); 
    crsInfoWin->show();  
  } 
  else {
    CourseInfoUI* crsInfoWin = new CourseInfoUI(manager, 1); 
    crsInfoWin->show();
  }

  delete this;

}

