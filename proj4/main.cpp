/*
 *  main.cpp
 *  Cullen McCaleb & Frank Li
 *  12/08
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file contains the main function for the Gerp project. In the main 
 *  function, the correct number of arguments is checked, and an instance 
 *  of searchDir is created. runGerp is called on that instance, and the
 *  program is launched.
 *
 */

#include <iostream>
#include <string>
#include "DirNode.h"
#include "FSTree.h"
#include "wordHash.h"
#include "searchDir.h"
#include "HashMap.cpp"

int main(int argc, char *argv[]){
    //check that the correct number of arguments are given
    if(argc != 3){
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }
    searchDir gerp;
    gerp.runGerp(argv[1], argv[2]);
    
    return 0;
}