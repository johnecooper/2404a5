//////////////////////////////////////////////////////////////////////////
// TOOLS
// Tools used to assist in the code

#ifndef TOOLS_H
#define TOOLS_H

#include "Types.h"
//#include "Queue.h"
#include "CourseQueue.h"

class Tools {
  public:
    Tools();
    ~Tools();
    
    // Conversion functions
    static string floatToString(float);
    static string intToString(int);
    static float  stringToFloat(string);
    static int    stringToInt(string);

    // Error checking functions
    static int  validStuNum(string aStuNum);
    static int  validName(string aName);
    static int  validEmail(string anEmail);
    static int  validNumber(string aNum);
    static int  validGPA(string aGPA);

    //Queue Functions

    //static void sortQueue(Queue *);
  //  static bool isInQueue(Queue *, string);
      //static string isAppNumInQueue(Queue *, int);
    //static void closeOtherApps(Queue *, string, int);
   //static Application* getApp(Queue *, int) const;
};

#endif

