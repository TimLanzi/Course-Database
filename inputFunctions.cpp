#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

using namespace std;

//function for taking a menu vector, having the user enter their choice, and returning
//the value of the menu option
const int FetchMenuOption (vector<string> &options)
{
    int choice;
    string line;

	  //do while choice is invalid
    do
    {
		    //print menu options
        for(int i=0; i<int(options.size()); i++)
        {
            cout << i+1 << " - " << options[i] << endl;
        }

		    //get user choice
        cout << "Please enter your choice" <<endl;
        getline(cin,line);
        choice = atoi(line.c_str());

		    //if user choice is invalid, display error message and prompt user to try again
        if(choice <= 0 || choice > int(options.size()))
        {
            cout << "Not a valid choice... Please enter an option from the menu only..." <<endl;
        }
    } while(choice < 1 || choice > int(options.size()));

    return choice;
}

//function for taking and printing a constant Yes/No question prompt, taking user
//input, and returning either true for yes, or false for no
const bool FetchYesNo(string &prompt)
{
    bool choice;
    bool isValid = false;
    string line;

	  //do while choice is invalid
    do
    {
		    //print prompt and take user's choice
        cout << prompt << " (Y/N)"<<endl;
        getline(cin,line);

		    //if user answers with a non case-sensitive 'y', or a string with that as the first character...
        if (line[0] == 'y' || line[0] == 'Y')
        {
            choice = true;		//set choice to true
            isValid = true;		//set choice validity to true
        }
        //if user answers with a non case-sensitive 'n', or a string with that as the first character...
        else if (line[0] == 'n' || line[0] == 'N')
        {
            choice = false;		//set choice to false
            isValid = true;		//set choice validity to true
        }
        //if user enters an invalid choice display error message and keep choice validity set as false
        else
        {
            cout << "Invalid input... Please input a valid statement..." <<endl;
        }
    } while(!isValid);

    return choice;
}

//function for searching for course ID
//takes user input, checks for valid ID, and either returns ID if valid, or prompts user
//to try again if invalid
string FetchCourseID()
{
    bool isValid = false;
    string line;

	  //do while choice is invalid
    do
    {
		    //prompts user to enter valid course ID
        cout << "Enter a valid course ID"<<endl;
        getline(cin,line);

		    //if the entered course ID is valid set validity to true
        if (line.length()==7 && isalpha(line[0]) && isupper(line[0])
                && isalpha(line[1]) && isupper(line[1])
                && isalpha(line[2]) && isupper(line[2])
                && isalpha(line[3]) && isupper(line[3])
                && isdigit(line[4]) && isdigit(line[5])
                && isdigit(line[6]))
        {
            isValid = true;
        }
		    //otherwise prompt user to try again and keep validity set as false
        else
        {
            cout << "Invalid course ID. Please input a valid course ID." <<endl;
        }
    } while(!isValid);

    return line;
}

//function for searching for course title
//takes user input, checks for valid title, and either returns title if valid, or prompts user
//to try again if invalid
string FetchCourseTitle()
{
    bool isValid = false;
    string line;

	  //do while input is invalid
    do
    {
		    //prompts user to enter valid course title
        cout << "Enter a valid course title"<<endl;
        getline(cin,line);

		    //if length of title is within valid range set validity to true
        if (line.length()>0 &&line.length()<=50)
        {
            isValid = true;
        }
		    //otherwise prompt user to try again and keep validity set as false
        else
        {
            cout << "Course title must be less than 50 characters... Try again..." <<endl;
        }
    } while(!isValid);

    return line;
}

//function for searching for credit hours
//takes user input, checks for valid number of credit hours, and either returns amount entered if valid, or prompts user
//to try again if invalid
int FetchCourseHrs()
{
    bool isValid = false;
    string line;
    int hours;

	  //do while input is invalid
    do
    {
		    //prompts user to enter valid number of credit hours
        cout << "Enter a valid number of credit hours"<<endl;
        getline(cin,line);
        hours=atoi(line.c_str());

		    //if amount of credit hours is within valid range set validity to true
        if (hours>0 && hours<=4)
        {
            isValid = true;
        }
		    //otherwise prompt user to try again and keep validity set as false
        else
        {
            cout << "Credit hours must total less than 4... Try again..." <<endl;
        }
    } while(!isValid);

    return hours;
}

//function for searching for course subject
//takes user input, checks for valid subject, and either returns subject if valid, or prompts user
//to try again if invalid
string FetchCourseSubject()
{
    bool isValid = false;
    string line;

	  //do while input is invalid
    do
    {
    		//prompts user to enter valid subject
    		cout << "Enter a valid course subject"<<endl;
        getline(cin,line);

		    //if the entered subject is valid set validity to true
        if (line.length()==4 && isalpha(line[0]) && isupper(line[0])
                && isalpha(line[1]) && isupper(line[1])
                && isalpha(line[2]) && isupper(line[2])
                && isalpha(line[3]) && isupper(line[3]))
        {
            isValid = true;	
        }
		    //otherwise prompt user to try again and keep validity set as false
        else
        {
            cout << "Invalid subject... Please input a valid course subject..." <<endl;
        }
    } while(!isValid);

    return line;
}
