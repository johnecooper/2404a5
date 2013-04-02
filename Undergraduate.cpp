//////////////////////////////////////////////////////////////////////////
// UNDERGRADUATE CLASS
// Contains all the attributes and functions of an undergraduate student's information 

#include "Types.h"
#include "Undergraduate.h"

//////////////////////////////////////////////////////////////////////////
// Default Constructor
Undergraduate::Undergraduate(string num, string fn, string sn, string em, 
                             string maj, int yr, float cg, float mgpa) 
  : GenInfo(num, fn, sn, em), major(maj), yearStanding(yr), cgpa(cg), majorGPA(mgpa)
{
  //cout << "CONSTRUCT Undegraduate" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Undergraduate::~Undergraduate() {
  cout << "DESTRUCT Undegraduate StuNum #" << getStuNum() << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string Undergraduate::getMajor()    { return major; }
int    Undergraduate::getYear()     { return yearStanding; }
float  Undergraduate::getCGPA()     { return cgpa; }
float  Undergraduate::getMGPA()     { return majorGPA; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void Undergraduate::setMajor(string maj)    { major        = maj; }
void Undergraduate::setYear(int yr)         { yearStanding = yr;  }
void Undergraduate::setCGPA(float cgp)      { cgpa         = cgp; }
void Undergraduate::setMGPA(float mgp)      { majorGPA     = mgp; }


