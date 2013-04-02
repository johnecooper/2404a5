//////////////////////////////////////////////////////////////////////////
// TACOURSEQUEUE
// Implements a singly linked list of courses taken by applicant

#ifndef TACOURSEQUEUE_H
#define TACOURSEQUEUE_H

#include "Types.h"

class TACourse;

class TACourseQueue {
  friend class Manager;
  class Node{
    friend class TACourseQueue;
    friend class Manager;
    private:
      TACourse* data;
      Node*     next;
  };

  public:
    TACourseQueue();
    TACourseQueue(TACourseQueue&);
    ~TACourseQueue();

    void  pushBack(TACourse*);

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
