/*
 *  unit_test.h
 *  Cullen McCaleb & Frank Li
 *  12/07
 *
 *  CS 15 Project 4 Gerp
 *
 *  This file's purpose is to test various parts of our gerp project, a 
 *  program that can search for a given word in a given directory.
 *
 */

#include "HashMap.cpp"
#include "wordHash.h"
#include "DirNode.h"
#include "FSTree.h"
#include "stringProcessing.h"
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

// testStringProcessing()
// Purpose: Tests the stringProcessing class from part one, which we'll 
//          use in part 2.
void testStringProcessing(){
    assert(stripNonAlphaNum("$$#%@frank-cullen%^*") == "frank-cullen");
    assert(stripNonAlphaNum("$$#1234^*") == "1234");
    assert(stripNonAlphaNum("$$6-afraid-7*") == "6-afraid-7");
}

// testCreateHashMap()
// Purpose: Tests if the HashMap can be constructed
void testCreateHashMap(){
    HashMap<int, int> myHash;
}

// testHashInHash()
// Purpose: Tests the inHash function in the HashMap class.
void testHashInHash(){
    HashMap<std::string, int> testHash;
    testHash.insert("one", 1);
    testHash.insert("two", 2);
    assert(testHash.inHash("one"));
    assert(testHash.inHash("two"));
    assert(not testHash.inHash("three"));
}

// testHashInsertAndGet()
// Purpose: Tests the insert and get functions in the HashMap class.
void testHashInsertAndGet(){
    HashMap<int, int> map;
    map.insert(1, 5);
    assert(map.get(1) == 5);
}

// testHashSize()
// Purpose: Tests the size function in the HashMap class.
void testHashSize(){
    HashMap<int, int> map;
    map.insert(1, 5);
    map.insert(2, 6);
    map.insert(3, 7);
    assert(map.size() == 3);
}

// testHashAt()
// Purpose: Tests the at function in the HashMap class.
void testHashAt(){
    HashMap<int, int> map;
    map.insert(1, 5);
    map.insert(2, 6);
    map.insert(3, 7);
    assert(map.at(1) == 6);
}

// testDoubleHash()
// Purpose: Tests the HashMap class when created with a hash inside a hash.
void testDoubleHash(){
    HashMap<std::string, HashMap<std::string, int>> outmap;
    HashMap<std::string, int> inmap;
    inmap.insert("found", 5);
    outmap.insert("looking", inmap);
    assert(outmap.get("looking").get("found") == 5);
}

//testHashWStruct()
// Purpose: Tests the HashMap class by created a nested HashMap with a struct 
// as the value.
void testHashWStruct(){
    struct testStruct{
        int example;
        int test;
    };
    HashMap<std::string, HashMap<std::string, testStruct>> gerpHash;
    HashMap<std::string, testStruct> dummyHash;
    testStruct newInstance{1, 2};
    dummyHash.insert("test", newInstance);
    gerpHash.insert("test", dummyHash);
    assert(gerpHash.get("test").get("test").example == 1);
    assert(gerpHash.get("test").get("test").test == 2);
}

// testInsertGet()
// Purpose: Tests the add to hash function in the wordHash class
void testInsertGet(){
    struct testStruct{
        int example;
        int test;
    };
    HashMap<std::string, HashMap<std::string, vector<testStruct>>> testHash;
    HashMap<std::string, vector<testStruct>> inhash;
    vector<testStruct> testv;
    vector<testStruct> testv2;
    testStruct tester{1, 1};
    testStruct tester2{2, 2};
    testv.push_back(tester);
    testv2.push_back(tester2);
    inhash.insert("found", testv);
    testHash.insert("looking", inhash);
    testHash.get("looking").insert("yes", testv2);
    assert(testHash.get("looking").inHash("yes"));
    assert(testHash.get("looking").get("yes").front().test == 2);
}

// testMoreInsertGet()
// Purpose: Further tests the insert and get functions in the HashMap class
void testMoreInsertGet(){
    // Create a nested hash map
    HashMap<std::string, HashMap<std::string, int>> nestedHashMap;

    // Inserting values into the nested hash map
    nestedHashMap.insert("Key1", HashMap<std::string, int>());
    nestedHashMap.get("Key1").insert("SubKey1", 100);
    nestedHashMap.get("Key1").insert("SubKey2", 200);

    nestedHashMap.insert("Key2", HashMap<std::string, int>());
    nestedHashMap.get("Key2").insert("SubKey3", 300);
    nestedHashMap.get("Key2").insert("SubKey4", 400);

    //assert
    assert(nestedHashMap.get("Key1").get("SubKey1") == 100);
    assert(nestedHashMap.get("Key2").get("SubKey4") == 400);
}



// testCreateWordHash()
// Purpose: Tests if the wordHash class can be constructed
void testCreateWordHash(){
    wordHash myHash("proj-gerp-test-dirs/tinyData");
}

// testPopulatePaths()
// Purpose: Tests if the treeTraversal function works to populate the paths 
//          vector in wordHash.
void testPopulatePaths(){
    wordHash myHash("proj-gerp-test-dirs/tinyData");
    myHash.fillHash();
    //test the paths vector against the results of FSTreeTraversal
    assert(myHash.paths[0] == "proj-gerp-test-dirs/tinyData/hello");
    assert(myHash.paths[2] == "proj-gerp-test-dirs/tinyData/a/found");
    assert(myHash.paths[5] == 
            "proj-gerp-test-dirs/tinyData/b/c/heyLookAtMe.txt");
}

// //testToLower()
// //Purpose: Tests the tolower function in wordHash
// void testToLower(){
//     wordHash myHash("proj-gerp-test-dirs/tinyData");
//     std::string upper = "YES";
//     std::string lower = myHash.toLower(upper);
//     assert(lower == upper);
// }




