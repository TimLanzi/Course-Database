#include <iomanip>
#include "course.h"

//constructor for course in database
Course::Course(string id, string title, double hr)
{
    courseID = id;
    courseTitle = title;
    creditHr = hr;
    prereq = NULL;
}

//copy constructor
Course::Course (const Course &course): courseID(course.courseID), courseTitle(course.courseTitle), creditHr(course.creditHr)
{
    prereq = NULL;
    //copy course prereqs from course
    for(node<string>* p = course.prereq; p!=NULL; p=p->next)
    {
        addPrereq(p->value);
    }
}

//set course ID
void Course::setID(string id)
{
    courseID = id;
}

//set course title
void Course::setTitle(string title)
{
    courseTitle = title;
}

//set course credit hours
void Course::setCreditHours(double hr)
{
    creditHr = hr;
}

//add prereq to course
void Course::addPrereq(string pre)
{
    AddNode<string>(prereq, pre);
}

//overloaded << operator
ostream &operator << (ostream &strm, const Course &obj)
{
    strm << obj.getID() << "," << obj.getTitle() << "," << obj.getCreditHours();
    for(node<string>* p = obj.prereq; p!=NULL; p=p->next)
    {
        strm << "," << p->value;
    }

    return strm;
}

//remove prereq from course
void Course::removePrereq(const string &pre)
{
    DeleteNode<string>(prereq, pre);
}

//determines if a course is prereq for other courses
bool Course::isPrereq(const string &course)
{
	for(node<string>* p = prereq; p!=NULL; p=p->next)
    {
        if(course== p->value)
        {
			       return true;	//returns true if course is prereq
		    }
    }
    return false;	//returns false if course is not prereq
}

//formatted print function for all course information
void Course::print()
{
	cout <<left << setw(10) << courseID << setw(53) << courseTitle << showpoint
	<< setprecision(2) << setw(3) << creditHr <<right << " Hr   Prereq(s):  ";
	for(node<string>* p = prereq; p!=NULL; p=p->next)
    {
        cout << setw(10) << p->value;
    }
    cout <<endl;
}
