//////////////////////////////////////////////////////////////////////////
// UNDERGRADUATE CLASS
// Contains all the attributes and functions of an undergraduate students's information 

#ifndef UNDERGRADUATE_H
#define UNDERGRADUATE_H

#include "GenInfo.h"

class Undergraduate : public GenInfo {
  public:
    Undergraduate(string="000000000",string="",string="",string="",
		        string="",int=0,float=0.0,float=0.0);
   ~Undergraduate();

   string getMajor();
   int    getYear();
   float  getCGPA();
   float  getMGPA();

   void   setMajor(string);
   void   setYear(int);
   void   setCGPA(float);
   void   setMGPA(float);


  private:
    string   major;
    int      yearStanding;
    float    cgpa;
    float    majorGPA;
};

#endif
