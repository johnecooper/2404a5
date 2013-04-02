//////////////////////////////////////////////////////////////////////////
// GRADUATE APPLICATION QUEUE
// Implements a singly linked list of all graduate applications

#ifndef GRADAPPQUEUE_H
#define GRADAPPQUEUE_H

#include "GradApp.h"

class GradApp;

class GradAppQueue {
  friend class OnePendingUI;
  friend class AllPendingUI;
  class Node{
    friend class GradAppQueue;
    friend class OnePendingUI;
    friend class AllPendingUI;
    private:
      GradApp* data;
      Node*        next;
  };

  public:
    GradAppQueue();
    GradAppQueue(GradAppQueue&);
    ~GradAppQueue();
    void  pushBack(GradApp*);
    bool  popFront();
    Node* front();
    bool  empty();
    void  clear();
    void  clearCopy();
    int   size()  const;
    void  print() const;
    void  sortByResearch();
    
  private:
    Node* head;
   
};

#endif

