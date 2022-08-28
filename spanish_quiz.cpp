/* 			
Name:                Megan Pierce     
Date:                Apr 18 2022
Assignment #:        EXAM 3 Program
Status:              Completed
Language:            C++
-------------------------------------------------------------------------
This program reads Spanish and English words from a provided .txt file (dictionary), quizes the user
and provides a .txt summary of how they did.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


class Dictionary								//class to store data from txt file for the English/Spanish dictionary
{
	private:
		string dict_English;
		string dict_Spanish;
		
	public:
		void setEnglish(string);
		void setSpanish(string);
		string getEnglish();
		string getSpanish();		
		
}; // end of Dictionary class


void Dictionary::setEnglish(string value)
{
	dict_English = value;
}//end of setEnglish

void Dictionary::setSpanish(string value)
{
	dict_Spanish = value;
}//end of setSpanish


string Dictionary::getEnglish()
{
	return dict_English;
}//end of getEnglish

string Dictionary::getSpanish()
{
	return dict_Spanish;
}//end of getSpanish


class QuizAnswers 								//class that stores each English quiz word, the user's answer, and the correct answer
{
	private:
		string english;
		string answer;
		string correctAnswer;
		
	public:
		void setEnglish(string);
		void setAnswer(string);
		void setCorrectAnswer(string);
		string getEnglish();
		string getAnswer();
		string getCorrectAnswer();
}; //end of QuizAnswers class

void QuizAnswers::setEnglish(string value)
{
	english = value;
}//end of set English

void QuizAnswers::setCorrectAnswer(string value)
{
	correctAnswer = value;
}//end of set correct answer

string QuizAnswers::getCorrectAnswer()
{
	return correctAnswer;
}//end of get correct answer

void QuizAnswers::setAnswer(string value)
{
	answer = value;
	for(int i = 0; i < answer.length();i++)
	{
		if(answer[i] >= 'A' && answer[i] <= 'Z')
		{
			answer[i]=answer[i]+32;
		}//end of if
	}//end of for
}//end of set answer

string QuizAnswers::getAnswer()
{
	return answer;
}//end of return answer

string QuizAnswers::getEnglish()
{
	return english;
}//end of return English

//REPORT CARD STRUCT
struct Report									//struct for program run total of attempts, fails, passes, quiz questions and highest grade
{
	int attempts;
	int passes;
	int fails;
	int countAllQuestions;
	float highestGrade;
};//end of struct Report


//function prototypes
void header();															//header function
string getString(string);												//function to gather string data from keyboard
char getCommand(string);												//function to gather char data from keyboard
int getQuizCount(int, string);											//function to get # of quiz questions from keyboard
void initializeStruct(Report*);											//function that initializes Report struct variables to 0
void loadDictionary(int &, Dictionary*);								//function to read from txt file into Dictionary class
void runQuiz(Dictionary* , QuizAnswers* , int, int, Report*, string);   //function to run an individual quiz
void updateSummary(int, int, Report*);									//function to update Report class
void shortSummary(string, float, float, float, int);					//function to print a summary individual quiz results								
void writeSingle(string, int, QuizAnswers*, Report*);					//function to write questions/answers/corrections for an individual quiz
void endQuizNumbers(Report*);											//function to print summary of Report class at the end of the program
void goodbye();														    //end function
const int maxWords = 100; 												//max words allowed in dictionary class


//MAIN PROGRAM
int main()
{
	//variable declarations
	string studentName;
	int wordCount = 0;                                     //how many words will be in dictionary file
	int wordsForQuiz = 0;                                  //how many words user would like to be quizzed on                                  //
	char cmd = 'Y';
	Dictionary* quizDictionary = new Dictionary[maxWords]; //class to contain English/Spanish dictionary from text file
	Report* quizSummary = new Report[1];				   //class to track attempts, passes, fails, # of quiz questions & highest grade
	initializeStruct(quizSummary);						   //sets Report struct items to 0
	
	header();											   //"hello" function
	loadDictionary(wordCount, quizDictionary);			   //function to read English/Spanish text file into dictionary class
	
	cout << "Enter your name: ";
	getline(cin >> ws, studentName);
	
	while(cmd == 'Y')
	{
		wordsForQuiz = getQuizCount(wordCount, "How many questions would you like on the quiz?\n>> ");
		QuizAnswers* quiz = new QuizAnswers[wordsForQuiz]; //quiz answer storage
		runQuiz(quizDictionary, quiz, wordsForQuiz, wordCount, quizSummary, studentName);
		writeSingle(studentName, wordsForQuiz, quiz, quizSummary); //writing this quiz's questions/answers/corrections
		
		cmd = getCommand("Would you like to take another quiz? (Y)es or (N)o:\n>> ");
	}//end of while
	
	endQuizNumbers(quizSummary);						   //displays Report class information
	
	goodbye();  										   //end of program
	
	system("PAUSE");
    return 0;
}//end of main


void runQuiz(Dictionary* quizDictionary, QuizAnswers* quiz, int wordsForQuiz, int wordCount, Report* quizSummary, string studentName)
{
	int question = 1;   //quiz question numbering
	int quizword;		//index number for quiz word selection
	float wrong = 0;    //incorrect user answers
	float correct = 0;  //correct user answers
	float grade = 0;    //final grade of current quiz
	
	quizSummary[0].attempts ++; //adding 1 to total attempts at quizzes
	
	cout << "\n                  Quiz# " << quizSummary[0].attempts << endl;
	
	for (int a = 0; a < wordsForQuiz; a++)
	{	
		
		srand(time(0));
		quizword = rand() % wordCount; //random # chosen for index number
		
		
		
		cout << "Question #" << question << ":" << endl;
		cout << "English word: " << quizDictionary[quizword].getEnglish() << endl;
		quiz[a].setEnglish(quizDictionary[quizword].getEnglish());
		quiz[a].setAnswer(getString(">> "));
		quiz[a].setCorrectAnswer(quizDictionary[quizword].getSpanish());
		
		if (quiz[a].getAnswer() == quiz[a].getCorrectAnswer())
		{
			cout << "\nCorrect!" << endl;
			cout << "--------------------------------------------\n" << endl;
			correct ++;
		}//end of if answer was right
		else
		{
			cout << "\nIncorrect." << endl;
			cout << "--------------------------------------------\n" << endl;
			wrong ++;
		}//end of else if answer was wrong
		
		question ++; //increment question# by 1 
		
	}//end of for
	
	grade = (correct / float(wordsForQuiz)) * 100;
	
	updateSummary(grade, wordsForQuiz, quizSummary); //CAUSING AN ERROR "terminate called after throwing
	//an instance of std::length_error

	cout << "--------------------------------------------" << endl;
	shortSummary(studentName, correct, wrong, grade, wordsForQuiz);

}//end of runQuiz


void writeSingle(string studentName, int wordsForQuiz, QuizAnswers* quiz, Report* quizSummary)
{
	ofstream summary;
	summary.open("quizSummary.txt");
	
	summary << "Summary of Quiz #" << quizSummary[0].attempts << " taken by " << studentName << "\n";
	summary << "-----------------------------------------------------------\n";
	for (int i = 0; i < wordsForQuiz; i++)
	{
		summary << "Question " << i + 1 << ": " << quiz[i].getEnglish() << "\n";
		summary << "Your answer: " << quiz[i].getAnswer() << "\n";
		if(quiz[i].getAnswer() == quiz[i].getCorrectAnswer())
		{
			summary << "Correct!\n\n";
		}//end of if user answer was correct
		else
		{
			summary << "Wrong. Correct answer: " << quiz[i].getCorrectAnswer() << "\n\n";
		}//end of else if user's answer was wrong
		
	}//end of for loop
	
	summary.close();
	
	cout << "A summary of the most recent quiz taken can be found in quizSummary.txt.\n" << endl;
}//end of writeSingle



void shortSummary(string studentName, float correct, float wrong, float grade, int wordsForQuiz)
{
	cout << "          SUMMARY" << endl;
	cout << left << setw(10) << "Name:" << right << setw(20) << studentName << endl;
	cout << left << setw(10) << "Answered:" << right << setw(20) << wordsForQuiz << endl;
	cout << left << setw(10) << "Correct:" << right << setw(20) << correct << endl;
	cout << left << setw(10) << "Incorrect:" << right << setw(20) << wrong << endl;
	cout << fixed << setprecision(0);
	cout << left << setw(10) << "Grade: " << right << setw(20) << grade << endl;
	if(grade >=60)
	{
		cout << "\nCongrats! You passed the quiz.\n" << endl;
	}//end of pass message
	else
	{
		cout << "\nYou failed the quiz this time.\n" << endl;
	}//end of fail message
}//end of short summary (EMBEDDED IN RUN QUIZ FUNCTION)

void updateSummary(int grade, int wordsForQuiz, Report* quizSummary)
{

	
	if(grade >= 60)
	{
		quizSummary[0].passes ++;
	}// end of if grade is passing
	else
	{
		quizSummary[0].fails ++;
	}// end of if grade is failing
	
	quizSummary[0].countAllQuestions += wordsForQuiz; //adding count of words quizzed on
	
	if(grade > quizSummary[0].highestGrade)
	{
		quizSummary[0].highestGrade = grade;
	}//end of if grade is now highest grade
	
}//end of updateSummary (EMBEDDED IN RUN QUIZ FUNCTION)

string getString(string prompt)
{
	string userInput;
	
	cout << prompt;
	cin >> userInput;

	return userInput;
}//end of getString

void header()
{
	cout << "              English-Spanish Class" << endl;
	cout << "             Written by Megan Pierce" << endl;
	cout << "--------------------------------------------------" << endl;
}//end of header


void loadDictionary(int & wordCount, Dictionary* quizDictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open("dictionary.txt");
	string englishWord;
	string spanishWord;

	if(dictionaryFile)
	{
		while(dictionaryFile)
		{

			dictionaryFile >> englishWord;
			quizDictionary[wordCount].setEnglish(englishWord);
			dictionaryFile >> spanishWord;
			quizDictionary[wordCount].setSpanish(spanishWord);
			dictionaryFile.ignore(20,'\n');

			wordCount += 1;

		}//end of while
		wordCount -= 1;
		
	}//end of if
	else
	{
		cout << "Dictionary could not be located. Please check that dictionary.txt exists." << endl;
	}//end of else
	
	cout << "--------------------------------------------------" << endl;
	cout << "      Dictionary has successfully loaded." << endl;
	cout <<"      " << wordCount << " quiz words exist." << endl;
	cout << "--------------------------------------------------" << endl;
}//end of loadDictionary


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


int getQuizCount(int wordCount, string prompt)
{
	int number;
	
	while(true)
	{
		cout << prompt;
		cin >> number;
		
		if (number > 0 && number <= wordCount)
		{
			return number;
		}//end of if
		
		cout << "Dictionary is limited to " << wordCount << " words." << endl;
	}//end of while
}//end of getQuizCount

void goodbye()
{
	cout << "--------------------------------------------------" << endl;
	cout << "               Good effort." << endl; 
	cout << "Keep studying and try the quizzing yourself again." << endl;
	cout << "--------------------------------------------------" << endl;
}//end of goodbye


void endQuizNumbers(Report* quizSummary)
{
	cout << "--------------------------------------------------" << endl;
	cout << left << setw(16) << "Quizes Taken:" << right << setw(20) << quizSummary[0].attempts << endl;
	cout << left << setw(16) << "Quizes Passed:" << right << setw(20) << quizSummary[0].passes << endl;
	cout << left << setw(16) << "Quizes Failed:" << right << setw(20) << quizSummary[0].fails << endl;
	cout << left << setw(16) << "Total questions:" << right << setw(20) << quizSummary[0].countAllQuestions << endl;
	cout << left << setw(16) << "Highest grade:" << right << setw(20) << quizSummary[0].highestGrade << endl;
	
}//end of endQuizNumbers

void initializeStruct(Report* quizSummary)
{
	quizSummary[0].attempts = 0;
	quizSummary[0].passes = 0;
	quizSummary[0].fails = 0;
	quizSummary[0].countAllQuestions = 0;
	quizSummary[0].highestGrade = 0;
	
}//end of initializeStruct