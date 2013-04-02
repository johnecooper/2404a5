//////////////////////////////////////////////////////////////////////////
// TACOURSE CLASS
// Contains all of the attributes and functions of a TA'd course

#include "Types.h"
#include "TACourse.h"
#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
TACourse::TACourse(string n, Manager* aManager) {
  manager = aManager;
  setCourse(n);
  //cout << "CONSTRUCT TACourse for " << n << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
TACourse::~TACourse() {
  //cout << "DESTRUCT TACourse" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string  TACourse::getTerm()       { return term;       }
string  TACourse::getYear()       { return year;       }
string  TACourse::getSupervisor() { return supervisor; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void TACourse::setCourse(string crs) {
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();
  while (currNode != 0) {
    if (currNode->data->getName() == crs) { 
      setName(currNode->data->getName());
      break;
    }
    currNode = currNode->next;
  }
}

void TACourse::setDataMembers(string tr, string yr, string sup){
  term       = tr;
  year       = yr;
  supervisor = sup;
}
