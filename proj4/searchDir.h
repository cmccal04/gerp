/*
 *  searchDir.h
 *  Cullen McCaleb & Frank Li
 *  12/07
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file is the header file for the searchDir class, which will
 *  fascillatate the output in the gerp project, using the HashMap created
 *  in the wordHash class. The public function runGerp uses the private
 *  functions to run the insensitive search, sensitive search, @f command,
 *  and @q command that are required in the Gerp project.
 *  There are no significant data structures in this class, other than a
 *  redefinition of the wordInstance struct from wordHash.
 *
 */

#include "wordHash.h"

class searchDir {
    public:
        //constructor
        searchDir();
        //only public function
        void runGerp(std::string inputFile, std::string outputFile);

    private:
        //wordInstance struct
        struct wordInstance{
            int pathIndex;
            int lineNum;
        };

        //private functitons
        void insensitive(std::string command, wordHash* gerpHash, 
                                                std::ostream& output);
        void sensitive(std::string command, wordHash* gerpHash, 
                                                std::ostream& output);
        bool checkRepeats(int j, int i, std::string word, wordHash* gerpHash, 
                                    vector<wordInstance>& reportedLines);
};