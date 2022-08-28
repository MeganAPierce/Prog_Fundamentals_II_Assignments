/* 
Name:                   Megan Pierce  
Date:                   04-08-22      
Assignment #:           Project 7: Test Scores
Status:                 Completed
Language:                C++
-------------------------------------------------------------------------
This program asks for input from user (how many students, student names and their three test scores)
and then prints a report sheet in order of best grades.
*/

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Student
{
	string name;
	int testOne;
	int testTwo;
	int testThree;
	float average;

};//end of struct

//function prototypes
void header();
int getInteger(string prompt);
int arraySizer(string prompt);
void fillArray(Student *, int);
void printGrades(Student *, int);
float findAverage(Student *, int);
void bubbleSort(Student *,int);
void makeLetterGrade(Student *, int , char & );
char getCommand(string prompt);
void footer();


int main()
{
	//variable prototypes and initialization
	int arraySize;
	Student* myStudents = nullptr;
	char cmd = 'Y';
	
	//beginning of program run
	header();
	
	while(cmd == 'Y')
	{
		arraySize = arraySizer("How many students do you have? ");	
		myStudents = new Student[arraySize];
		
		fillArray(myStudents, arraySize);
		bubbleSort(myStudents,arraySize);
		printGrades(myStudents, arraySize);
		delete[] myStudents;
		cmd = getCommand("\nRun again? (Y)es or (N)o: ");

	}//end of while
	
	footer();
	
	system("PAUSE");    
    return 0;
}//end of main

//program header
void header()
{
	cout << "----------------------------------------------------" << endl;
	cout << "                    TEST SCORES" << endl;
	cout << "              Written by Megan Pierce" << endl; 
	cout << "----------------------------------------------------" << endl;
}//end of header


//footer function
void footer()
{
	cout << "----------------------------------------------------" << endl;
	cout << " Thank you for using TEST SCORES. Have a nice day." << endl;
	cout << "----------------------------------------------------" << endl;
}//end of footer

//function to flag end of program
char getCommand(string prompt)
{
	char cmd;
	cout << prompt;
	cin >> cmd;
	cmd = toupper(cmd);
	
	if (cmd == 'Y')
	{
		return cmd;
	}//end of if YES, quit
	else if (cmd == 'N')
	{
		return cmd;
	}//end of if NO, continue
	else
	{
		cout << "You can only choose Y for YES or N for NO. Try again." << endl;
	}//end of bad user input

}//end of char getCommand

//function to help determin array sizing
int arraySizer(string prompt)
{
	int value;
	while(true)
	{
		cout << prompt;
		cin >> value;
		
		if (value < 0)
		{
			cin.clear();
			cin.ignore(120,'\n');
			cout << "Error: Number of students can't be negative'. " << endl;
		}//end of if user inputs invalid score
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(120,'\n');
			cout << "Error: Integer values only. " << endl;
		}//end of if user inputs non-integer
		else
		{
			return value;
		}//end of else
	}//end of while true
}//end of arraySizer


//getInteger - LIMITS SET FOR TEST GRADES!
int getInteger(string prompt)
{
	int value;
	
	while(true)
	{
		cout << prompt;
		cin >> value;
		
		if (value < 0 || value > 110)
		{
			cin.clear();
			cin.ignore(120,'\n');
			cout << "Error: Score must be between 0 and 110. " << endl;
		}//end of if user inputs invalid score
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(120,'\n');
			cout << "Error: Integer values only. " << endl;
		}//end of if user inputs non-integer
		else
		{
			return value;
		}//end of else
	}//end of while true
	
}//end of getInteger


//get string function
string getString(string prompt)
{
	string value;
	
	cout << prompt;
	cin.ignore();
	getline(cin, value);
	
	return value;
	
}//end of getString

void fillArray(Student *myStudents, int arraySize)
{
	for(int i = 0; i < arraySize; i++)
	{
		cout << "Student #" << i + 1 << endl;
		myStudents[i].name = getString("Enter student name: ");
		myStudents[i].testOne = getInteger("Enter grade for test 1: ");
		myStudents[i].testTwo = getInteger("Enter grade for test 2: ");
		myStudents[i].testThree = getInteger("Enter grade for test 3: ");
		myStudents[i].average = findAverage(myStudents, i);
		cout << "\n";
	}//end of for
}//end of fillArray



float findAverage(Student *myStudents, int i)
{
	float testAverage;
	
	testAverage = ((myStudents[i].testOne + myStudents[i].testTwo + myStudents[i].testThree) / 3);
	return testAverage;
}//end of findAverage


void printGrades(Student *myStudents, int arraySize)
{
	char letterGrade;
	cout << "----------------------------------------------------" << endl;
	cout << "Student Name:" << setw(18) << "Test Scores:" << setw(20) << "Letter Grade" << endl;
	for(int i = 0; i < arraySize; i++)
	{
		makeLetterGrade(myStudents, i, letterGrade);
		cout << left << setw(20) << myStudents[i].name;
		cout << left << myStudents[i].testOne << "," << left << myStudents[i].testTwo << "," << left << myStudents[i].testThree;
		cout << right << setw(20) << letterGrade << endl;
		cout << "\n";
	}//end of for
	
}//end of printGrades

void makeLetterGrade(Student *myStudents, int i, char & letterGrade)
{
	if (myStudents[i].average >= 90)
	{
		letterGrade = 'A';
	}//end of if A
	else if (myStudents[i].average >= 80 && myStudents[i].average < 90)
	{
		letterGrade = 'B';
	}//end of if B
	else if (myStudents[i].average >= 70 && myStudents[i].average < 80)
	{
		letterGrade = 'C';
	}//end of if C
	else if (myStudents[i].average >= 60 && myStudents[i].average < 70)
	{
		letterGrade = 'D';
	}//end of if D
	else
	{
		letterGrade = 'F';
	}//end of if fail
	
}//end of letterGrade

void bubbleSort(Student *myStudents,int arraySize)
{
	for(int maxElement = arraySize -1; maxElement > 0; maxElement--)
	{
		for (int i = 0; i < maxElement; i++)
		{
			if (myStudents[i].average < myStudents[i+1].average)
			{
				swap (myStudents[i], myStudents[i+1]);
			}//end of if
		}//end of inbedded for
	}//end of for
}//end of bubbleSort

