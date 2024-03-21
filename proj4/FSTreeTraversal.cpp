/*
 *  FSTreeTraversal.cpp
 *  Cullen McCaleb and Frank Li
 *  12/04
 *
 *  CS 15 Project 4 Gerp
 *
 *  FSTreeTraversal.cpp is a program that prints every directory to file path 
 *  in a given directory. This is done using an n-ary tree data structure,
 *  built from the given DirNode and FSTree classes.
 *
 */

#include <string>
#include "FSTree.h"
#include "DirNode.h"
#include <vector>
#include <iostream>

using namespace std;

//function declarations
void traverseTree(std::string directory);
void traverseTreeHelper(DirNode *node, std::vector<string>& path);


/* traverseTree()
* Purpose: Creates a tree from a given directory, and prints every path in 
           that tree, from the directory name to the file name
* Input: A string representing the directory name.
* Return: Nothing
*/
void traverseTree(std::string directory){
    FSTree myTree(directory);
    DirNode *root = myTree.getRoot();
    std::vector<string> path;
    traverseTreeHelper(root, path);
}

/* traverseTreeHelper()
* Purpose: Helps traverseTree to print each root-leaf path in the FSTree.
           This is a recursive function.
* Input: A pointer to a dirNode, and a reference to a vector containing the 
         names of every file in the paths.
* Return: Nothing
*/
void traverseTreeHelper(DirNode *node, std::vector<string>& path){
    if (node->isEmpty()){
        return;
    }

    path.push_back(node->getName());

    if (node->hasFiles()) {
        for(int i = 0; i<node->numFiles(); i++){
            path.push_back(node->getFile(i));
            int pathSize = path.size();
            for (int j = 0; j < pathSize; j++) {
                std::cout << path[j];
                if (j != pathSize - 1){
                    std::cout << "/";
                }
            }
            path.pop_back();
            std::cout << std::endl;
        }
    }
        if(node->hasSubDir()){
            for(int i = 0; i<node->numSubDirs(); i++){
                traverseTreeHelper(node->getSubDir(i), path);
            }
        }

    path.pop_back();
}

/* main()
* Purpose: Main function for FSTreeTraversal.cpp
* Input: An int representing the number of command line arguments, and an 
         array containing these arguments.
* Return: Nothing
*/
int main(int argc, char *argv[]){
    if(argc == 2){
        traverseTree(argv[1]);
    }else{
        std::cerr << "Usage: ./treeTraversal inputDirectory" << endl;
    }
}