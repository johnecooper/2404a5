///////////////////////////////////////////////////////////////////////////////////////
// ALL PENDING WINDOW
// Shows a list of pending applications for all courses
//   sorted by applicant's major GPA or research area

#include <fstream>

#include "AllPendingUI.h"
#include "AdminOptionUI.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "Tools.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
AllPendingUI::AllPendingUI(Manager* aManager) 
: aTable(3, 3, false),
  aLabel("List of all applications sorted by Major GPA and Research Area"),
  backButton("Back"),
  cancelButton("Cancel"),
  saveButton("Save"),
  summary(10, false, Gtk::SELECTION_NONE)
{
  manager = aManager;

  set_default_size(1200, 500);
  set_title("cuTAES");
  set_modal(true);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  set_deletable(false);

  // Scrolled window settings
  scrolledWindow.set_border_width(5);
  scrolledWindow.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);  

  summary.set_column_title(0, "Course");
  summary.set_column_title(1, "UGrad/Grad");
  summary.set_column_title(2, "Student #");
  summary.set_column_title(3, "First Name");
  summary.set_column_title(4, "Last Name");
  summary.set_column_title(5, "E-mail");
  summary.set_column_title(6, "Major/Research");
  summary.set_column_title(7, "Year/Program");
  summary.set_column_title(8, "CGPA/Supervisor");
  summary.set_column_title(9, "Major GPA");

  fillSummary();

  scrolledWindow.add(summary);

  aTable.attach(aLabel, 0, 2, 0, 1,Gtk::EXPAND,Gtk::FILL,0,10);
  aTable.attach(backButton, 0, 1, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(cancelButton, 2, 3, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(saveButton, 1, 2, 2, 3,Gtk::FILL,Gtk::FILL,40,50);
  aTable.attach(scrolledWindow, 0, 3, 1, 2);

  add(aTable);

  backButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllPendingUI::on_backButton), "Back") );
  cancelButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllPendingUI::on_cancelButton), "Cancel") );
  saveButton.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &AllPendingUI::on_saveButton), "Save") );

  show_all_children();

  //cout << "CONSTRUCT AllPendingUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
AllPendingUI::~AllPendingUI() {
  //cout << "DESTRUCT AllPendingUI" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the back button
void AllPendingUI::on_backButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the cancel button
void AllPendingUI::on_cancelButton(const Glib::ustring& data){
  AdminOptionUI* adminWin = new AdminOptionUI(manager);
  adminWin->show();
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// Event handler for the save button
void AllPendingUI::on_saveButton(const Glib::ustring& data){
  string cn = "./AppSummaries/AllCourseSummary";
  int i = 0;

  // Create an output file
  ofstream outFile(cn.c_str(), ios::out); 
  if (!outFile)
    cout << "Could not open file" << endl;

  // Output application information to permanent storage
  outFile << "*NEW SUMMARY OF ALL PENDING APPLICATIONS*" << endl;
  for ( i =0; i< summary.size(); i++){
    outFile << endl;
    if (summary.get_text(i,0) == "--------")
      continue;
    outFile << summary.get_text(i,0) << endl;
    outFile << summary.get_text(i,1) << endl;
    outFile << summary.get_text(i,2) << endl;
    outFile << summary.get_text(i,3) << endl;
    outFile << summary.get_text(i,4) << endl;
    outFile << summary.get_text(i,5) << endl;
    outFile << summary.get_text(i,6) << endl;
    outFile << summary.get_text(i,7) << endl;
    outFile << summary.get_text(i,8) << endl;
    outFile << summary.get_text(i,9) << endl;
  }
  outFile << endl;
  saveDialog();
}

//////////////////////////////////////////////////////////////////////////
// Fills in the ListViewText widget with appropriate information
void AllPendingUI::fillSummary() {
  int i = 0;

   // Go through all the courses
  CourseQueue::Node* currCrs = manager->getCourseQueue()->front();

  while(currCrs != 0){

    UGradAppQueue* copyU = currCrs->data->getUGradApps();
    UGradAppQueue::Node* currUNode;
  
    GradAppQueue*  copyG = currCrs->data->getGradApps();
    GradAppQueue::Node* currGNode;

    // Add separator for each course if there are apps for the course
    if ( !(copyG->front() == 0 && copyU->front() == 0) && i!=0) {
      summary.append("");
      summary.set_text(i, 0, "--------"); summary.set_text(i, 1, "--------");
      summary.set_text(i, 2, "--------"); summary.set_text(i, 3, "--------");
      summary.set_text(i, 4, "--------"); summary.set_text(i, 5, "--------");
      summary.set_text(i, 6, "--------"); summary.set_text(i, 7, "--------");
      summary.set_text(i, 8, "--------"); summary.set_text(i, 9, "--------");
      i++;
    }
    // If UGradAppQueue isn't empty
    if (copyU->front() != 0) {
      copyU->sortByMGPA();
      currUNode = copyU->front();

      while (currUNode != 0) {
        summary.append("");   
        summary.set_text(i, 0, currUNode->data->getCourse()->getName());
        summary.set_text(i, 1, "UGRAD");
        summary.set_text(i, 2, currUNode->data->getUndergrad()->getStuNum());
        summary.set_text(i, 3, currUNode->data->getUndergrad()->getFirstName());
        summary.set_text(i, 4, currUNode->data->getUndergrad()->getSurname());
        summary.set_text(i, 5, currUNode->data->getUndergrad()->getEmail());
        summary.set_text(i, 6, currUNode->data->getUndergrad()->getMajor());
        summary.set_text(i, 7, Tools::floatToString(currUNode->data->getUndergrad()->getYear()));
        summary.set_text(i, 8, Tools::floatToString(currUNode->data->getUndergrad()->getCGPA()));
        summary.set_text(i, 9, Tools::floatToString(currUNode->data->getUndergrad()->getMGPA()));
        i++;
        currUNode = currUNode->next;
      }
    }
    // If GradAppQueue isn't empty
    if (copyG->front() != 0) { 
      copyG->sortByResearch();
      currGNode = copyG->front();

      while (currGNode != 0) {
        summary.append("");
        summary.set_text(i, 0, currGNode->data->getCourse()->getName());
        summary.set_text(i, 1, "GRAD");
        summary.set_text(i, 2, currGNode->data->getGrad()->getStuNum());
        summary.set_text(i, 3, currGNode->data->getGrad()->getFirstName());
        summary.set_text(i, 4, currGNode->data->getGrad()->getSurname());
        summary.set_text(i, 5, currGNode->data->getGrad()->getEmail());
        summary.set_text(i, 6, currGNode->data->getGrad()->getResearch());
        summary.set_text(i, 7, currGNode->data->getGrad()->getProgram());
        summary.set_text(i, 8, currGNode->data->getGrad()->getSupervisor());
        summary.set_text(i, 9, "");
        i++;
        currGNode = currGNode->next;
      }
    }

    currCrs = currCrs->next;
  }

  // If there are no matches
  if (i == 0)
    summary.append("There are no applications.");

}

//////////////////////////////////////////////////////////////////////////
// Display saved dialog
void AllPendingUI::saveDialog(){
  Gtk::MessageDialog dialog(*this, "Summary saved."); 
  dialog.run();
}

