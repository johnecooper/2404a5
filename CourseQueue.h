//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#ifndef COURSEQUEUE_H
#define COURSEQUEUE_H

#include "Types.h"
#include "Course.h"

template <class T> class CourseQueue {

  

  public:
    template <class T> class Node {
    public:
      T* data;
      Node*   next;
    };
    template <class T> CourseQueue<T>::CourseQueue() 
    : head(0)
    { 
      //cout << "CONSTRUCT CourseQueue" << endl;
    }

    template <class T> CourseQueue<T>::CourseQueue(CourseQueue& oldQueue)
    : head(0)
    {
      Node  *currNode = oldQueue.head,
            *prevNode = 0;
      while (currNode != 0){
        Node* newNode = new Node;
        newNode->data = currNode->data;
        newNode->next = 0;

        if (!head) {
          head     = newNode;
          prevNode = head;
        } else {
            prevNode->next = newNode;
            prevNode       = newNode;
        }
        currNode = currNode->next;
      }
      //cout << "COPY CONSTRUCT CourseQueue" << endl;
    }

    template <class T> CourseQueue<T>::~CourseQueue() {
      //cout << "DESTRUCT CourseQueue" << endl;
    }

    template <class T> void  CourseQueue<T>::pushBack(T* newCourse){
      Node* tmpNode = new Node;
      tmpNode->data = newCourse;
      tmpNode->next = 0;
      Node *currNode = head;

      // Adding to an empty list
      if (head == 0){
        head = tmpNode;
        return;
      }
      // Iterate all the way to the end of the linked list
      while(currNode != 0){
         if(currNode->next == 0)
            break;
         currNode = currNode->next;
      }

      currNode->next = tmpNode;
    }

    template <class T> bool  CourseQueue<T>::popFront(){
      Node *currNode; 

      if(head == 0)
        return 1;

      currNode = head;
      head = currNode->next;
      delete currNode;

      return 0;
    }

    template <class T> Node* CourseQueue<T>::front(){
        return head;
      }

    template <class T> bool  CourseQueue<T>::remove(string crs){
      Node* currNode = head;
      Node* prevNode = 0;

      if (currNode == 0) { // empty list
        cout << "The queue is empty" << endl;
        return false;
      }

      while (currNode->next != 0) {
        if (currNode->data->getName() == crs) { // match found
          if (prevNode == 0)  // First element
            head = currNode->next;
          else               // Middle element
            prevNode->next = currNode->next;
          delete currNode->data;
          delete currNode;
          return true;
        }
        prevNode = currNode;
        currNode = currNode->next;
      }

    // Last element
      if (currNode->data->getName() == crs) {
        if (prevNode == 0)
          head = 0;
        else
          prevNode->next = 0;
        delete currNode->data;
        delete currNode;
        return true;
      }

    // crs is not in list
      return false;
    }

    template <class T> bool  CourseQueue<T>::empty(){
      if (head == 0)
        return true;
      return false;
    }

    template <class T> void  CourseQueue<T>::clear(){
      Node *currNode, *nextNode;

      if (head == 0)
        return;

      currNode = head;

      while (currNode != 0) {
        nextNode = currNode->next;
        delete currNode->data;
        delete currNode;
        currNode = nextNode;
      }

      head = 0;
    }

    template <class T> void  CourseQueue<T>::clearCopy(){
      Node *currNode, *nextNode;

      if (head == 0)
        return;

      currNode = head;

      while (currNode != 0) {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
      }
      head = 0;
    }

    template <class T> int   CourseQueue<T>::size()  const{
      Node* currNode = head;
      int   count = 0; 

      while (currNode != 0) {
        count++;
        currNode = currNode->next;
      }
      return count;
    }

    template <class T> void  CourseQueue<T>::print() const{
    }

    template <class T> T* CourseQueue<T>::operator[](int i) const {
      int  count     = 0;
      Node *currNode = head;

      while(currNode != 0){
        if (count == i)
          return currNode->data;
    
        currNode = currNode->next;
        count++;
      }
      return 0;
    }

    template <class T> CourseQueue& CourseQueue<T>::operator+=(T* crs){
      pushBack(crs);
      return *this;
    }
 
    template <class T> CourseQueue& CourseQueue<T>::operator+=(CourseQueue&){
      Node *currNode = crsQueue.head;

      while (currNode != 0) {
        (*this) += currNode->data;
        currNode = currNode->next;
      }
  
      return *this;
    }

    template <class T> CourseQueue  CourseQueue<T>::operator+ (T* crs){
      CourseQueue newQueue = *this;
      newQueue += crs;

      return newQueue;
    }

    template <class T> CourseQueue  CourseQueue<T>::operator+ (CourseQueue&);
    template <class T> CourseQueue& CourseQueue<T>::operator-=(T*);
    template <class T> CourseQueue& CourseQueue<T>::operator-=(CourseQueue&);
    template <class T> CourseQueue  CourseQueue<T>::operator- (T*);
    template <class T> CourseQueue  CourseQueue<T>::operator- (CourseQueue&);
    template <class T> void         CourseQueue<T>::operator!();
    Node* head;
};

#endif

