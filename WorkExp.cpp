//////////////////////////////////////////////////////////////////////////
// WORKEXP CLASS
// Contains all of the attributes and functions of a work experience

#include "Types.h"
#include "WorkExp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
WorkExp::WorkExp(Manager* aManager,string r) {
  manager = aManager;
  setResp(r);
  //cout << "CONSTRUCT WorkExp for " << r << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
WorkExp::~WorkExp() {
  //cout << "DESTRUCT WorkExp" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string  WorkExp::getResp()         { return resp;     }
string  WorkExp::getDuration()     { return duration; }
string  WorkExp::getStart()        { return start;    }
string  WorkExp::getEnd()          { return end;      }

//////////////////////////////////////////////////////////////////////////
// Set functions
void WorkExp::setResp(string r)         { resp = r;       }

void WorkExp::setDataMembers(string dur, string s, string e) {
  duration = dur;
  start = s;
  end = e;
}

//////////////////////////////////////////////////////////////////////////
// Print function
string WorkExp::print() { 
  string out = "Responsibility: " + getResp() + "\n" +
               "     Duration: " + getDuration() + "\n" +
               "     Start: " + getStart() + "\n" +
               "     End: " + getEnd() + "\n";

  return out;
}
