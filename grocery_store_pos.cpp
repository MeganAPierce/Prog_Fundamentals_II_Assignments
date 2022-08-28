/* 
Name:     		Megan Pierce
Date: 			3-22-2022
Assignment #:	Exam 2 Project: Grocery Store POS
-------------------------------------------------------------------------
Goal:
Write a program that will be a POS system for a grocery store. 

For every transaction the list of items will be displayed with the price
and the total sales amount will be displayed.

The list of items and its price will be loaded from a text file. Assume
there are not more than 25 items in the store. Sales tax is 8.25%. 

*/
#include <iomanip>
#include <fstream>    //for file handling
#include <iostream>	  // for cin, cout, endl
using namespace std;


// struct definitions

//struct for file read
struct Basket
{
	string foodItem;
	float pounds;
	float totalPrice;
	
}; //end of struct Transaction


//prototype declerations
void header();
void footer();
int getIntegerEntry(string);
float getFloatEntry(string);
int countFile(int &);
void createArrays(int, int [], string [], float []);
void displayMenu(int, int [], string [], float []);
char userInput(char &);
void addBasket(int, int, int [], string [], float [], Basket []);
void displayBasket(int, Basket []);
void displayTotal(Basket [], int );
int main()
{
	//header function with grocery store name
	header();
	
    // decleration of variables 
    const int MAX_VALUE = 25;
    Basket myCustomer[MAX_VALUE];
	int count; //count for basket
	int arrayNum; //to set number of elements in product and price arrays
	char cmd; //for user input
	count = 0; //initialize count

	//function to decide how large arrays should be
	countFile(arrayNum);
	
	//declaring arrays
	int productNum[arrayNum];
	string productName[arrayNum];
	float pricePerPound[arrayNum];
	
	//filling empty arrays
	createArrays(arrayNum, productNum, productName, pricePerPound);
	
	while(true)
	{
		char cmd;
		displayMenu(arrayNum, productNum, productName, pricePerPound);
		userInput(cmd);
		if(cmd == 'T' && count <= MAX_VALUE)
		{
			addBasket(count, arrayNum, productNum, productName, pricePerPound, myCustomer);
			count += 1;
		}//end of if add to basket
		else if(cmd == 'T' && count > MAX_VALUE)
		{
			cout << "test" <<endl;
		}//end of if start transaction but user has reached max value
		else if(cmd == 'E')
		{	
			if (count == 0)
			{
				cout <<"\nYour basket is empty. Canceling transaction.\n" << endl;
				break;
			}//end of count == 0
			else
			{
				displayBasket(count, myCustomer);
				displayTotal(myCustomer, count);
				break;
			}//end of else
		}//end of if finalize order
		else if (cmd == 'X')
		{
			cout << "Transaction canceled" << endl;
			break;
		}//end of if transaction is canceled		
		else
		{
			cout << "----------------------------------------------" << endl;
			cout << "\nThat wasn't in the list of options. Try again.\n" << endl;
			cout << "----------------------------------------------" << endl;
		}//else if user input is invalid

	}//end of while
	
	
    // displays the results

    
    system("PAUSE");
    return 0;
    
}// end of main



//function to display at the very beginning of program
void header()
{
	cout << "-----------------------------------" << endl;
	cout << "         Megan's Grocery" << endl;
	cout << "-----------------------------------" << endl;
	
}//end of void header()

//function to display at the very end of the program
void footer()
{
	cout << "Thank you for shopping with us. Goodbye." << endl;
	
}//end of void footer()


//function to determine line count in text file, to help determine size of menu
int countFile(int & arrayNum)
{
	int lineCount;
	lineCount = 0;
	ifstream inputFile; //ifstream to READ
	inputFile.open("item.txt"); //file is open
	string line;

	
	if(inputFile)
	{
		while(inputFile >> line)
		{
			lineCount += 1;
		}
		inputFile.close();
	}//end of if
	else
	{
		cout << "File not found." << endl;
	}//end of else
	
	arrayNum = lineCount / 2;
	
	return arrayNum;
}//end of countFile


//function to read text file into arrays per 
void createArrays(int arrayNum, int productNum[], string productName[], float pricePerPound[])
{
	ifstream inputFile;
	inputFile.open("item.txt");
	
	for(int i = 0; i < arrayNum; i++)
	{
		productNum[i] = i + 1;
		inputFile >> productName[i];
		inputFile >> pricePerPound[i];
	}//end of for
	
	inputFile.close();
	
}//end of createArrays


//function to display menu
void displayMenu(int arrayNum,int productNum[], string productName[], float pricePerPound[])
{
	cout << "           Grocery Items" << endl;
	cout << " Item #:" << setw(12) << "Product:" <<  setw(12) << "$/lb:" << endl;
	cout << "-----------------------------------" << endl;	
	for(int i = 0; i < arrayNum; i++)
	{
		cout << fixed << setprecision(2);
		cout << productNum[i] << setw(20) << productName[i] << setw(9) << "$" << pricePerPound[i] << endl;		
	}//end of for
}//end of displayMenu


//function to gather user input
char userInput(char & cmd)
{
	
	cout << "\nT - Add to your basket" << endl;
	cout << "X - Cancel your order" << endl;
	cout << "E - Finalize order" << endl;
	cout << "\nEnter the letter corresponding to your choice: ";
	cin >> cmd;
	
	cmd = toupper(cmd);
	
	return cmd;
}//end of userInput


char overMax(char & cmd)
{
	cout << "No more items are available to choose from. " <<endl;
	cout << "Choose from the following:" << endl;
	cout << "X - Cancel your order" << endl;
	cout << "E - Finalize order" << endl; 
	cout << "\nEnter the letter corresponding to your choice: ";
	cin >> cmd;
	cmd = toupper(cmd);
}

float getFloatEntry(string prompt)
{
	float value;
	
	while (true)
	{
		cout << prompt;
		cin >> value;
		
		if (value >= 0)
		{
			return value;
		} // end of if (value >= 0)
		
		cout << "You can't enter a negative. Retry." << endl;
		
	} // end of while (true)	
	
} //end of getFloatEntry()

int getIntegerEntry(string prompt)
{
	int value;
	
	while (true)
	{
		cout << prompt;
		cin >> value;
		
		if (value >= 0)
		{
			return value;
		} // end of if (value >= 0)
		
		cout << "You can't enter a negative. Retry. " << endl;
		
	} // end of while (true)
} // end getIntegerEntry()


void addBasket(int count, int arrayNum, int productNum[], string productName[], float pricePerPound[], Basket myCustomer[])
{
	int foodID;
	int found;
	float pounds;
	found = 0;
	
	foodID = getIntegerEntry("\nEnter the number ID of the food item: ");
	
	for(int i = 0; i < arrayNum; i++)
	{
		if(foodID == productNum[i])
		{
			found = 1; 
			myCustomer[count].foodItem = productName[i];
			pounds = getFloatEntry("How many pounds would you like? ");
			myCustomer[count].pounds = pounds;
			myCustomer[count].totalPrice = (pricePerPound[count] * pounds);
			cout << productName[i] << " have been added to your basket!\n" << endl;
		}//end of if
	}//end of for
	
	if (found == 0)
	{
		cout << "I'm sorry but that's not an option. Please try another." << endl;
	}
}//end of void addBasket

void displayBasket(int count, Basket myCustomer[])
{
	if(count > 0)
	{
		cout << "Items sold today..." << endl;
		cout << "-----------------------------------" << endl;
		cout << left << setw(15) <<"Product:" << right << setw(8) << "Amount:" <<  right << setw(11) << "Cost:" << endl;
		cout << "-----------------------------------" << endl;
		
		for(int i = 0; i < count; i++)
		{
			cout << fixed << setprecision(2);
			cout << setfill('.');
			cout << left << setw(15) << myCustomer[i].foodItem<< right << setw(5) << myCustomer[i].pounds << " lbs." << right << setw(4) << "$" << myCustomer[i].totalPrice << endl;
		}//end of for loop
	}//end of if
	else if(count <=0)
	{
		cout << "\n\n Your basket is empty! Please review the menu again.\n" << endl;
	}//end of else

}//end of void displayBasket

void displayTotal(Basket myCustomer[], int count)
{
	float subTotal;
	float endTotal;
	float salesTax;
	
	subTotal = 0;
	endTotal = 0;
	salesTax = 0;
	
	for(int i = 0; i < count; i++)
	{
		subTotal += myCustomer[i].totalPrice;
	}
	
	endTotal = subTotal * 1.0825;
	salesTax = endTotal - subTotal;
	cout << fixed << setprecision(2);
	cout << setfill('.');
	cout << "Sub Total:" << right << setw(19) << "$" <<subTotal << endl;
	cout << "Sales Tax:" << right << setw(20) << "$" <<salesTax << endl;
	cout << "GRAND TOTAL:" << right << setw(17) << "$" <<endTotal << endl;
	
 }//end of void displayTotal
 
 