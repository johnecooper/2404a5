/////////////////////////////////////////////////////////////////////////
// UNDERGRAD APPLICATION CLASS
// Contains all of the attributes and functions of an undergraduate's application

#ifndef UGRADAPP_H
#define UGRADAPP_H

#include "Application.h"
#include "Undergraduate.h"
#include "TakenCourse.h"
#include "TakenCourseQueue.h"

class TakenCourseQueue;

class UGradApp : public Application {
  public:
    UGradApp();
    ~UGradApp();

    Undergraduate*     getUndergrad()     const;
    TakenCourseQueue*  getTakenCrsQueue() const;

    void   setUndergrad(Undergraduate*); 
    void   setTakenCrsQueue(TakenCourseQueue*);
    void   print() const;

  private:
    Undergraduate*    undergrad;

    // Linked lists
    TakenCourseQueue* takenCrsQueue;  
};

#endif
