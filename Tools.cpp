//////////////////////////////////////////////////////////////////////////
// TOOLS
// Tools used to assist in the code

#include <locale>  // for isdigit, isalpha, ispunct, char_traits
#include <sstream>
#include <string>

#include "Tools.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
Tools::Tools(){
  //cout << "CONSTRUCT Tools" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
Tools::~Tools() {
  //cout << "DESTRUCT Tools" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Takes a float and returns a string
string Tools::floatToString(float f) {
  stringstream out;
  out << f;
  return out.str();
}

//////////////////////////////////////////////////////////////////////////
// Takes an int and returns a string
string Tools::intToString(int i) {
  stringstream out;
  out << i;
  return out.str();
}

//////////////////////////////////////////////////////////////////////////
// Takes a string and returns a float
float Tools::stringToFloat(string s) {
  istringstream istr(s, istringstream::in);
  float f;
  istr >> f;
  return f;
}

//////////////////////////////////////////////////////////////////////////
// Takes a string and returns an int
int Tools::stringToInt(string s) {
  istringstream istr(s, istringstream::in);
  int i;
  istr >> i;
  return i;
}

//////////////////////////////////////////////////////////////////////////
// Check for valid student number
int Tools::validStuNum(string aStuNum){
  int i=0;
  locale loc;
  string s = "100";

  if (aStuNum.length() != 9 || char_traits<char>::eq(aStuNum[0],'0'))
    return 0;
  if ( aStuNum.compare(0, s.length(), s) != 0)
    return 0;
  for (i=0; i<aStuNum.length(); i++){
    if (!isdigit(aStuNum[i],loc))
      return 0;
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
// Check for valid name
int Tools::validName(string aName){
  int i=0;
  locale loc;

  for (i=0; i<aName.length(); i++){
    if (!isalpha(aName[i],loc))
      return 0;
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
// Check for valid email
int Tools::validEmail(string anEmail){
  int i=0;
  locale loc;

  for (i=0; i<anEmail.length(); i++){
    // (Punctuation and not an underscore or period) or (space)
    if ((ispunct(anEmail[i],loc) && (!char_traits<char>::eq(anEmail[i],'_') && !char_traits<char>::eq(anEmail[i],'.')))
        || isspace(anEmail[i],loc))
      return 0;
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
// Checks for valid number
int Tools::validNumber(string aNum){
  int i=0;
  locale loc;
  
  istringstream is(aNum, istringstream::in);
  float num;
  is >> num;
  if (num < 1.0 || num > 4.0)
    return 0;

  for (i=0; i<aNum.length(); i++){
    if (!isdigit(aNum[i],loc))
      return 0;
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
// Checks for valid GPA
int Tools::validGPA(string aGPA){
  int i=0, hasDecimal=0;
  locale loc;

  for (i=0; i<aGPA.length(); i++){
    if (!isdigit(aGPA[i],loc)){
      // Check for number of decimals
      if (char_traits<char>::eq(aGPA[i],'.')) {
        hasDecimal++;
        if (hasDecimal > 1)
          return 0;
        else
          continue;
      }
      return 0;
    }
  }

  istringstream is(aGPA, istringstream::in);
  float gpa;
  is >> gpa;
  if (gpa < 1.0 || gpa > 12.0)
    return 0;

  return 1;
}

/*
void Tools::sortQueue(Queue * q){

  Node *currNode, *nextNode, *prevNode, *tmpNode;
  UGradApp* temp;

  if (q.head == 0) {
    cout << "There are no nodes to sort" << endl;
    return;
  }
  // If there's only one element in the list
  if (q.head->next == 0)
    return;

  prevNode = 0;
  currNode = q.head;
  nextNode = currNode->next;

  bool swap = true;
  while(swap) {
    swap = false;
    while(currNode !=0 && nextNode !=0){
      if (nextNode->data->getPerson()->geSortField().compare(currNode->data->getPerson()->getSortField())>0) {
        if(prevNode == 0){
          tmpNode = currNode;
          head = nextNode;
          tmpNode->next = nextNode->next;
          nextNode->next = tmpNode;
        }
        else {
          tmpNode = currNode;
          prevNode->next = nextNode;
          tmpNode->next = nextNode->next;
          nextNode->next = tmpNode;
        }
        swap = true;
      }
      prevNode = currNode;
      currNode = nextNode;
      nextNode = nextNode->next;
    }
    prevNode = 0;
    currNode = head;
    nextNode = currNode->next;
  }
}
*/
/*
bool Tools::isInQueue(Queue * q, string s){
  
  Node* currNode =  q.head;

  if (currNode == 0)
    return false;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getPerson()->getStuNum() == n) {
      cout << n << " has an existing application" << endl;
      return true;
    }
    currNode = currNode->next;
  }

  return false;

}
*/
/*
string Tools:: isAppInQueue(Queue * q, int n){
  Node* currNode =  q.head;

  if (currNode == 0)
    return "0";

  // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getAppNum() == n) {
      if(currNode->data->getStatus() == ASSIGNED)
        return "ASSIGNED";
      if(currNode->data->getStatus() == CLOSED)
        return "CLOSED";
      return currNode->data->getPerson()->getStuNum();
    }
    currNode = currNode->next;
  }
  return "0";
}
*/

void Tools::closeOtherApps(Queue * q, string stuNum, int appNum) {
  Node* currNode =  q.head;

  if (currNode == 0)
    return;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getUndergrad()->getStuNum() == stuNum) {
      if( currNode->data->getAppNum() != appNum)
        currNode->data->operator-();
    }
    currNode = currNode->next;
  }
  return;
}






