/*
 *  wordHash.h
 *  Cullen McCaleb & Frank Li
 *  12/06
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file is a header file for the wordHash class. The class includes
 *  functions to fill in a hash map containing all the words in a given
 *  directory. These functions will run when a user of the class calls
 *  fillHash(). 
 *  The primary data structure in this class is the HashMap data structure
 *  which was created in my HashMap class. Using this HashMap class, wordHash
 *  creates a double hash map to organize every word in the directory
 *  in the form of wordInstances.
 *
 */

#ifndef _WORD_HASH_
#define _WORD_HASH_

#include "FSTree.h"
#include "DirNode.h"
#include "stringProcessing.h"
#include "HashMap.cpp"
#include <vector>


class wordHash {
    public:
        //constructor
        wordHash(string dirName);

        //public functions
        void fillHash();
        std::string toLower(std::string &word);

        //vectors that hold the paths and lines for each word
        //the lineNum and pathIndex in wordInstance refer to these vectors
        vector<std::string> paths;
        vector<vector<std::string>> lines;

        //wordInstance struct
        struct wordInstance{
            int pathIndex;
            int lineNum;
        };

        //Hash map declaration
        //has to be public because we need wordInstance in it
        HashMap<std::string, HashMap<std::string, vector<wordInstance>>> 
                                                                mainHash;

    private:

        //variabls that are initialized in the constructor
        std::string directory;
        FSTree tree;

        //private functions
        void fillPaths(DirNode *node, std::vector<string>& path);
        void addLines(std::string& line, int pathIndex);
        void insertWords(ifstream& myfile, int pathIndex);
        void addToHash(std::string &lower, std::string &word, 
                                            int pathIndex, int lineNum);


};

#endif