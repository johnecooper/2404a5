/////////////////////////////////////////////////////////////////////////
// TAKENCOURSE CLASS
// Contains all of the attributes and functions of a taken course

#ifndef TAKENCOURSE_H
#define TAKENCOURSE_H

#include "Course.h"

class Course;
class Manager;

class TakenCourse : public Course {
  public:
    TakenCourse(string,  Manager*);
    ~TakenCourse();
   
    Manager* manager;

    string  getTerm();
    string  getYear();
    string  getFinalGrade();

    void setDataMembers(string, string, string);
    void setCourse(string);

  private:
    string   term;
    string   year;
    string   finalGrade;
};

#endif
