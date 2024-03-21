/*
 *  searchDir.cpp
 *  Cullen McCaleb & Frank Li
 *  12/07
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file contains the implementation of the searchDirr class, which will
 *  fascillatate the output in the gerp project, using the hashMap created
 *  in the wordHash class.
 *
 */

#include "searchDir.h"
#include <fstream>

/* searchDir()
* Purpose: Constructs an instance of the searchDir class.
* Input: Nothing.
* Return: Nothing.
*/
searchDir::searchDir(){
    //nothing needs to be done
}

/* runGerp()
* Purpose: Runs all of gerp, by handling the various required commands based 
           on a given input file, and outputting everything to a given output 
           file.
* Input: Two strings, representing the input file and output file.
* Return: Nothing.
*/
void searchDir::runGerp(std::string inputFile, std::string outputFile){
    std::ofstream output(outputFile);
    wordHash makeHash(inputFile);
    makeHash.fillHash();
    std::string command;
    std::cout << "Query? ";
    while((cin >> command)){
        if((command == "@i") or (command == "@insensitive")){
            cin >> command;
            insensitive(command, &makeHash, output);
        }else if((command == "@f")){
            output.close();
            cin >> command;
            runGerp(inputFile, command);
            return;
            //not sure, we'll figure it out
        }else if((command == "@q") or (command == "@quit")){
            std::cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }else {
            sensitive(command, &makeHash, output);
        }
        std::cout << "Query? ";
    }
    output.close();
}

/* sensitive()
* Purpose: Handles the case sensitive word search in Gerp. Searches through a 
           HashMap created by a wordHash instance from runGerp.
* Input: A string representing the commmand, a pointer to a wordHash instance,
         and a reference to an ostream to send the output.
* Return: Nothing.
*/
void searchDir::sensitive(std::string command, wordHash* gerpHash, 
                                                        std::ostream& output){
    //search for command in the hash
    command = stripNonAlphaNum(command);
    std::string word = gerpHash->toLower(command);
    if(gerpHash->mainHash.inHash(word)){
        if(gerpHash->mainHash.get(word).inHash(command)){
            for(size_t i = 0; 
                    i<gerpHash->mainHash.get(word).get(command).size(); i++){
                //get the path and line number
                output << gerpHash->paths
                [gerpHash->mainHash.get(word).get(command)[i].pathIndex]
                << ":" << gerpHash->mainHash.get(word).get(command)
                [i].lineNum << ": ";
                //get the line
                output << gerpHash->lines
                [gerpHash->mainHash.get(word).get(command)[i].pathIndex]
                [gerpHash->mainHash.get(word).get(command)[i].lineNum-1] 
                << endl;
                
            }
        }else{
            output << command << " Not Found. Try with @insensitive or @i." 
                                                                << endl;
        }
    }else{
        output << command << " Not Found. Try with @insensitive or @i." 
                                                                << endl;
    }
}

/* insensitive()
* Purpose: Handles the case insensitive wordsearch in Gerp. Searches through a
           HashMap created by a wordHash instance from runGerp.
* Input: A string representing the commmand, a pointer to a wordHash instance,
         and a reference to an ostream to send the output.
* Return: Nothing.
*/
void searchDir::insensitive(std::string command, wordHash* gerpHash, 
                                                        std::ostream& output){
    //create a vector to hold the lines that have printed, so as not to 
    //repeat lines
    vector<wordInstance> reportedLines;
    //search for command in the hash
    command = stripNonAlphaNum(command);
    std::string word = gerpHash->toLower(command);
    if(gerpHash->mainHash.inHash(word)){
        for(int j = 0; j<gerpHash->mainHash.get(word).size(); j++){
            for(size_t i = 0; i<gerpHash->mainHash.get(word).at(j).size(); i++){
                //make sure the line has not been printed yet
                if(checkRepeats(j, i, word, gerpHash, reportedLines)){
                    //get the path and line number
                    output << gerpHash->paths
                    [gerpHash->mainHash.get(word).at(j)[i].pathIndex]
                    << ":" << gerpHash->mainHash.get(word).at(j)
                    [i].lineNum << ": ";
                    //get the line
                    output << gerpHash->lines
                    [gerpHash->mainHash.get(word).at(j)[i].pathIndex]
                    [gerpHash->mainHash.get(word).at(j)[i].lineNum-1] 
                    << endl;
                }
            }
        }
    }else{
        output << command << " Not Found." << endl;
    }
}

/* checkRepeats()
* Purpose: Checks if there are repeats of a wordInstance in a vector 
           of wordInstances.
* Input: A string, a pointer to a wordHash instance, and two integers 
         representing where in the HashMap to check for a repeat. A 
         reference to a vector of wordInstances that contains the lines
        that have already been outputted.
* Return: A boolean representing if the line already exists in repeatedLines.
*/
bool searchDir::checkRepeats(int j, int i, std::string word, 
            wordHash* gerpHash, vector<wordInstance>& reportedLines){
    wordInstance newLine{gerpHash->mainHash.get(word).at(j)[i].pathIndex, 
    gerpHash->mainHash.get(word).at(j)[i].lineNum-1};
    for(size_t t = 0; t<reportedLines.size(); t++){
        if((reportedLines[t].pathIndex == newLine.pathIndex) 
        and ((reportedLines[t].lineNum) == newLine.lineNum)){
            return false;
        }
    }
    reportedLines.push_back(newLine);
    return true;

}







