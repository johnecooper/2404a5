//////////////////////////////////////////////////////////////////////////
// WORKEXP CLASS
// Contains all of the attributes and functions of a work experience

#include "Types.h"
#include "WorkExp.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
WorkExp::WorkExp(string r, Manager* aManager) {
  manager = aManager;
  setResp(r);
  //cout << "CONSTRUCT WorkExp for " << r << endl;
}

WorkExp::WorkExp(Manager* aManager) {
  manager = aManager;
  //cout << "CONSTRUCT WorkExp" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
WorkExp::~WorkExp() {
  cout << "DESTRUCT WorkExp" << endl;
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


