//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#ifndef COURSEQUEUE_H
#define COURSEQUEUE_H

#include "Types.h"
#include "Course.h"

template <class T> 
class CourseQueue {
  friend ostream& operator<<(ostream& out, CourseQueue<T>& crsQueue) {
    int index = 0;
    T* ptr = crsQueue[index++];
  
    out << "[";

    while(ptr) {
      out << " " << *ptr;
      ptr = crsQueue[index++];
    }
    out << " ]" << endl;

    return out;
  }

  

  public:
    class Node {
    public:
      T* data;
      Node*   next;
    };
    CourseQueue() 
    : head(0)
    { 
      //cout << "CONSTRUCT CourseQueue" << endl;
    }

    CourseQueue(CourseQueue& oldQueue)
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

    ~CourseQueue() {
      //cout << "DESTRUCT CourseQueue" << endl;
    }

    void pushBack(T* newCourse){
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

    bool popFront(){
      Node *currNode; 

      if(head == 0)
        return 1;

      currNode = head;
      head = currNode->next;
      delete currNode;

      return 0;
    }

    Node* front(){
        return head;
      }

    bool remove(T* crs){
      Node* currNode = head;
      Node* prevNode = 0;

      if (currNode == 0) { // empty list
        cout << "The queue is empty" << endl;
        return false;
      }

      while (currNode->next != 0) {
        if (!(currNode->data != crs)) { // match found
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
      if (!(currNode->data != crs)) {
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

    bool empty(){
      if (head == 0)
        return true;
      return false;
    }

    void clear(){
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

    void clearCopy(){
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

    int size()  const{
      Node* currNode = head;
      int   count = 0; 

      while (currNode != 0) {
        count++;
        currNode = currNode->next;
      }
      return count;
    }

    void print() const{
    }

    T* operator[](int i) const {
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

    CourseQueue& operator+=(T* crs){
      pushBack(crs);
      return *this;
    }
 
    CourseQueue& operator+=(CourseQueue& crsQueue){
      Node *currNode = crsQueue.head;

      while (currNode != 0) {
        (*this) += currNode->data;
        currNode = currNode->next;
      }
  
      return *this;
    }

    CourseQueue operator+ (T* crs){
      CourseQueue newQueue = *this;
      newQueue += crs;

      return newQueue;
    }

    CourseQueue operator+ (CourseQueue& crsQueue){
      CourseQueue newQueue = (*this);
      newQueue += crsQueue;

      return newQueue;
    }

    CourseQueue& operator-=(T* crs){
      remove(crs);
      return *this;
    } 

    CourseQueue& operator-=(CourseQueue& crsQueue){
      Node *currNode = crsQueue.head;
  
      // Finding a crs in empty list
      if (head == 0) {
        cout << "There are no nodes to remove" << endl;
        return *this;
      }

      while (currNode != 0) {
        (*this) -= currNode->data;
        currNode = currNode->next;
      }
  
      return *this;
    }

    CourseQueue operator- (T* crs){
      CourseQueue newQueue;

      Node *currNode = head;

      while (currNode != 0) {
        if (currNode->data != crs)
          newQueue += currNode-> data;
        currNode = currNode->next;
      }

      return newQueue;
    }
    
    CourseQueue operator- (CourseQueue& crsQueue){
      CourseQueue newQueue;

      bool same = false;

      Node *currNode = head,  *crsNode  = crsQueue.head;
      while (currNode !=0) { 
        crsNode = crsQueue.head;
        same = false; 
        while(crsNode != 0){
          if (!(crsNode->data != currNode->data)) {
             same = true; 
             break;   
          }
          crsNode = crsNode->next; 
        }
        if (same == false)
           newQueue += currNode-> data;
        currNode = currNode->next;
      }

      return newQueue; 
    }
    
    void operator!(){
      clear();
    }
    Node* head;
};

#endif

