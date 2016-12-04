#include <iostream>
#include <sstream>
#include <string>
#include "User.hpp"
#include "account.hpp"

#ifndef IMPLEMENT_H
#define IMPLEMENT_H

int getNumIn();

Account& selectAccount(User& user);
void editPassword(User& user, Account&);
void editAccounts(User& user);
void editUsername(User& user, Account&);
int logIn(User &user);
void addAccount(User& user);
User createUserAccount();
void mainMenu(User&); 
#endif
