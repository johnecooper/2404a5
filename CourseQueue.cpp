//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
CourseQueue::CourseQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT CourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
CourseQueue::CourseQueue(CourseQueue& oldQueue)
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

//////////////////////////////////////////////////////////////////////////
// Destructor
CourseQueue::~CourseQueue() {
  clear();
  //cout << "DESTRUCT CourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
void CourseQueue::pushBack(Course* newCourse) {
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

//////////////////////////////////////////////////////////////////////////
// Removes first item in the queue
bool CourseQueue::popFront() {
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
CourseQueue::Node* CourseQueue::front(){
  return head;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool CourseQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void CourseQueue::clear(){
  Node *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
    delete currNode->data->getUGradApps();
    delete currNode->data->getGradApps();
    delete currNode->data;
    delete currNode;
    currNode = nextNode;
  }

  head = 0;
}

//////////////////////////////////////////////////////////////////////////
// Returns the size of the queue
int CourseQueue::size() const {
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
void CourseQueue::print() const {
  Node* currNode = head;

  cout << endl << endl << "ALL COURSES:" <<endl;
  while (currNode != 0) {
    cout << "  " << currNode->data->getName() << endl;
    currNode = currNode->next;
  }
}
