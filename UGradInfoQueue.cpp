//////////////////////////////////////////////////////////////////////////
// UGRADINFO QUEUE
// Implements a singly linked list of all Undergraduates

#include "UGradInfoQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
UGradInfoQueue::UGradInfoQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT UGradInfoQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
UGradInfoQueue::UGradInfoQueue(UGradInfoQueue& oldQueue)
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
  //cout << "COPY CONSTRUCT UGradInfoQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
UGradInfoQueue::~UGradInfoQueue() {
  clear();
  //cout << "DESTRUCT UGradInfoQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// If the item is not in the queue, it is added to the back
void UGradInfoQueue::pushBack(Undergraduate* newUndergrad) {
  Node* tmpNode = new Node;
  tmpNode->data = newUndergrad;
  tmpNode->next = 0;

  Node *currNode = head;

  // Adding to an empty list
  if (head == 0){
    head = tmpNode;
    cout << "Added " << tmpNode->data->getStuNum() << " to UGradInfoQueue" << endl;
    return;
  }
  // Iterate all the way to the end of the linked list
  while(currNode != 0){
    if(currNode->next == 0)
      break;

    currNode = currNode->next;
  }

  currNode->next = tmpNode;
  cout << "Added " << tmpNode->data->getStuNum() << " to UGradInfoQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Removes first item in the queue
bool UGradInfoQueue::popFront() {
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
UGradInfoQueue::Node* UGradInfoQueue::front(){
  return head;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool UGradInfoQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void UGradInfoQueue::clear(){
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
int UGradInfoQueue::size() const {
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
void UGradInfoQueue::print() const {
  Node* currNode = head;

  cout << endl << endl << "ALL UNDERGRADS:" <<endl;
  
  if (currNode == 0) {
    cout << "  There are no undergraduates" << endl;
    return;
  }

  while (currNode != 0) {
    cout << "  " << currNode->data->getFirstName() << " " 
                 << currNode->data->getSurname() << ", #" 
                 << currNode->data->getStuNum() << endl;
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Checks if given student number is in the queue
// Returns a pointer to the GenInfo data if it is in queue
// Otherwise, returns 0
Undergraduate* UGradInfoQueue::isInQueue(string n) const{
  Node* currNode =  head;

  if (currNode == 0)
    return 0;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getStuNum() == n) {
      cout << currNode->data->getStuNum() << " is in UGradInfoQueue" << endl;
      return currNode->data;
    }
    currNode = currNode->next;
  }

  return 0;
}
