/* 			
Name:                Megan Pierce     
Date:                Apr 18 2022
Assignment #:        Project 9: Payroll V2.0
Status:              Completed
Language:            C++
-------------------------------------------------------------------------

*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Employee
{
 	private:
 		int id; // employee ID
 		char* name; // employee name
 		double hourlyPay; // pay per hour
 		int numDeps; // number of dependents
 		int type; // employee type

 	public:
		Employee( int initId=0, char initName[] = nullptr, double initHourlyPay=0.0,int initNumDeps=0, int initType=0 ); // Constructor
		bool set(int newId, char newName[], double newHourlyPay,int newNumDeps, int newType);
		int getID();
		void setID(int value);
		void setHourly(float value);
		float getHourly();
		void setDeps(int value);
		int getDeps();
		void setType(int value);
		int getType();
		void setName(char value[]);
		char* getName();
};

Employee::Employee(int initId, char initName[], double initHourlyPay,int initNumDeps, int initType )
{
 	bool status = set( initId, initName, initHourlyPay,initNumDeps, initType );
	if ( !status )
	{
		id = 0;
		name = new char[25];
		hourlyPay = 0.0;
		numDeps = 0;
		type = 0;
	}//end of if
}//end of constructor Employee::Employee

bool Employee::set( int newId, char newName[], double newHourlyPay,int newNumDeps, int newType )
{
 	bool status = false;
	if ( newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 && newType >= 0 && newType <= 1 )
	{
		status = true;
		id = newId;
		strcpy(name, newName);
		hourlyPay = newHourlyPay;
		numDeps = newNumDeps;
		type = newType;
	}//end of if
	
 return status;
 
}//end of bool Employee::set

void Employee::setName(char value[25])
{
	strcpy(name,value);
}//end of set name

char* Employee::getName()
{
	return name;
}//end of get name

void Employee::setID(int value)
{
	id = value;
}//end of setID

int Employee::getID()
{
	return id;
}//end of getID

void Employee::setHourly(float value)
{
	hourlyPay = value;
}//end of set hourly pay

float Employee::getHourly()
{
	return hourlyPay;
}//end of get hourly

void Employee::setDeps(int value)
{
	numDeps = value;
}//end of set dependents

int Employee::getDeps()
{
	return numDeps;
}//end of getDeps

void Employee::setType(int value)
{
	type = value;
}//end of set Type

int Employee::getType()
{
	return type;
}//end of get Type


struct Report
{
	int employeeID;
	char* employeeName;
	float hoursWorked;
	float taxes;
	float insurance;
	float grossPay;
	float netPay;
	
};//end of struct Report

//function prototypes
void fillRoster(Employee [], Report [], int &);
void readWeek(int, Report []);
char getCommand(string prompt);
void calculateGross(int, Employee [], Report []);
void calculateExpenses(int, Employee [], Report []);
void showReport(int, Report []);
void printReport(int, Report []);

const int maxEmployee = 100;

int main()
{
	
	Employee myRoster[maxEmployee];
	Report weeklyPayroll[maxEmployee];
	int employeeCount;
	employeeCount = 0;
	char cmd = 'Y';
	char print = 'N';
	
    fillRoster(myRoster, weeklyPayroll, employeeCount);
    
    while(cmd == 'Y')
    {
    	readWeek(employeeCount, weeklyPayroll);
		calculateGross(employeeCount, myRoster, weeklyPayroll);
		calculateExpenses(employeeCount, myRoster, weeklyPayroll);
		showReport(employeeCount, weeklyPayroll);
		print = getCommand("Would you like to store this payroll info into a text file? (Y)es or (N)o: ");
		if(print == 'Y')
		{
			printReport(employeeCount, weeklyPayroll);
		}//end of if
    	cmd = getCommand("Process another pay week? (Y)es or (N)o: ");
	}//end of transaction


	system("PAUSE");
    return 0;
}//end of main

void printReport(int employeeCount, Report weeklyPayroll[])
{
	ofstream report;
	report.open("payroll.txt");
	report << "ID:        Name:                   Taxes  Insurance  Gross  Net:\n";
	for (int i = 0; i < employeeCount; i++)
	{
		report << setw(3) << right << weeklyPayroll[i].employeeID;
		report << setw(30) << right << weeklyPayroll[i].employeeName; 
		report << fixed << setprecision(2) << setw(8) << weeklyPayroll[i].taxes << setw(8) << weeklyPayroll[i].insurance << setw(8) << weeklyPayroll[i].grossPay << setw(8) << weeklyPayroll[i].netPay << "\n";
	}
	report.close();
	
}//end of printReport

void showReport(int employeeCount, Report weeklyPayroll[])
{
	cout << "ID:        NAME:                    TAXES:           INSURANCE:          GROSS PAY:       NETPAY:" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < employeeCount; i++)
	{
		cout << fixed << setprecision(2);
		cout << setw(3) << right << weeklyPayroll[i].employeeID;
		cout << setw(30) << right << weeklyPayroll[i].employeeName;
		if(weeklyPayroll[i].hoursWorked != 0)
		{
			cout << setw(8) << right << weeklyPayroll[i].taxes;
			cout << setw(20) << right << weeklyPayroll[i].insurance;
			cout << setw(20) << right << weeklyPayroll[i].grossPay;
			cout << setw(15) << right << weeklyPayroll[i].netPay << endl;
		}//end of if hoursWorked isn't 0
		else
		{
			cout << setw(8) << right << " N/A ";
			cout << setw(20) << right << " N/A ";
			cout << setw(20) << right << " N/A ";
			cout << setw(15) << right << " N/A " << endl;
		}//end of else
	}//end of for
}//end of showReport


void calculateGross(int employeeCount, Employee myRoster[], Report weeklyPayroll[])
{
	int type;
	
	for(int i = 0; i < employeeCount; i++)
	{
		type = myRoster[i].getType();
		if (type == 0)
		{
			if(weeklyPayroll[i].hoursWorked > 40)
			{
				weeklyPayroll[i].grossPay = ((weeklyPayroll[i].hoursWorked - 40) * (1.5 * myRoster[i].getHourly())) + (40 * myRoster[i].getHourly());
			}//end of if overtime
			else
			{
				weeklyPayroll[i].grossPay = weeklyPayroll[i].hoursWorked * myRoster[i].getHourly();
			}//end of if no overtime
		}//end of if hourly worker
		else if (type == 1)
		{
			weeklyPayroll[i].grossPay = weeklyPayroll[i].hoursWorked * myRoster[i].getHourly();
		}//end of sallaried worker
		
	}//end of for
}//end of void calculateGross

void calculateExpenses(int employeeCount, Employee myRoster[], Report weeklyPayroll[])
{
	for (int i = 0; i < employeeCount; i++)
	{	
		weeklyPayroll[i].taxes = weeklyPayroll[i].grossPay * .15; //flat tax of 15% for all employee types
		weeklyPayroll[i].insurance = 30.00 * myRoster[i].getDeps(); //$30 per dependent for all employee types
		weeklyPayroll[i].netPay = weeklyPayroll[i].grossPay - weeklyPayroll[i].insurance - weeklyPayroll[i].taxes;
	}//end of for loop
}//end of void calculateTaxes
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

void readWeek(int employeeCount,Report weeklyPayroll[])
{
	int empID;
	float hoursWorked;
	
	ifstream transactionFile;
	transactionFile.open("transaction.txt");
	
	if(transactionFile)
	{
		
		while(transactionFile)
		{
			transactionFile >> empID;
			transactionFile >> hoursWorked;
			transactionFile.ignore(20,'\n');
					
			for (int i = 0; i < employeeCount; i++)
			{
				if(weeklyPayroll[i].employeeID == empID)
				{
					if (hoursWorked > 0)
					{
						weeklyPayroll[i].hoursWorked = hoursWorked;
					}//end of if hoursWorked is valid
					else
					{
						weeklyPayroll[i].hoursWorked = 0;
					}//end of if hoursWorked is invalid
					
				}//end of if employee is in roster
			}//end of for loop
					
		}//end of while
						
				
		transactionFile.close();
	}//end of if transaction file exists
	else
	{
		cout << "File with this week's hours worked was not found." << endl;
	}//end of else
	

}//end of readWeek


void fillRoster(Employee myRoster[], Report weeklyPayroll[], int & employeeCount)
{
	int empID;
	char empName[25];
	float empHrly;
	int empDependents;
	int empType;
	ifstream masterFile;
	
    masterFile.open("masterfile.txt");
    if (masterFile)
    {
    	while(masterFile)
	    {
			masterFile >> empID;
	    	masterFile.getline(empName, 25);
	    	masterFile.clear();
	    	masterFile >> empHrly;
	    	masterFile >> empDependents;
	    	masterFile >> empType;
	    	masterFile.ignore(20,'\n');
	    	
	    	myRoster[employeeCount].setID(empID);
	    	weeklyPayroll[employeeCount].employeeID = myRoster[employeeCount].getID();
	    	myRoster[employeeCount].setName(empName);
	    	weeklyPayroll[employeeCount].employeeName = myRoster[employeeCount].getName();
	    	myRoster[employeeCount].setHourly(empHrly);	    	
	    	myRoster[employeeCount].setDeps(empDependents);
	    	myRoster[employeeCount].setType(empType);
	    	
			
			employeeCount += 1;
		}//end of while
		
		employeeCount -= 1;
		
	}//end of if
	else
	{
		cout << "TEST";
	}//end of else
	
	masterFile.close();
}//end of fillRoster
