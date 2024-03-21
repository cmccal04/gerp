/*
 *  HashMap.cpp
 *  Cullen McCaleb & Frank Li
 *  12/06
 *
 *  CS 15 Project 4 Gerp
 *
 *  File Purpose:
 *  This file contains the definitions and implementation for a HashMap class.
 *  This HashMap class creates a hash map data structure for use in the gerp
 *  project. The hash map is created using a vector, and handles collisions
 *  using another vector for chainging. It also dynamically resizes.
 * 
 *  This class offers an insert function, two get funciions, an inHash 
 *  function, an at function, and a size function to interact with the 
 *  hash map. 
 * 
 * NOTES: There are two get functions, one for constant values and the other 
 *        for non-constant values.
 * 
 *        HashMap is in one file, and not split into a .h and .cpp file, since
 *        it requires the use of a template.
 *
 */

#ifndef _HASH_MAP_
#define _HASH_MAP_

#include <iostream>
#include <vector>
#include <list>
#include <functional>

//use a template for the HashMap class
template <typename K, typename V>
class HashMap {
public:
    /* HashMap()
    * Purpose: Constructor for HashMap to make the size of the map 1.
    * Input: Nothing
    * Return: Nothing
    * */
    HashMap(){
        map.resize(1);
        numElements = 0;
        capacity = 1;
    }

    /* insert()
    * Purpose: Insert key-value pair into the map.
    * Input: a const reference to a key, and a const reference to a value
    * Return: Nothing
    */
    void insert(const K& key, const V& value) {
        numElements++;

        //convert numElements to a double, and check if resizing is necessary
        if((static_cast<double>(numElements) / map.size()) > 0.75){
            resize();
        }

        //create hash index for the key
        int index = hash(key);
        //create the new node
        Node newWord{key, value};

        //go through the value vector for the given key's index
        for (size_t i = 0; i<map[index].size(); i++) {
            //if the key already exists, update its value
            if (map[index][i].key == key) {
                map[index][i].value = value;
                return;
            }
        }

        // Add the new node to the hashMap
        map[index].push_back(newWord);
    }
    
    /* get()
    * Purpose: Get a non-constant value from a given key.
    * Input: A constant reference to a key.
    * Return: A reference to the value.
    */
    V& get(const K& key) {
        //default-initialized value for V
        static V default_value = V{};

        //create hash index for the key
        int index = hash(key);

        //go through the value vector for the given key's index
        for (size_t i = 0; i<map[index].size(); i++) {
            //if the key already exists, return its value
            if (map[index][i].key == key) {
                return map[index][i].value;
            }
        }
        //key not found, return a null V
        return default_value;
    }

    /* get()
    * Purpose: Get a constant value from a given key.
    * Input: A constant reference to a key.
    * Return: A reference to the value.
    */
    const V& get(const K& key) const {
        //default-initialized value for V
        static V default_value = V{};

        //create hash index for the key
        int index = hash(key);

        //go through the value vector for the given key's index
        for (size_t i = 0; i<map[index].size(); i++) {
            //if the key already exists, return its value
            if (map[index][i].key == key) {
                return map[index][i].value;
            }
        }
        //key not found, return a null V
        return default_value;
    }

    /* at()
    * Purpose: Return the value at a given index of the hash map.
    * Input: An index of type size_t
    * Return: A reference to the value, of the type of the value.
    */
    const V& at(size_t index) const{
        size_t count = 0;
        //loop through the each node in the map until you reach the index
        for (size_t i = 0; i < map.size(); ++i) {
            for (size_t j = 0; j < map[i].size(); ++j) {
                if (count == index) {
                    return map[i][j].value;
                }
                count++;
            }
        }

        throw std::out_of_range("Index out of bounds");
    }

    /* inHash()
    * Purpose: Find out if the value is in the hashmap or not.
    * Input: A constant reference to a key
    * Return: A boolean representing if the key is in the hashmap.
    */
    bool inHash(const K& key) const{
        //create hash index for the key
        int index = hash(key);
        //go through the value vector for the given key's index
        for (size_t i = 0; i<map[index].size(); i++) {
            //if the key already exists, return its value
            if (map[index][i].key == key) {
                return true;
            }
        }
        // Key not found, return a null V
        return false;
    }

    /* size()
    * Purpose: Returns the size of the hashmap
    * Input: Nothing
    * Return: An int representing the number of elements
    */
    int size() {
        return numElements;
    }

private:

    //node to contain key-value pairs
    struct Node {
        K key;
        V value;
    };

    //ints to keep track of the capacity and elements of the map
    int capacity;
    int numElements;

    //vector of a vector of values (the second vector is for chaining)
    std::vector<std::vector<Node>> map;

    //hash function for the keys
    std::hash<K> hasher;

    /* hash()
    * Purpose: Gets an index for the key
    * Input: A reference to a key.
    * Return: An int representing the index
    */
    int hash(const K& key) const {
        return hasher(key) % map.size();
    }

    /* resize()
    * Purpose: Resizes the hash map if the capacity is too small
    * Input: Nothing.
    * Return: Nothing.
    */
    void resize(){
        //changes capacity to a big enough amount
        int newCapacity = capacity*2 + 2;

        std::vector<std::vector<Node>> newMap;
        newMap.resize(newCapacity);

        for(int i = 0; i<capacity; i++){
            for(size_t j = 0; j<map[i].size(); j++){
                //create a new hash index for each key, and insert the key
                //into the new index
                int index = hasher(map[i][j].key) % newCapacity;
                newMap[index].push_back(map[i][j]);
            }
        }
        //put the new data into the old map
        map = newMap;
        capacity = newCapacity;
    }
};

#endif




