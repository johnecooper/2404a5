///////////////////////////////////////////////////////////////////////////////////////
// ONE PENDING WINDOW
// Shows a list of pending applications for one course, sorted by applicant's major GPA

#include <fstream>

#include "OnePendingUI.h"
#include "SelectCrsUI.h"
#include "AdminOptionUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "Tools.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
OnePendingUI::OnePendingUI(Manager* aManager, string crs) 
: aTable(3, 3, false),
  aLabel("List of applications sorted by Major GPA and Research Area for " + crs),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save"),
  summary(8, false, Gtk::SELECTION_NONE)
{
  manager = aManager;
  course = crs;

  set_default_size(1100, 500);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS); 

  summary.set_column_title(0, "Student #");
  summary.set_column_title(1, "First Name");
  summary.set_column_title(2, "Last Name");
  summary.set_column_title(3, "E-mail");
  summary.set_column_title(4, "Major/Research");
  summary.set_column_title(5, "Year/Program");
  summary.set_column_title(6, "CGPA/Supervisor");
  summary.set_column_title(7, "Major GPA");

  fillSummary();

  scrolledWindow.add(summary);

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,10);
  aTable.attach(scrolledWindow, 0, 3, 1, 2);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(cancelButton, 2, 3, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(saveButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,50);

  add(aTable);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OnePendingUI::on_backButton), "Back") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OnePendingUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &OnePendingUI::on_saveButton), "Save") );

  show_all_children();

  //cout << "CONSTRUCT OnePendingUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
OnePendingUI::~OnePendingUI() {
  //cout << "DESTRUCT OnePendingUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void OnePendingUI::on_backButton(const Glib::ustring& data){
  SelectCrsUI* selectWin = new SelectCrsUI(manager); 
  selectWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the cancel button
void OnePendingUI::on_cancelButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the save button
void OnePendingUI::on_saveButton(const Glib::ustring& data){
  string cn = "./AppSummaries/ByCourse/" + course;
  int i =0;

  // Create an output file
  ofstream outFile(cn.c_str(), ios::out); 
  if (!outFile)
    cout << "Could not open file" << endl;

  // Output application information to permanent storage
  outFile << "*NEW SUMMARY OF PENDING APPLICATIONS FOR "<< course << "*" << endl;
  for ( i =0; i< summary.size(); i++){
    if (summary.get_text(i,0) == "UNDERGRADS") {
      outFile << endl;
      outFile << "-------- UNDERGRADS --------";
      outFile << endl;
      continue;
    }
    if (summary.get_text(i,0) == "GRADS") {
      outFile << endl;
      outFile << "---------- GRADS -----------";
      outFile << endl;
      continue;
    }
    if (summary.get_text(i,0) == "No Undergrad applications for this course." ||
        summary.get_text(i,0) == "No Grad applications for this course." ) {
      outFile << endl;
      outFile << summary.get_text(i,0) << endl;
      outFile << endl;
      continue;
    }
    outFile << endl;
    outFile << summary.get_text(i,0) << endl;
    outFile << summary.get_text(i,1) << endl;
    outFile << summary.get_text(i,2) << endl;
    outFile << summary.get_text(i,3) << endl;
    outFile << summary.get_text(i,4) << endl;
    outFile << summary.get_text(i,5) << endl;
    outFile << summary.get_text(i,6) << endl;
    outFile << summary.get_text(i,7) << endl;
  }
  outFile << endl;
  saveDialog();
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void OnePendingUI::fillSummary() {
   int i=0;
   // Find course selected in course queue
  CourseQueue::Node* currCrs = manager->getCourseQueue()->front();

  while(currCrs != 0){
    if (currCrs->data->getName() == course)
      break;
    currCrs = currCrs->next;
  }

  UGradAppQueue* copyU = currCrs->data->getUGradApps();
  GradAppQueue*  copyG = currCrs->data->getGradApps();

  // Add separator for undergrads
  summary.append("");
  summary.set_text(i, 0, "UNDERGRADS"); summary.set_text(i, 1, "--------"); 
  summary.set_text(i, 2, "--------");   summary.set_text(i, 3, "--------"); 
  summary.set_text(i, 4, "--------");   summary.set_text(i, 5, "--------"); 
  summary.set_text(i, 6, "--------");   summary.set_text(i, 7, "--------");
  i++;

  i = fillUGradSummary(copyU, i);

  // Add separator for grads
  summary.append("");
  summary.set_text(i, 0, "GRADS");    summary.set_text(i, 1, "--------");
  summary.set_text(i, 2, "--------"); summary.set_text(i, 3, "--------");
  summary.set_text(i, 4, "--------"); summary.set_text(i, 5, "--------");
  summary.set_text(i, 6, "--------"); summary.set_text(i, 7, "--------");
  i++;

  fillGradSummary(copyG, i);
}

//////////////////////////////////////////////////////////////////////////
// Fills in the UndergradApps information
int OnePendingUI::fillUGradSummary(UGradAppQueue* copy, int i) {
  UGradAppQueue::Node* currNode;
  currNode = copy->front();

  // If UGradQueue is empty
  if (currNode == 0) {
    summary.append("");
    summary.set_text(i, 0, "No Undergrad applications for this course.");
    i++;
    return i;
  }  

  copy->sortByMGPA();
  currNode = copy->front();

  while (currNode != 0) {
    if (currNode->data->getCourse()->getName() == course) {
      summary.append("");
      summary.set_text(i, 0, currNode->data->getUndergrad()->getStuNum());
      summary.set_text(i, 1, currNode->data->getUndergrad()->getFirstName());
      summary.set_text(i, 2, currNode->data->getUndergrad()->getSurname());
      summary.set_text(i, 3, currNode->data->getUndergrad()->getEmail());
      summary.set_text(i, 4, currNode->data->getUndergrad()->getMajor());
      summary.set_text(i, 5, Tools::floatToString(currNode->data->getUndergrad()->getYear()));
      summary.set_text(i, 6, Tools::floatToString(currNode->data->getUndergrad()->getCGPA()));
      summary.set_text(i, 7, Tools::floatToString(currNode->data->getUndergrad()->getMGPA()));
      i++;
    }
    currNode = currNode->next;
  }
  
  return i;
}

//////////////////////////////////////////////////////////////////////////
// Fills in the GradApps information
void OnePendingUI::fillGradSummary(GradAppQueue* copy, int i) {
  GradAppQueue::Node* currNode;
  currNode = copy->front();

  // If GradQueue is empty
  if (currNode == 0) {
    summary.append("No Grad applications for this course.");
    return;
  }  

  copy->sortByResearch();
  currNode = copy->front();

  while (currNode != 0) {
    if (currNode->data->getCourse()->getName() == course) {
      summary.append("");
      summary.set_text(i, 0, currNode->data->getGrad()->getStuNum());
      summary.set_text(i, 1, currNode->data->getGrad()->getFirstName());
      summary.set_text(i, 2, currNode->data->getGrad()->getSurname());
      summary.set_text(i, 3, currNode->data->getGrad()->getEmail());
      summary.set_text(i, 4, currNode->data->getGrad()->getResearch());
      summary.set_text(i, 5, currNode->data->getGrad()->getProgram());
      summary.set_text(i, 6, currNode->data->getGrad()->getSupervisor());
      summary.set_text(i, 7, "");
      i++;
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Display save dialog
void OnePendingUI::saveDialog(){
  Gtk::MessageDialog dialog(*this, "Summary saved."); 
  dialog.run();
}

