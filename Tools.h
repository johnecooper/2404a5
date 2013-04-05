//////////////////////////////////////////////////////////////////////////
// TOOLS
// Tools used to assist in the code

#ifndef TOOLS_H
#define TOOLS_H

#include "Types.h"
//#include "Queue.h"
#include "CourseQueue.h"
#include "Application.h"

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

    static void sortQueue(CourseQueue<Application> *);
    static bool isInQueue(CourseQueue<Application> *, string);
    static string isAppNumInQueue(CourseQueue<Application> *, int);
    static void closeOtherApps(CourseQueue<Application> *, string, int);
    static Application* getApp(CourseQueue<Application> *, int);
};

#endif

