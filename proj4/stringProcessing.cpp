/*
 *  stringProcessing.cpp
 *  Cullen McCaleb & Frank Li
 *  12/04
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file is the implementation of the stripNonAlphaNum and isAlphaNum
 *  functions, which are defined in strinProcessing.h.
 * 
 */ 

#include <string>
#include "stringProcessing.h"
#include <iostream>
#include <sstream>

using namespace std;

/*
stripNonAlphaNum
purpose: strip all the non-alphanumeric (alphabetic) characters from the given 
        input.
Input: string input
output: string without the non-alphanumeric characters
*/
string stripNonAlphaNum (std::string input) {
    while(not input.empty() and (not isAlphaNum(input.front()))){
        input.erase(0, 1);
    }

    while(not input.empty() and (not isAlphaNum(input.back()))){
        input.pop_back();
    }
    return input;
}

/*
isAlphaNum
purpose: private class function used to determine whether the given char
        is an alphanumeric character or not
Input: char input
output: boolean value that returns true if the char is an alphanumeric and false
        otherwise
*/
bool isAlphaNum (char input) {
    if (int(input) <= 90 and int(input) >= 65 ) {
        return true;
    }
    if (int(input) <= 122 and int(input) >= 97) {
        return true;
    }
    if(int(input) <= 57 and int(input) >= 48){
        return  true;
    }
    return false;
}