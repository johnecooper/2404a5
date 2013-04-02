//////////////////////////////////////////////////////////////////////////
// MANAGER FOR THE cuTAES SYSTEM
// Controls the system's applications and queues

#include <fstream>
#include <sstream>
#include <string>

#include "Manager.h"
#include "Tools.h"
#include "UGradApp.h"
#include "GradApp.h"
#include "UGradInfoQueue.h"
#include "GradInfoQueue.h"
#include "UGradAppQueue.h"
#include "GradAppQueue.h"
#include "CourseQueue.h"
#include "TakenCourseQueue.h"
#include "TakenCourse.h"
#include "TACourseQueue.h"
#include "TACourse.h"
#include "WorkExpQueue.h"
#include "WorkExp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
Manager::Manager() 
: currUGradApp(0),
  currGradApp(0),
  allUGradApps(new UGradAppQueue()),
  allGradApps(new GradAppQueue()),
  allCourses(new CourseQueue()),
  allUGradInfo(new UGradInfoQueue()),
  allGradInfo(new GradInfoQueue())
{
  // Get the last Application number
  string appNumber;
  ifstream infile("lastAppNum.txt", ios::in);
  if (!infile)
    cout<<"Could not open file"<<endl;
  infile >> appNumber;
  istringstream is(appNumber, istringstream::in);
  is >> lastAppNum;

  // Assemble the allCourses queue from reading in course names from a file
  string courses[MAX_BUF];
  int    count=0, i;
  ifstream infile2("courses.txt", ios::in);
  if (!infile2)
    cout << "Could not open file" << endl;
  while (!infile2.eof()) {
    getline(infile2, courses[count]);
    count++;
  }
  for (i=0; i<(count-1); i++) {
    Course* newCourse = new Course(courses[i]);
    allCourses->pushBack(newCourse);
  }

  // Assemble the application and information queues from existing applications
  assembleQueues();

  allUGradApps->print();
  allGradApps->print();
  allUGradInfo->print();
  allGradInfo->print();
  allCourses->print();

  //cout << "CONSTRUCT Manager" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Manager::~Manager() {
  // Output last Application number to file
  ofstream outFile("lastAppNum.txt", ios::out);
  if (!outFile)
    cout << "Could not open file" << endl;
  outFile << lastAppNum << endl;

  cout << endl << endl << "**Deleting allUGradApps" << endl;
  allUGradApps->clear(); // Delete data and nodes
  delete allUGradApps;   // Delete pointer to the queue
  cout << endl << endl << "**Deleting allGradApps" << endl;
  allGradApps->clear();  // Delete data and nodes
  delete allGradApps;    // Delete pointer to queue
  cout << endl << endl << "**Deleting allUGradInfo" << endl;
  delete allUGradInfo;
  cout << endl << endl << "**Deleting allGradInfo" << endl;
  delete allGradInfo;
  cout << endl << endl << "**Deleting allCourses" << endl;
  delete allCourses;

  //cout << "DESTRUCT Manager" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get Functions
CourseQueue*       Manager::getCourseQueue()   { return allCourses;    }
GradAppQueue*      Manager::getGradApps()      { return allGradApps;   }
UGradAppQueue*     Manager::getUGradApps()     { return allUGradApps;  }
GradInfoQueue*     Manager::getGradInfo()      { return allGradInfo;   }
UGradInfoQueue*    Manager::getUGradInfo()     { return allUGradInfo;  }
UGradApp*          Manager::getCurrUGradApp()  { return currUGradApp;  }
GradApp*           Manager::getCurrGradApp()   { return currGradApp;   }

//////////////////////////////////////////////////////////////////////////
// Sets both current applications to be null
void Manager::setCurrAppsNull() { 
  currUGradApp = 0;
  currGradApp  = 0;
}

//////////////////////////////////////////////////////////////////////////
// Creates a new Undergrad Application
UGradApp* Manager::makeNewUGradApp() {
  UGradApp* app = new UGradApp;
  app->setStatus(PENDING);
  app->setAppNum(++lastAppNum);
  currUGradApp = app;
  return app;
}


//////////////////////////////////////////////////////////////////////////
// Creates a new Grad Application
GradApp* Manager::makeNewGradApp() {
  GradApp* app = new GradApp;
  app->setStatus(PENDING);
  app->setAppNum(++lastAppNum);
  currGradApp = app;
  return app;
}

//////////////////////////////////////////////////////////////////////////
// Changes the undergrad Application's members
void Manager::changeUAppMem() {
  UGradApp* newApp = new UGradApp;
  newApp->setStatus(PENDING);
  newApp->setAppNum(++lastAppNum);
  newApp->setUndergrad(currUGradApp->getUndergrad());
  currUGradApp = newApp;
}

//////////////////////////////////////////////////////////////////////////
// Changes the grad Application's members
void Manager::changeGAppMem() {
  GradApp* newApp = new GradApp;
  newApp->setStatus(PENDING);
  newApp->setAppNum(++lastAppNum);
  newApp->setGrad(currGradApp->getGrad());
  currGradApp = newApp;
}

//////////////////////////////////////////////////////////////////////////
// Cancels the current working Application
// Used when user presses the 'Cancel' button the the midst of applying
void Manager::cancelApp() {
  if (currUGradApp) {
    delete currUGradApp->getTakenCrsQueue();
    delete currUGradApp->getTACrsQueue();
    delete currUGradApp->getWorkExpQueue();
    delete currUGradApp;
    currUGradApp = 0;
  }
  else if (currGradApp){
    delete currGradApp->getTACrsQueue();
    delete currGradApp->getWorkExpQueue();
    delete currGradApp;
    currGradApp = 0;
  }

  lastAppNum--;
  //cout << "lastAppNum = " << lastAppNum << endl;
}

//////////////////////////////////////////////////////////////////////////
// Saves the current working Application
//   Adds the current application to the appropriate AppQueue in Manager
//   and in the course object. Then outputs the information into permanent
//   storage.
void Manager::saveApp() {
  string cn;
  int i, takenQueueSize, taQueueSize, workQueueSize;
  TakenCourseQueue::Node* takenNode;
  TACourseQueue::Node* taNode;
  WorkExpQueue::Node* workNode;
  ofstream outFile;

  // Find course selected in course queue
  CourseQueue::Node* currCrs = allCourses->front();

  // If it is a UGradApp
  if (currUGradApp) {
    // Add to AppQueue
    allUGradApps->pushBack(currUGradApp);

    while(currCrs != 0){
      if (currCrs->data->getName() == currUGradApp->getCourse()->getName())
        break;
      currCrs = currCrs->next;
    }
    // Add to AppQueue in course object
    currCrs->data->getUGradApps()->pushBack(currUGradApp);

    // Open the appropriate course file
    cn = "./Applications/UndergradApps/" + currUGradApp->getCourse()->getName();
    outFile.open(cn.c_str(), ios::app); 
    if (!outFile)
      cout << "Could not open file" << endl;

    // Output application information to permanent storage
    outFile << endl;
    outFile << "*NEW UGRAD APPLICATION*" << endl;
    outFile << currUGradApp->getAppNum() << endl;
    outFile << currUGradApp->getCourse()->getName() << endl;
    outFile << currUGradApp->getStatusString(currUGradApp->getStatus()) << endl;
    outFile << currUGradApp->getUndergrad()->getStuNum() << endl;
    outFile << currUGradApp->getUndergrad()->getFirstName() << endl;
    outFile << currUGradApp->getUndergrad()->getSurname() << endl;
    outFile << currUGradApp->getUndergrad()->getEmail() << endl;
    outFile << currUGradApp->getUndergrad()->getMajor() << endl;
    outFile << currUGradApp->getUndergrad()->getYear() << endl;
    outFile << currUGradApp->getUndergrad()->getCGPA() << endl;
    outFile << currUGradApp->getUndergrad()->getMGPA() << endl;

    takenQueueSize = currUGradApp->getTakenCrsQueue()->size();
    taQueueSize    = currUGradApp->getTACrsQueue()->size();
    workQueueSize  = currUGradApp->getWorkExpQueue()->size();

    takenNode = currUGradApp->getTakenCrsQueue()->front();
    taNode    = currUGradApp->getTACrsQueue()->front();
    workNode  = currUGradApp->getWorkExpQueue()->front();

    outFile << endl;
    outFile << "Related courses taken:" << endl;
    for(i=0; i<takenQueueSize; i++){
       outFile << takenNode->data->getName() << endl;
       outFile << takenNode->data->getTerm() << endl;
       outFile << takenNode->data->getYear() << endl;
       outFile << takenNode->data->getFinalGrade() << endl;
       takenNode = takenNode->next;
    } 
  }

  // If it is a GradApp
  else if (currGradApp) {
    // Add to AppQueue
    allGradApps->pushBack(currGradApp);

    while(currCrs != 0){
      if (currCrs->data->getName() == currGradApp->getCourse()->getName())
        break;
      currCrs = currCrs->next;
    }
    // Add to AppQueue in course object
    currCrs->data->getGradApps()->pushBack(currGradApp);

    // Open the appropriate course file
    cn = "./Applications/GradApps/" + currGradApp->getCourse()->getName();
    outFile.open(cn.c_str(), ios::app); 
    if (!outFile)
      cout << "Could not open file" << endl;

    // Output application information to permanent storage
    outFile << endl;
    outFile << "*NEW GRAD APPLICATION*" << endl;
    outFile << currGradApp->getAppNum() << endl;
    outFile << currGradApp->getCourse()->getName() << endl;
    outFile << currGradApp->getStatusString(currGradApp->getStatus()) << endl;
    outFile << currGradApp->getGrad()->getStuNum() << endl;
    outFile << currGradApp->getGrad()->getFirstName() << endl;
    outFile << currGradApp->getGrad()->getSurname() << endl;
    outFile << currGradApp->getGrad()->getEmail() << endl;
    outFile << currGradApp->getGrad()->getResearch() << endl;
    outFile << currGradApp->getGrad()->getProgram() << endl;
    outFile << currGradApp->getGrad()->getSupervisor() << endl;

    taQueueSize    = currGradApp->getTACrsQueue()->size();
    workQueueSize  = currGradApp->getWorkExpQueue()->size();

    taNode    = currGradApp->getTACrsQueue()->front();
    workNode  = currGradApp->getWorkExpQueue()->front();
  }

  outFile << endl;
  outFile << "TA courses taken:" << endl;
  for(i=0; i<taQueueSize; i++){
     outFile << taNode->data->getName() << endl;
     outFile << taNode->data->getTerm()<< endl;
     outFile << taNode->data->getYear()<< endl;
     outFile << taNode->data->getSupervisor()<< endl;
     taNode = taNode->next;
  }

  outFile << endl;
  outFile << "Work Experience:" << endl;
  for(i=0; i<workQueueSize; i++){
     outFile << workNode->data->getResp() << endl;
     outFile << workNode->data->getDuration() << endl;
     outFile << workNode->data->getStart() << endl;
     outFile << workNode->data->getEnd() << endl;
     workNode = workNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the course pointer in UGradApp to a course in the CourseQueue
void Manager::setCourse(UGradApp* app, string course) {
  CourseQueue::Node* currNode = allCourses->front();
  while (currNode != 0) {
    if (currNode->data->getName() == course) { 
      app->setCourse(currNode->data);
      break;
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the course pointer in GradApp to a course in the CourseQueue
void Manager::setCourse(GradApp* app, string course) {
  CourseQueue::Node* currNode = allCourses->front();
  while (currNode != 0) {
    if (currNode->data->getName() == course) { 
      app->setCourse(currNode->data);
      break;
    }
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the Undergrad pointer to the appropriate Undergrad in allUGradInfo
// But if it is a new Undergrad, set the data members and add to allUGradInfo
void Manager::setUGradInfo(string num, string fn, string sn, string em, 
                             string maj, int yr, float cg, float mgpa) {
  // If this Undergrad is in the queue, set the Undergrad pointer
  if (allUGradInfo->isInQueue(num))
    currUGradApp->setUndergrad(allUGradInfo->isInQueue(num));
  // If this is a new Undergrad, set the data members and add it to the allUGradInfo queue
  else {
    currUGradApp->getUndergrad()->setStuNum(num);
    currUGradApp->getUndergrad()->setFirstName(fn);
    currUGradApp->getUndergrad()->setSurname(sn);
    currUGradApp->getUndergrad()->setEmail(em);
    currUGradApp->getUndergrad()->setMajor(maj);
    currUGradApp->getUndergrad()->setYear(yr);
    currUGradApp->getUndergrad()->setCGPA(cg);
    currUGradApp->getUndergrad()->setMGPA(mgpa);
    allUGradInfo->pushBack(currUGradApp->getUndergrad());
  }
}

//////////////////////////////////////////////////////////////////////////
// Sets the Grad pointer to the appropriate Grad in allGradInfo
// But if it is a new Grad, set the data members and add to allGradInfo
void Manager::setGradInfo(string num, string fn, string sn, string em, 
                             string res, string prog, string sup) {
  // If this Grad is in the queue, set the Grad pointer
  if (allGradInfo->isInQueue(num))
    currGradApp->setGrad(allGradInfo->isInQueue(num));
  // If this is a new Grad, set the data members and add it to the allGradInfo queue
  else {
    currGradApp->getGrad()->setStuNum(num);
    currGradApp->getGrad()->setFirstName(fn);
    currGradApp->getGrad()->setSurname(sn);
    currGradApp->getGrad()->setEmail(em);
    currGradApp->getGrad()->setResearch(res);
    currGradApp->getGrad()->setProgram(prog);
    currGradApp->getGrad()->setSupervisor(sup);
    allGradInfo->pushBack(currGradApp->getGrad());
  }
}

//////////////////////////////////////////////////////////////////////////
// Assemble the application and information queues from existing applications
//   Opens the correct file for each course and reads in the applications
//   from that file. New Application objects are made, its values are set,
//   and they are added to the appropriate AppQueue.
//   This is done for both Undergrad and Grad Applications
void Manager::assembleQueues() {
  int crsQueueSize;
  CourseQueue::Node* currNode;
  string cn, text, t1, t2, t3;
  UGradApp* uApp;
  GradApp* gApp;

  // For each type of application
  // 0 = UGradApp; 1 = GradApp
  for (int gradType=0; gradType<2; gradType++) {
    // Reset variables
    crsQueueSize = allCourses->size();
    currNode = allCourses->front();

    if (gradType == 0)
      cout << endl << endl << "ASSEMBLE UGRADS" << endl;
    else if (gradType == 1)
      cout << endl << endl << "ASSEMBLE GRADS" << endl;

    // For each course
    for (int index=0; index<crsQueueSize; index++) {
      // Get correct file
      if (gradType == 0)
        cn = "./Applications/UndergradApps/" + currNode->data->getName();
      else if (gradType == 1)
        cn = "./Applications/GradApps/" + currNode->data->getName();
      cout << "Looking at file " << currNode->data->getName() << endl;

      // Open file to import information
      ifstream infile3(cn.c_str(), ios::in);
      if (!infile3) {
        if (index < crsQueueSize-1)
          currNode = currNode->next;
        continue;
      }

      // While there is still another line to read in the file
      while (!infile3.eof()) {
        getline(infile3, text);

        // If it's the beginning of a UGrad Application
        if (text == "*NEW UGRAD APPLICATION*") {
          uApp = new UGradApp();
          for (int i=0; i<11; i++) {
            getline(infile3, text);
            switch (i) {
              case 0:  uApp->setAppNum(Tools::stringToInt(text)); break;
              case 1:  setCourse(uApp, text); break;
              case 2:  if (text == "PENDING")       uApp->setStatus(PENDING);
                       else if (text == "ACCEPTED") uApp->setStatus(ACCEPTED);
                       else if (text == "CLOSED")   uApp->setStatus(CLOSED);
                       break;
              case 3:  if (allUGradInfo->isInQueue(text)) {
                         uApp->setUndergrad(allUGradInfo->isInQueue(text));
                         while (i<11) {
                           getline(infile3, text);
                           i++;
                         }
                       }
                       else 
                         uApp->getUndergrad()->setStuNum(text);
                       break;
              case 4:  uApp->getUndergrad()->setFirstName(text); break;
              case 5:  uApp->getUndergrad()->setSurname(text); break;
              case 6:  uApp->getUndergrad()->setEmail(text); break;
              case 7:  uApp->getUndergrad()->setMajor(text); break;
              case 8:  uApp->getUndergrad()->setYear(Tools::stringToInt(text)); break;
              case 9:  uApp->getUndergrad()->setCGPA(Tools::stringToFloat(text)); break;
              case 10: uApp->getUndergrad()->setMGPA(Tools::stringToFloat(text)); 
                       allUGradInfo->pushBack(uApp->getUndergrad()); 
                       break;
            }
          }
          allUGradApps->pushBack(uApp);
          currNode->data->getUGradApps()->pushBack(uApp);
        }

        // If it's the beginning of a Grad Application
        else if (text == "*NEW GRAD APPLICATION*") {
          gApp = new GradApp();
          for (int i=0; i<10; i++) {
            getline(infile3, text);
            switch (i) {
              case 0:  gApp->setAppNum(Tools::stringToInt(text)); break;
              case 1:  setCourse(gApp, text); break;
              case 2:  if (text == "PENDING")       gApp->setStatus(PENDING);
                       else if (text == "ACCEPTED") gApp->setStatus(ACCEPTED);
                       else if (text == "CLOSED")   gApp->setStatus(CLOSED);
                       break;
              case 3:  if (allGradInfo->isInQueue(text)) {
                         gApp->setGrad(allGradInfo->isInQueue(text));
                         while (i<10) {
                           getline(infile3, text);
                           i++;
                         }
                       }
                       else 
                         gApp->getGrad()->setStuNum(text);
                       break;
              case 4:  gApp->getGrad()->setFirstName(text); break;
              case 5:  gApp->getGrad()->setSurname(text); break;
              case 6:  gApp->getGrad()->setEmail(text); break;
              case 7:  gApp->getGrad()->setResearch(text); break;
              case 8:  gApp->getGrad()->setProgram(text); break;
              case 9:  gApp->getGrad()->setSupervisor(text);
                       allGradInfo->pushBack(gApp->getGrad()); 
                       break;
            }
          }
          allGradApps->pushBack(gApp);
          currNode->data->getGradApps()->pushBack(gApp);
        }

        // If we are reading in the related courses (ONLY FOR UGRAD)
        if (text == "Related courses taken:") {
          getline(infile3, text);
          while (text != "") {
            TakenCourse* tknCrs = new TakenCourse(text, this);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            tknCrs->setDataMembers(t1, t2, t3);
            uApp->getTakenCrsQueue()->pushBack(tknCrs);
            getline(infile3, text);
          }
        }

        // If we are reading in the TA'd courses
        if (text == "TA courses taken:") {
          getline(infile3, text);
          while (text != "") {
            TACourse* taCrs = new TACourse(text, this);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            taCrs->setDataMembers(t1, t2, t3);
            if (gradType == 0)
              uApp->getTACrsQueue()->pushBack(taCrs);
            else
              gApp->getTACrsQueue()->pushBack(taCrs);
            getline(infile3, text);
          }
        }
    
        // If we are reading in the work experiences
        else if (text == "Work Experience:") {
          getline(infile3, text);
          while (text != "") {
            WorkExp* wrkExp = new WorkExp(text, this);
            getline(infile3, t1);
            getline(infile3, t2);
            getline(infile3, t3);
            wrkExp->setDataMembers(t1, t2, t3);
            if (gradType == 0)
              uApp->getWorkExpQueue()->pushBack(wrkExp);
            else
              gApp->getWorkExpQueue()->pushBack(wrkExp);
            getline(infile3, text);
          }
        }
      } 
      currNode = currNode->next;
    }
  }
}

