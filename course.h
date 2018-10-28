//begin guarding header file
#ifndef COURSE_H
#define COURSE_H

#include <ostream>
#include <string>
#include "node.h"

using namespace std;

//define Course class
class Course {

//define public variables/functions
public:
	//constructor prototypes and function prototypes
    Course(string=string(""), string=string(""), double=0.0);
    Course (const Course &course);
    void setID(string);
    void setTitle(string);
    void setCreditHours(double);
    void addPrereq(string);
    void print();
    void removePrereq(const string&);
    bool isPrereq(const string&);

	  //prototype for overloaded << operator
    friend ostream &operator<< (ostream &strm, const Course &obj);

	  //overloaded < operator
    friend bool operator< (const Course &l, const Course &r)
    {
        return l.courseID < r.courseID;
    }

	  //first overloaded == operator
    friend bool operator== (const Course &l, const Course &r)
    {
        return l.courseID == r.courseID;
    }

	  //second overloaded == operator
    friend bool operator== (const Course &l, const string &r)
    {
        return l.courseID == r;
    }

	  //getID function
    string getID () const
    {
        return courseID;
    }

	  //getTitle function
    string getTitle() const
    {
        return courseTitle;
    }

	  //getCreditHours funciton
    double getCreditHours() const
    {
        return creditHr;
    }

//private class variables
private:
    string courseID;
    string courseTitle;
    double creditHr;
    node<string> *prereq;


};

#endif
