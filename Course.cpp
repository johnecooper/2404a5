//////////////////////////////////////////////////////////////////////////
// COURSE CLASS
// Contains all of the attributes and functions of a course

#include "Course.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
Course::Course(string n) 
: name(n), UGradApps(new UGradAppQueue()), GradApps(new GradAppQueue())
{
  cout << "CONSTRUCT Course" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Course::~Course() {
  cout << "DESTRUCT Course " << name << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string         Course::getName()      { return name;      }
UGradAppQueue* Course::getUGradApps() { return UGradApps; }
GradAppQueue*  Course::getGradApps()  { return GradApps;  }

//////////////////////////////////////////////////////////////////////////
// Set functions
void Course::setName(string n)    { name = n;       }
