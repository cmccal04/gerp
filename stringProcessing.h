/*
 *  stringProcessing.h
 *  Cullen McCaleb & Frank Li
 *  12/04
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file is a header file for the stripNonAlphaNum and isAlphaNum
 *  functions, which work together to strip the non-alpha numeric characters
 *  from a given string.
 * 
 */ 

#include <iostream>

using namespace std;


std::string stripNonAlphaNum (std::string input);
bool isAlphaNum (char input);