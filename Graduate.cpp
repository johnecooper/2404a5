//////////////////////////////////////////////////////////////////////////
// GRADUATE CLASS
// Contains all the attributes and functions of a graduate student's information 

#include "Types.h"
#include "Graduate.h"

//////////////////////////////////////////////////////////////////////////
// Default Constructor
Graduate::Graduate(string num, string fn, string sn, string em,
                   string ra, string prg, string sup) 
     : GenInfo(num, fn, sn, em), researchArea(ra), program(prg), supervisor(sup)
{
  //cout << "CONSTRUCT Graduate" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Graduate::~Graduate() {
  cout << "DESTRUCT Graduate StuNum #" << getStuNum() << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string Graduate::getResearch()    { return researchArea; }
string Graduate::getProgram()     { return program;      }
string Graduate::getSupervisor()  { return supervisor;   }


//////////////////////////////////////////////////////////////////////////
// Set functions
void Graduate::setResearch(string ra)    { researchArea  = ra;  }
void Graduate::setProgram(string prg)    { program       = prg; }
void Graduate::setSupervisor(string sup) { supervisor    = sup; }
