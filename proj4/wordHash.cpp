/*
 *  wordHash.cpp
 *  Cullen McCaleb & Frank Li
 *  12/06
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file contains the implementation of the wordHash class, which creates
 *  and fills a hashMap according to the contents of a given directory.
 *
 */

#include "FSTree.h"
#include "DirNode.h"
#include "stringProcessing.h"
#include "wordHash.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>

/* wordHash()
* Purpose: Constructs an instance of wordHash, by updated the directory name,
*          creating an FSTree, and updating tree.
* Input: Nothing.
* Return: Nothing.
*/
wordHash::wordHash(string dirName) {
    directory = dirName;
    FSTree tempTree(directory);
    //use of copy contructor
    tree = tempTree;
}

/* fillHash()
* Purpose: Creates a tree from a given directory, uses fillPaths to
           traverse the tree and fill in the paths array, then uses insertWords
           to fill the hash.
* Input: Nothing
* Return: Nothing
*/
void wordHash::fillHash(){
    std::vector<string> tempPath;
    fillPaths(tree.getRoot(), tempPath);
    for(size_t i = 0; i<paths.size(); i++){
        ifstream file(paths[i]);
        insertWords(file, i);
    }
}

/* fillPaths()
* Purpose: Takes a tree's root and fills in the path array, recursively.
* Input: A pointer to a dirNode, and a reference to a vector containing the 
         names of every file in the paths.
* Return: Nothing.
*/
void wordHash::fillPaths(DirNode *node, std::vector<string>& tempPath){
    //check that the tree is not empty
    if (node->isEmpty()){
        return;
    }
    //traverse the tree to fill the paths array
    tempPath.push_back(node->getName());
    if (node->hasFiles()) {
        for(int i = 0; i<node->numFiles(); i++){
            tempPath.push_back(node->getFile(i));
            int pathSize = tempPath.size();
            for (int j = 0; j < pathSize; j++) {
                if(j == 0){
                    paths.push_back("");
                }
                paths.back() += tempPath[j];
                if (j != pathSize - 1){
                    paths.back() += "/";
                }
            }
            tempPath.pop_back();
            
        }
    }
        if(node->hasSubDir()){
            for(int i = 0; i<node->numSubDirs(); i++){
                fillPaths(node->getSubDir(i), tempPath);
            }
        }
    tempPath.pop_back();
}  

/* insertWords()
* Purpose: Inserts all the words in a file to the hash table.
* Input: A a reference to an ifstream, as the file, and an index to the path
         array. The pathIndex is used so the words that are added are 
         associated with a path.
* Return: Nothing.
*/
void wordHash::insertWords(ifstream& myfile, int pathIndex) {
    //myfile.open(filename);
    vector<std::string> fileLines;
    lines.push_back(fileLines);
    //check if the file is open
    // if(myfile.fail()) {
    //     std::cerr << "error opening file \n";
    //     return;
    // }
    //variables
    std::string word;
    std::string line;
    int lineNum = 0;
    //read lines
    while (std::getline(myfile, line)) {
        lineNum++;
        //copy the line into istream
        std::istringstream words(line); 
        //read words from line
        addLines(line, pathIndex);
        while(getline(words, word, ' ')) {
            //remove the non-letters/numbers
            word = stripNonAlphaNum(word);
            //change word to lowercase
            std::string lower = toLower(word);
            //insert word into hash
            addToHash(lower, word, pathIndex, lineNum);
        }
    }
}

/* toLower()
* Purpose: Takes a word with uppercase letters and makes it all lowercase
* Input: A refrence to a string to make lowercase.
* Return: A string, representing the lowercase version of the word.
*/
std::string wordHash::toLower(std::string &word) {
   std::string lowercase = word;
    for (char& c : lowercase) {
        if (c >= 'A' and c <= 'Z') {
            c = c + ('a' - 'A');
        }
    }
    return lowercase;
}

/* addToHash()
* Purpose: Adds a word to the hash. The spot in the hash depends on if the 
           word already exists or not.
* Input: References to two strings representing the word, and lowercase 
         version of the word. Two ints representing the paths index and
         line number.
* Return: Nothing
*/
void wordHash::addToHash(std::string &lower, std::string &word, int pathIndex, 
                                                            int lineNum) {
    //check if the word is in the first hash already
    if(not mainHash.inHash(lower)){
        HashMap<std::string, vector<wordInstance>> minHash;
        vector<wordInstance> wordInstances;
        //create a wordInstance with lineNum and pathNum
        wordInstances.emplace_back(wordInstance{pathIndex, lineNum});
        minHash.insert(word, wordInstances);
        mainHash.insert(lower, minHash);
    }else{  
        HashMap<std::string, vector<wordInstance>>& minHash = 
                                                    mainHash.get(lower);
        //check if the case sensitive word is in the second hash
        if(minHash.inHash(word)){
            vector<wordInstance>& wordInstances = minHash.get(word);
            if(not ((wordInstances.back().lineNum == lineNum) and 
                            (wordInstances.back().pathIndex == pathIndex))){
                wordInstances.emplace_back(wordInstance{pathIndex, lineNum});
            }
        }else{
            //create a word instance of the new word
            vector<wordInstance> wordInstances;
            wordInstances.emplace_back(wordInstance{pathIndex, lineNum});
            minHash.insert(word, wordInstances);
        }
    }
}

/* addLines()
* Purpose: Adds a line to the line vector.
* Input: A reference to a string represnting the line, and pathIndex to 
         represent the file the line is associated with.
* Return: Nothing.
*/
void wordHash::addLines(std::string &line, int pathIndex){
    lines[pathIndex].push_back(line);
}