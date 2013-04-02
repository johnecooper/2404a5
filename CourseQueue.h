//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#ifndef COURSEQUEUE_H
#define COURSEQUEUE_H

#include "Types.h"
#include "Course.h"

class CourseQueue {
  friend class SelectCrsUI;
  friend class StuAppFormUI;
  friend class GradAppFormUI;
  friend class CourseInfoUI;
  friend class Manager;
  friend class TakenCourse;
  friend class OnePendingUI;
  friend class AllPendingUI;
  friend class TACourse;
  class Node {
    friend class CourseQueue;
    friend class SelectCrsUI;
    friend class StuAppFormUI;
    friend class GradAppFormUI;
    friend class CourseInfoUI;
    friend class Manager;
    friend class TakenCourse;
    friend class OnePendingUI;
    friend class AllPendingUI;
    friend class TACourse;
    private:
      Course* data;
      Node*   next;
  };

  public:
    CourseQueue();
    CourseQueue(CourseQueue&);
    ~CourseQueue();
    void  pushBack(Course*);
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

