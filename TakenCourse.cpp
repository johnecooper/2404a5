//////////////////////////////////////////////////////////////////////////
// TAKENCOURSE CLASS
// Contains all of the attributes and functions of a taken course

#include "Types.h"
#include "TakenCourse.h"
#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
TakenCourse::TakenCourse(string n, Manager* aManager) {
  manager = aManager;
  setCourse(n);
  //cout << "CONSTRUCT TakenCourse for " << n << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
TakenCourse::~TakenCourse() {
  //cout << "DESTRUCT TakenCourse" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string  TakenCourse::getTerm()       { return term;       }
string  TakenCourse::getYear()       { return year;       }
string  TakenCourse::getFinalGrade() { return finalGrade; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void TakenCourse::setCourse(string crs) { 
  CourseQueue::Node* currNode = manager->getCourseQueue()->front();
  while (currNode != 0) {
    if (currNode->data->getName() == crs) { 
      setName(currNode->data->getName());
      break;
    }
    currNode = currNode->next;
  }
}

void TakenCourse::setDataMembers(string tr, string yr, string fg){
  term       = tr;
  year       = yr;
  finalGrade = fg;
}
