#include <iostream>
using namespace std;

#include "Course.h"
#include "CourseQueue.h"
#include <fstream>

void testing_not(string[]);
void testing_subscript(string[]);
void testing_plus_equals_ptr(string[]);
void testing_plus_equals_queue(string[]);
void testing_plus_ptr(string[]);
void testing_plus_queue(string[]);
void testing_minus_equals_ptr(string[]);
void testing_minus_equals_queue(string[]);
void testing_minus_ptr(string[]);
void testing_minus_queue(string[]);


int main() {
  string   courses[30];
  int      count=0, i;
  ifstream infile("courses.txt", ios::in);

  if (!infile)
    cout << "Could not open file" << endl;
  while (!infile.eof()) {
    getline(infile, courses[count]);
    count++;
  }

  cout << "********* TEST PROGRAM *********" << endl;

  // Testing the ! 
  testing_not(courses);


  // Testing the [] subscript 
  testing_subscript(courses);


  // Testing the += with course pointer passed in
  testing_plus_equals_ptr(courses);

  // Testing the += with coursequeue passed in
  testing_plus_equals_queue(courses);


  // Testing the + with course pointer passed in
  testing_plus_ptr(courses);

  // Testing the + with coursequeue passed in
  testing_plus_queue(courses);


  // Testing the -= with course pointer passed in
  testing_minus_equals_ptr(courses);

  // Testing the -= with coursequeue passed in
  testing_minus_equals_queue(courses);


  // Testing the - with course pointer passed in
  testing_minus_ptr(courses);

  // Testing the - with course queue passed in
  testing_minus_queue(courses);


  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Tests the ! which empties the queue
void testing_not(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the ! which empties queue -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }

  cout << "Queue: " << queue1; 
  !queue1;
  cout << "Queue after ! : " << queue1 << endl; 
}

//////////////////////////////////////////////////////////////////////////
// Tests the [] which returns the course pointer at index specified
void testing_subscript(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the [] which returns the course pointer at index -----";
  cout << endl << "----- CASE: In bounds index -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }

  cout << "Queue: " << queue1; 
  cout << "Element at position 2  : " << queue1[2]->getName() << endl;
  cout << "Element at position 4  : " << queue1[4]->getName() << endl;


  cout << endl << "----- CASE: Invalid index -----" << endl;
  cout << "Element at position -1  : " << queue1[-1] << endl;

  cout << endl << "----- CASE: Out of bounds index -----" << endl;
  cout << "Element at position 8  : " << queue1[8] << endl << endl;
  
  !queue1;
}


//////////////////////////////////////////////////////////////////////////
// Tests the += with course pointer passed in
void testing_plus_equals_ptr(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the += for a course pointer -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }

  cout << "Queue: " << queue1 << endl; 
  !queue1;
}


//////////////////////////////////////////////////////////////////////////
// Tests the += with course queue passed in
void testing_plus_equals_queue(string courses[]) {
  CourseQueue queue1, queue2;

  cout << endl << "----- Testing the += for a new queue -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i+2]);
    queue1 += newCourse;
    queue2 += newCourse2;
  }

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 += queue2;

  cout << "Queue 1 after adding Queue 2: " << queue1;
  !queue1;
  queue2.clearCopy();

  cout << endl << "----- Testing the += for a new queue *CASCADING* -----" << endl;
  CourseQueue q1, q2, q3;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i+2]);
    Course* newCourse3 = new Course(courses[i+3]);
    q1 += newCourse;
    q2 += newCourse2;
    q3 += newCourse3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;
  
  q1 += q2 += q3;

  cout << "Queue 1 after cascading: " << q1;
  cout << "Queue 2 after cascading: " << q2;
  cout << "Queue 3 after cascading: " << q3 << endl;

  !q1;
  q2.clearCopy();
  q3.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the + with course pointer passed in
void testing_plus_ptr(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the + for a course pointer -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }

  cout << "Original queue: " << queue1; 
  cout << "Adding course: " << courses[7];
  Course* newCourse = new Course(courses[7]);
  CourseQueue newQueue;

  newQueue = queue1 + newCourse;

  cout << endl << "New queue: " << newQueue;

  !newQueue;
  queue1.clearCopy();


  cout << endl << "----- Testing the + for a course pointer *CASCADING* -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }
  cout << "Queue 1: " << queue1; 

  cout << "Adding course: " << courses[7] << ", then adding course: " << courses[6] << endl;
  Course* newCourse2 = new Course(courses[7]);
  Course* newCourse3 = new Course(courses[6]);

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = queue1 + newCourse2 + newCourse3;  
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !newQueue;
  queue1.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the + with course queue passed in
void testing_plus_queue(string courses[]) {
  CourseQueue queue1, queue2;

  cout << endl << "----- Testing the + for a new queue -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i+2]);
    queue1 += newCourse;
    queue2 += newCourse2;
  }

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  CourseQueue newQueue;
  newQueue = queue1 + queue2;

  cout << "New queue: " << newQueue;
  !newQueue;
  queue1.clearCopy();
  queue2.clearCopy();

  cout << endl << "----- Testing the + for a new queue *CASCADING* -----" << endl;
  CourseQueue q1, q2, q3;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i+2]);
    Course* newCourse3 = new Course(courses[i+3]);
    q1 += newCourse;
    q2 += newCourse2;
    q3 += newCourse3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;


  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 + q2 + q3; 
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !newQueue;
  q1.clearCopy();
  q2.clearCopy();
  q3.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the -= with course pointer passed in
void testing_minus_equals_ptr(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the -= for a course pointer -----" << endl;

  cout << "----- EMPTY LIST CASE -----" << endl;

  Course* newCourse = new Course(courses[0]);
  queue1 -= newCourse;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  cout << endl << "----- MIDDLE OF LIST CASE -----" << endl;
  for (int i=0; i<4; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }

  cout << "Queue: " << queue1; 
  cout << "Removing " << courses[2] << endl;
  newCourse = new Course(courses[2]);
  queue1 -= newCourse;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  cout << "Queue after: " << queue1;

  cout << endl << "----- FRONT OF LIST CASE -----" << endl;
  cout << "Removing " << courses[0] << endl;
  newCourse = new Course(courses[0]);
  queue1 -= newCourse;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  cout << "Queue after: " << queue1;

  cout << endl << "----- END OF LIST CASE -----" << endl;
  cout << "Removing " << courses[3] << endl;
  newCourse = new Course(courses[3]);
  queue1 -= newCourse;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  cout << "Queue after: " << queue1;

  cout << endl << "----- LAST ELEMENT OF LIST CASE -----" << endl;

  cout << "Removing " << courses[1] << endl;
  newCourse = new Course(courses[1]);
  queue1 -= newCourse;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  cout << "Queue after: " << queue1 << endl;
}


//////////////////////////////////////////////////////////////////////////
// Tests the -= with course queue passed in
void testing_minus_equals_queue(string courses[]) {
  CourseQueue queue1, queue2;

  cout << endl << "----- Testing the -= for a new queue -----";
  cout << endl << "----- CASE: queue1 and queue2 are the same -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i]);
    queue1 += newCourse;
    queue2 += newCourse2;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue2;


  cout << endl << "----- CASE: all courses in queue2 are found in queue1 -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    queue1 += newCourse;
  }
  for (int i=0; i<5; i+=2) {
    Course* newCourse  = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;
  !queue2;


  cout << endl << "----- CASE: queue2 has courses that aren't in queue1 and aren't in order -----" << endl;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    queue1 += newCourse;
  }
  for (int i=0; i<3; i++) {
    Course* newCourse = new Course(courses[i+4]);
    queue2 += newCourse;
  }
  for (int i=0; i<2; i++) {
    Course* newCourse = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;
  !queue2;


  cout << endl << "----- CASE: queue 2 is empty -----" << endl;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    queue1 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;


  cout << endl << "----- CASE: queue 1 is empty -----" << endl;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue2;


  cout << endl << "----- Testing the -= for a new queue *CASCADING* -----" << endl;
  CourseQueue q1, q2, q3;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2 = new Course(courses[i+2]);
    Course* newCourse3 = new Course(courses[i+3]);
    q1 += newCourse;
    q2 += newCourse2;
    q3 += newCourse3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;
  
  q1 -= q2 -= q3;

  cout << "Queue 1 after cascading: " << q1;
  cout << "Queue 2 after cascading: " << q2;
  cout << "Queue 3 after cascading: " << q3 << endl;

  !q1;
  !q2;
  !q3;
}


//////////////////////////////////////////////////////////////////////////
// Tests the - with course pointer passed in
void testing_minus_ptr(string courses[]) {
  CourseQueue queue1;

  cout << endl << "----- Testing the - for a course pointer -----";
  cout << endl << "----- CASE: empty list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[1] << endl;
  Course* newCourse = new Course(courses[1]);
  CourseQueue newQueue;
  newQueue = queue1 - newCourse;

  cout << "New queue: " << newQueue;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;


  cout << endl << "----- CASE: middle of the list -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse = new Course(courses[i]);
    queue1 += newCourse;
  }
  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[2];
  newCourse = new Course(courses[2]);
  newQueue = queue1 - newCourse;

  cout << endl << "New queue: " << newQueue;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  newQueue.clearCopy();


  cout << endl << "----- CASE: front of the list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[0];
  newCourse = new Course(courses[0]);
  newQueue = queue1 - newCourse;

  cout << endl << "New queue: " << newQueue;
 
  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  newQueue.clearCopy();


  cout << endl << "----- CASE: end of the list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[4];
  newCourse = new Course(courses[4]);
  newQueue = queue1 - newCourse;

  cout << endl << "New queue: " << newQueue;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;
  newQueue.clearCopy();


  cout << endl << "----- CASE: element not in list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[8];
  newCourse = new Course(courses[8]);
  newQueue = queue1 - newCourse;

  cout << endl << "New queue: " << newQueue;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  newQueue.clearCopy();
  

  cout << endl << "----- CASE: last element of the list -----" << endl;

  !queue1;
  newCourse = new Course(courses[0]);
  queue1 += newCourse;

  cout << "Original queue: " << queue1; 
  cout << "Removing course: " << courses[0];
  newCourse = new Course(courses[0]);
  newQueue = queue1 - newCourse;

  cout << endl << "New queue: " << newQueue;

  delete newCourse->getUGradApps();
  delete newCourse->getGradApps();
  delete newCourse;

  newQueue.clearCopy();
  !queue1;


  cout << endl << "----- Testing the - for a course pointer *CASCADING* -----" << endl;
  CourseQueue q1;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    q1 += newCourse;
  }
  
  cout << "Queue 1: " << q1; 

  cout << "Removing course: " << courses[1] << ", then removing course: " << courses[2] << endl;
  Course* newCourse2 = new Course(courses[1]);
  Course* newCourse3 = new Course(courses[2]);

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 - newCourse2 - newCourse3;  
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;
 
  delete newCourse2->getUGradApps();
  delete newCourse2->getGradApps();
  delete newCourse2;
  delete newCourse3->getUGradApps();
  delete newCourse3->getGradApps();
  delete newCourse3;

  !q1;
  newQueue.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the - with course queue passed in
void testing_minus_queue(string courses[]) {
  CourseQueue queue1, queue2;

  cout << endl << "----- Testing the - for a new queue -----";
  cout << endl << "----- CASE: queue1 and queue2 are the same -----" << endl;

  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    Course* newCourse2  = new Course(courses[i]);
    queue1 += newCourse;
    queue2 += newCourse2;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  CourseQueue newQueue;
  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;
  !queue2;


  cout << endl << "----- CASE: all courses in queue2 are found in queue1 -----" << endl;

  for (int i=0; i<5; i+=2) {
    Course* newCourse  = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  !queue2;
  newQueue.clearCopy();


  cout << endl << "----- CASE: queue2 has courses that aren't in queue1 and aren't in order -----" << endl;
  for (int i=0; i<3; i++) {
    Course* newCourse = new Course(courses[i+4]);
    queue2 += newCourse;
  }
  for (int i=0; i<2; i++) {
    Course* newCourse = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  !queue2;
  newQueue.clearCopy();


  cout << endl << "----- CASE: queue 2 is empty -----" << endl;

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  newQueue.clearCopy();


  cout << endl << "----- CASE: queue 1 is empty -----" << endl;
  !queue1;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    queue2 += newCourse;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;
  !queue2;


  cout << endl << "----- Testing the - for a new queue *CASCADING* -----" << endl;
  CourseQueue q1, q2, q3;
  for (int i=0; i<5; i++) {
    Course* newCourse  = new Course(courses[i]);
    q1 += newCourse;
  }
  for (int i=0; i<8; i+=3) {
    Course* newCourse2 = new Course(courses[i]);
    q2 += newCourse2;
  }
  for (int i=0; i<10; i+=2) {
    Course* newCourse3 = new Course(courses[i]);
    q3 += newCourse3;
  }
  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 - q2 - q3;   
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !q1;
  !q2;
  !q3;
  newQueue.clearCopy();
}
