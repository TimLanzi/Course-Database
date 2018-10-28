#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include "course.h"
#include "inputFunctions.h"

using namespace std;

//define formatted print function
void prettyPrintList(node<Course>* list)
{
	for(node<Course>* c = list; c!= NULL; c=c->next)
	{
		c->value.print();
	}
}

int main(int argc, char **argv)
{
	  //define all linked lists
    node<Course> *courseData=NULL;
    node<Course> *searchList;
    node<Course> *resultsList;

    //define variables
    string line;
    string prereq;
    string id;
    string title;
    string hours;
    string subject;
    size_t endID;
    size_t endTitle;
    size_t beginPrereq;
    size_t endPrereq;
    int choice;
    double cHrs;

    //define vectors for all menus used
    vector<string> mainMenu;
    vector<string> modifyMenu;
    vector<string> searchMenu;
    vector<string> deleteAddMenu;

	  //push main menu options to main menu vector
    mainMenu.push_back("Insert New Course");
    mainMenu.push_back("Modify Existing Course");
    mainMenu.push_back("Delete Existing Course");
    mainMenu.push_back("Retrieve Course Data");
    mainMenu.push_back("Print Course Catalogue");
    mainMenu.push_back("Exit Program");

	  //push modify sub-menu options to modify menu vector
    modifyMenu.push_back("Course Title");
    modifyMenu.push_back("Credit Hours");
    modifyMenu.push_back("Prerequisites");
    modifyMenu.push_back("Cancel");

	  //push search sub-menu options to search menu vector
    searchMenu.push_back("Course ID");
    searchMenu.push_back("Course Title");
    searchMenu.push_back("Subject");
    searchMenu.push_back("Credit Hours");
    searchMenu.push_back("End Search");

	  //push modify sub-sub-menu options to the add/delete menu vector
    deleteAddMenu.push_back("Delete");
    deleteAddMenu.push_back("Add");
    deleteAddMenu.push_back("Cancel");

	  //define input data stream
    ifstream dataIn;

    //read in data from courseData.dat file
    if(argc > 1)
    {
        dataIn.open(argv[1]);
    }
    else
    {
        dataIn.open("courseData.dat");
    }

	  //check for file open error
    if(!dataIn.is_open())
    {
        cout << "File open error!"<<endl;
        return -1;
    }

  	//read in data to linked list nodes
    //commas are separator tokens
    while (dataIn.good())
    {
        getline(dataIn, line);		//read entire line from data file into the line variable

        //find and set course id
        endID = line.find(",");
        if(endID == string::npos)
        {
            break;
        }
        id = line.substr(0, (endID));

        //find and set sourse title
        endTitle = line.find(",", (endID+1));
        if(endTitle == string::npos)
        {
            break;
        }
        title = line.substr((endID+1), (endTitle-endID-1));

        //find and set credit hours (beginPrereq can also be considered endHours)
        beginPrereq = line.find(",", (endTitle+1));
        //if no comma is found hours is set to whatever is left in the line
        if(beginPrereq == string::npos)
        {
            hours = line.substr((endTitle+1), string::npos);
        }
        //otherwise hours is set as the previous values have been set
        else
        {
            hours = line.substr((endTitle+1), (beginPrereq-endTitle-1));
        }

		    //create new course using values previously found
        Course newCourse(id, title, atof(hours.c_str()));

		    //read in the prereqs of the course if there are any
        while (beginPrereq != string::npos)
        {
            endPrereq = line.find(",", (beginPrereq+1));
            //if no comma is found, set current prereq to whatever is left in the line
            if(endPrereq == string::npos)
            {
                prereq = line.substr((beginPrereq+1), string::npos);
            }
            //otherwise, continue normally
            else
            {
                prereq = line.substr((beginPrereq+1), (endPrereq-beginPrereq-1));
            }

            beginPrereq = endPrereq;	//iterate prereq starting point
            newCourse.addPrereq(prereq);	//add prereq to the current new course
        }

        //add new course to course database
        AddNode(courseData, newCourse);

    }

	  //close input file
    dataIn.close();

	  //begin menu functionality
    do
    {
		    //prompt user for input
        cout << "What would you like to do with the list? Please enter the number of the option you would like to implement..."<<endl;
        choice = FetchMenuOption(mainMenu);		//FetchMenuOption reads the options, takes user input, and sets choice to that input

    		//main menu as a switch
        switch(choice)
        {
    		    //insert course
            case 1:
            {
    			      //FetchCourseID asks user for name of course and checks for validity
                id=FetchCourseID();

                //check to see if ID exists
                bool alreadyHaveClass =false;
                for(node<Course>* curr =courseData; curr!=NULL; curr=curr->next)
                {
                    if (curr->value.getID() == id)
                    {
                        alreadyHaveClass = true;
                    }
                }

                //if the class exists, an error is reported and the class
                //is not inserted
                if(alreadyHaveClass)
                {
                    cout << "This class already exists" <<endl;
                    break;
                }

                //if the course ID does not exist, continue with adding course information
                title = FetchCourseTitle();
                cHrs = FetchCourseHrs();
                Course newCourse(id,title,cHrs);	//new data added to new course

    			      //set Yes/No prompt to prompt varible to be passed to FetchYesNo function
                string prompt("Does this course have prerequisites?");

                //while the answer is yes, continue adding prereqs
                while(FetchYesNo(prompt))
                {
                    prereq = FetchCourseID();
                    newCourse.addPrereq(prereq);
                    prompt= "Are there any other prerequisites?";	//continue prompting for multiple prereqs
                }
                InsertNode(courseData, newCourse);	//finalizes insertion of new course
            }
            break;

    		    //modify course
            case 2:
            {
    			      //prompts user for the name of the desired course
                cout << "Enter the ID of the course you would like to modify" <<endl;
                id = FetchCourseID();
                node<Course>* modNode = SearchNode(courseData, id);		//searches linked list for desired course
                string prompt;		//declares prompt variable for Yes/No questions

                //continues prompting for more changes until user is done
                do
                {
                    cout << "What aspect would you like to change?"<<endl;
                    choice = FetchMenuOption(modifyMenu);		//displays menu for modifications and takes user input

    				        //modify menu as switch
                    switch (choice)
                    {
        				        //change course title
                        case 1:
                            title = FetchCourseTitle();		//fetches current course title
                            prompt = "Are you sure you want to update course information?";		//prompt for verification

                            //if user decides not to update information, break out of switch statement
                            if(!FetchYesNo(prompt))
                            {
                              break;
                            }
                            modNode->value.setTitle(title);		//update information
                            break;

                        //change credit hours
                        case 2:
                            cHrs = FetchCourseHrs();	//fetches current credit hours
                            prompt = "Are you sure you want to update course information?";	//prompt for verification

                            //if user decides not to update information, break out of switch statement
                            if(!FetchYesNo(prompt))
                            {
                  						break;
                  					}
                            modNode->value.setCreditHours(cHrs);	//update information
                            break;

                        case 3:
                            cout<< "Would you like to delete or add a prerequisite?"<<endl;
                            choice = FetchMenuOption(deleteAddMenu);	//displays menu for prereq modifications and takes user input

        					          //delete prereq
                            if (choice == 1)
                            {
                                cout <<"Which prerequisite would you like to delete?"<<endl;
                                prereq = FetchCourseID();	//fetches course ID of desired prereq
                                prompt = "Are you sure you want to update course information?";		//prompt for verification

                                //if user decides not to update information, break out of switch statement
                    						if(!FetchYesNo(prompt))
                    						{
                    							break;
                    						}
                                modNode -> value.removePrereq(prereq);	//update information
                            }
                            //add prereq
                            else if (choice ==2)
                            {
                                cout << "Enter new prerequisite..." <<endl;
                                prereq = FetchCourseID();	//fetches course ID of desired prereq
                                prompt = "Are you sure you want to update course information?";		//prompt for verification

                                //if user decides not to update information, break out of switch statement
                    						if(!FetchYesNo(prompt))
                    						{
                    							break;
                    						}
                                modNode -> value.addPrereq(prereq);		//update information
                            }
                            //cancel prereq modification
                            else if (choice == 3)
                            {
                                break;
                            }
                            break;

                        //cancel modification
                        case 4:
                            break;
                    }
                    prompt="Any other changes?";	//prompts user for any other changes
                } while(FetchYesNo(prompt));	//while condition is user answers yes
            }
            break;

    		    //delete course
            case 3:
            {
                cout << "Which course would you like to delete?" <<endl;
                id = FetchCourseID();	//fetches course ID of desired course
                string prompt("Are you sure you want to delete this course?");		//prompt user for verification

                //if user answers yes
                if (FetchYesNo(prompt))
                {
                    DeleteNode(courseData, id);		//delete node for course

                    //remove course from records if it was a prereq to other courses
                    for(node<Course>*c = courseData; c!=NULL; c=c->next)
                    {
                        c->value.removePrereq(id);
                    }
                }
                //if user answers no cancel delete function
                else
                {
                    cout << "Cancelling delete function."<<endl;
                }
            }
            break;

            //retrieve course info
            case 4:
            {
    			      //declare new lists for narrowing search
                searchList = courseData;
                resultsList = NULL;
                cout << "How would you like to retrieve course info?"<<endl;
                while(true)
                {
                    choice = FetchMenuOption(searchMenu);		//displays menu options for the search menu and takes user input

    				        //if user doesn't want to search, break out of loop
                    if(choice == 5)
                    {
                        break;
                    }

    				        //search menu as switch
                    switch(choice)
                    {
        				        //search by course ID
                        case 1:
                            id = FetchCourseID();	//asks user for course ID

        					          //searches linked list for match
                            for(node<Course>* curr =searchList; curr!=NULL; curr=curr->next)
                            {
        						            //if course ID matches an ID in the list
                                //or is a prereq to another course, add this
                                //course to results list
                                if (curr->value.getID() == id || curr->value.isPrereq(id))
                                {
                                    AddNode(resultsList, curr->value);
                                }
                            }
                            break;

        				        //search by course title
                        case 2:
                            title = FetchCourseTitle();		//asks user for course title

        					          //searches linked list for match
                            for(node<Course>* curr =searchList; curr!=NULL; curr=curr->next)
                            {
        						            //if course title matches a title in the list
                                //or is a segment of a course title in the list,
                                //add this course to results list
                                if (curr->value.getTitle().find(title) !=string::npos)
                                {
                                    AddNode(resultsList, curr->value);
                                }
                            }
                            break;

        				        //search by course subject
                        case 3:
                            subject = FetchCourseSubject();		//asks user for course subject

        					           //searches linked list for match
                            for(node<Course>* curr =searchList; curr!=NULL; curr=curr->next)
                            {
        						            //if course subject matches a subject in the
                                //list, add this course to results list
                                if (curr->value.getID().find(subject) == 0)
                                {
                                    AddNode(resultsList, curr->value);
                                }
                            }
                            break;

        				        //search by credit hours
                        case 4:
                            cHrs = FetchCourseHrs();	//asks user for number of credit hours

        					          //searches linked list for match
                            for(node<Course>* curr =searchList; curr!=NULL; curr=curr->next)
                            {
        						            //if number of credit hours matches the number
                                //of credit hours of a course in the list,
                                //add this course to results linked list
                                if (curr->value.getCreditHours() == cHrs)
                                {
                                    AddNode(resultsList, curr->value);
                                }
                            }
                            break;
                    }

                    prettyPrintList(resultsList);	//prints out formatted resultsList
                    searchList = resultsList;		//makes the resultsList the list we search from in order to narrow the search
                    resultsList = NULL;				//sets resultsList equal to NULL once again
                    cout << "How would you like to narrow your search?" <<endl;		//asks user how they want to continue searching

                }
            }
            break;

            //prints formatted list of courses
            case 5:
                prettyPrintList(courseData);	//prints out the formatted courseData list
                break;
        }
    } while (choice >=1 && choice <=5);

	  //define output data stream
    ofstream dataOut;
    
    //re-opens the courseData.dat file to overwrite with new data
    if(argc > 1)
    {
        dataOut.open(argv[1]);
    }
    else
    {
        dataOut.open("courseData.dat");
    }

    //reads new course data overtop of old course data
    for(node<Course> *curr = courseData; curr != NULL; curr = curr -> next)
    {
        dataOut << curr->value <<endl;
    }

    dataOut.close();	//close output file
}
