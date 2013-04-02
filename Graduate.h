//////////////////////////////////////////////////////////////////////////
// GENERFAL INFORMATION CLASS
// Contains all the attributes and functions of a student's information 

#ifndef GRADUATE_H
#define GRADUATE_H

#include "GenInfo.h"

class GenInfo;

class Graduate : public GenInfo {
  public:
    Graduate(string="000000000",string="",string="",string="",
             string="",string="",string="");
   ~Graduate();

   string getResearch();
   string getSupervisor();
   string getProgram();
   
   void   setResearch(string);
   void   setSupervisor(string);
   void   setProgram(string);

  private:
    string researchArea;
    string program;
    string supervisor;
};

#endif
