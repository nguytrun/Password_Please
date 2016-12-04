#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include "account.hpp"

using namespace std;

int main() {

    //TESTING
    
    //Create an account with pre-determined security level
    Account a1 = Account("Best Buy", "helloWorld", 1);
    cout << "You've successfully added an account with pre-determined security level!"<<endl;
    cout << "Account Name: " << a1.getAccountName() <<endl;
    cout << "User Name: " << a1.getUserName() <<endl;
    cout << "Security Level: " << a1.getSecurityLevel() <<endl <<endl;
    
    //Create an account with no pre-determined security level
    Account a2 = Account("Amazon", "helloMoon", 0);
    cout << "You've successfully added an account with no pre-determined security level!" <<endl;
    cout << "Account Name: " << a2.getAccountName() <<endl;
    cout << "User Name: " << a2.getUserName() <<endl;
    cout << "Security Level: " << a2.getSecurityLevel() <<endl <<endl;
    
    //Set password that will pass
    a1.setPassword("Please");
    cout << endl;
    cout << "Password Set: " << a1.getPassword() <<endl;
    
    //Set password that will not pass
    a2.setPassword("wRong");
    cout << endl;
    
	return 0;

}
