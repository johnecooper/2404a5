//////////////////////////////////////////////////////////////////////////
// TAKEN COURSE QUEUE
// Implements a singly linked list of courses taken by applicant

#ifndef TAKENCOURSEQUEUE_H
#define TAKENCOURSEQUEUE_H

#include "Types.h"
#include "TakenCourse.h"

class TakenCourseQueue {
  friend class Manager;
  class Node{
    friend class TakenCourseQueue;
    private:
      friend class Manager;
      TakenCourse* data;
      Node*   next;
  };

  public:
    TakenCourseQueue();
    TakenCourseQueue(TakenCourseQueue&);
    ~TakenCourseQueue();

    void  pushBack(TakenCourse*);
    bool  popFront();
    Node* front();
    bool  empty();
    void  clear();
    int   size()  const;
    void  print() const;
    
  private:
    Node* head;
   
};

#endif

