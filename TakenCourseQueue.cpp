//////////////////////////////////////////////////////////////////////////
// TAKEN COURSE QUEUE
// Implements a singly linked list of courses taken by applicant

#include "TakenCourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
TakenCourseQueue::TakenCourseQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT TakenCourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
TakenCourseQueue::TakenCourseQueue(TakenCourseQueue& oldQueue)
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
 //cout << "COPY CONSTRUCT TakenCourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
TakenCourseQueue::~TakenCourseQueue() {
  clear();
  //cout << "DESTRUCT TakenCourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
void TakenCourseQueue::pushBack(TakenCourse* newCourse){
  Node* tmpNode = new Node;
  tmpNode->data = newCourse;
  tmpNode->next = 0;

  Node* currNode;

  // Adding to an empty list
  if (head == 0){
    head = tmpNode;
    return;
  }

  currNode = head;
 
 // Iterate all the way to the end of the linked list
  while(currNode != 0){
    if(currNode->next == 0)
       break;
    currNode = currNode->next;
  }

  currNode->next = tmpNode;
}

//////////////////////////////////////////////////////////////////////////
// Removes first item in the queue
bool TakenCourseQueue::popFront() {
  Node *currNode; 

  if(head == 0)
    return 1;

  currNode = head;
  head = currNode->next;
  delete currNode;

  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Return the first item in the queue
TakenCourseQueue::Node* TakenCourseQueue::front(){
  return head;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool TakenCourseQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void TakenCourseQueue::clear(){
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

//////////////////////////////////////////////////////////////////////////
// Returns the size of the queue
int TakenCourseQueue::size() const {
  Node* currNode = head;
  int   count = 0; 

  while (currNode != 0) {
    count++;
    currNode = currNode->next;
  }
  return count;
}

//////////////////////////////////////////////////////////////////////////
// Prints list of courses to std::cout
void TakenCourseQueue::print() const {
  Node* currNode = head;

  std::cout << "TAKEN COURSES:" <<endl;
  while (currNode != 0) {
    std::cout << "   " << currNode->data->getName() << endl;
    currNode = currNode->next;
  }
}



