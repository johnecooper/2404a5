/////////////////////////////////////////////////////////////////////////
// COURSE CLASS
// Contains all of the attributes and functions of a course

#ifndef COURSE_H
#define COURSE_H

#include "UGradAppQueue.h"
#include "GradAppQueue.h"

class Course {
  public:
    Course(string="");
    ~Course();

    string  getName();

    void           setName(string);
    UGradAppQueue* getUGradApps();
    GradAppQueue*  getGradApps();

  private:
    string         name;
    UGradAppQueue* UGradApps;
    GradAppQueue*  GradApps;
};

#endif
