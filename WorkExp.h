//////////////////////////////////////////////////////////////////////////
// WORKEXP CLASS
// Contains all of the attributes and functions of a work experience

#ifndef WORKEXP_H
#define WORKEXP_H

#include "Types.h"

class Manager;

class WorkExp {
  public:
    WorkExp(string, Manager*);
    WorkExp(Manager*);
    ~WorkExp();
   
    Manager* manager;

    string  getResp();
    string  getDuration();
    string  getStart();
    string  getEnd();

    void setResp(string);
    void setDataMembers(string, string, string);


  private:
    string   resp;
    string   duration;
    string   start;
    string   end;
};

#endif
