/***********************************************************
**User Story 6      Similar Password
**
**DESCRIPTION:      main CPP file
**Version:			1.0
**
**This program will check add a series of passwords and compare to see if they are the same(will add additional functionality later)
***********************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

bool checkSimilarity(string passwordsToAdd, string passwordList[], int numPasswords );
void warning();

int main() {


	
	//Member variables for the number of password, and the current password to be added onto list as well as the password.
	int numPasswords;
	int index;
	string passwordsToAdd;
	
	//Ask for user input
	cout << "How many passwords would you like to implement?" << endl;
	cin >> numPasswords;
	
	//Creates memory allocation for string array;
	string passwordList[numPasswords];

	
	// x is condition for loop to run until enough passwords are inputted
	int x = 0;
	index = 0;
	while (x == 0)
	{
		
		cout << "Enter Password " << index+1 << endl;
		cin >> passwordsToAdd;
		
		if (checkSimilarity(passwordsToAdd, passwordList,index) == false)
		{
			passwordList[index] = passwordsToAdd;
			index++;
			if (index == numPasswords) {
			x = 1;
			}
		}
		else 
		{
			warning();
		}
		

		
	}
	
	
   
}

bool checkSimilarity (string passwordsToAdd, string passwordList[], int index)
{
	//cout << "I was here " << endl;
	string p1;
	string p2 = passwordsToAdd;
	
	for (int i = 0; i <= index;i++)
	{
		p1 = passwordList[i];
		if (p1 == p2)
		{
			cout <<"same pw" <<endl;
			return true;
		}
		else
		{
		}
			
		
	}
	

	return false;
}

void warning() {
	cout << "Warning, you are using the same password, please switch to a different password" << endl;
}

