/**
 * Name: Jordan Wilson
 * Project 4: Hashtable
 * File: HashTable.cpp
 */

#include <iostream>
#include <optional>
#include <stdexcept>
#include "HashTable.h"

using namespace std;


/**
 * Method: constructor
* Only a single constructor that takes an initial capacity for the table is
* necessary. If no capacity is given, it defaults to 8 initially
*/
HashTable::HashTable(size_t initCapacity)
 : tCapacity(initCapacity), count(0)
{
 table.resize(tCapacity);
}

/**
 * Method: insert
 * Checks if the new key-value pair being inserted into the table is a duplicate or not.
 * If there isn't a duplicate it will return true,
 * Otherwise if a duplicate is found it'll return false.
*/
bool HashTable::insert(const std::string& key, const size_t& value) {
 if (alpha() >= 0.5) {
  resize();
 }
 size_t index = hash<std::string>{} (key) % tCapacity;
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;

  HashTableBucket& bucket = table[pIndex];
// duplicate key was found
  if (bucket.isNormal() && bucket.getKey() == key) {
   return false;
  }
// if condition for empty slot
  if (bucket.isEmpty()) {
   bucket.load(key, value);
   count++;
   return true;
  }
 }
 return false;
}

/**
 * Method: remove
 * If the key is found in the table it will erase the key-value pair from the table.
 * Marking a bucket as empty after removed.
*/
bool HashTable::remove(const std::string& key) {
 size_t index = hash<std::string>{}(key) % tCapacity;
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;
  HashTableBucket& bucket = table[pIndex];
// if condition to check if spot was never used
  if (bucket.isEmptySinceStart()) {
   return false;
  }
// if condition found key
  if (bucket.isNormal() && bucket.getKey() == key) {
   bucket.makeEar();
   count--;
   return true;
  }
 }
 return false;
}

/**
 * Method: contains
 * Will return true if key is in table
 * Otherwise, will return false
*/
bool HashTable::contains(const string& key) const {
 size_t index = hash<std::string>{}(key) % tCapacity;
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + 1) % tCapacity;
  const HashTableBucket& bucket = table[pIndex];
//if condition to check if spot was never used
  if (bucket.isEmptySinceStart()) {
   return false;
  }
// if condition found key
  if (bucket.isNormal() && bucket.getKey() == key) {
   return true;
  }
 }
 return false;
}

/**
 *Method: get
* If the key is found in the table, find will return the value associated with
* that key. If the key is not in the table, find will return something called
* nullopt.
*/
std::optional<size_t> HashTable::get(const string& key) const {
 size_t index = hash<std::string>{}(key) % tCapacity;
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index +1) % tCapacity;
  const HashTableBucket& bucket = table[pIndex];
// if condition to check if spot was never used
  if (bucket.isEmptySinceStart()) {
   return std::nullopt;
  }
// if condition to check if key was found
  if (bucket.isNormal() && bucket.getKey() == key) {
   return bucket.getValue();
  }
 }
 return std::nullopt;
}

/**
 * Method: operator[]
 * returns a reference to the value associated with a given key

 If the key is not
* in the table, returning a valid reference is impossible. You may choose to
* throw an exception in this case, but for our implementation, the situation
* results in undefined behavior. Simply put, you do not need to address attempts
* to access keys not in the table inside the bracket operator method.
*/
size_t& HashTable::operator[](const string& key) {
 size_t index = hash<std::string>{}(key) % tCapacity;
// for loop to iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;
  HashTableBucket& bucket = table[pIndex];
// if condition to check key found
  if (bucket.isNormal() && bucket.getKey() == key) {
   return bucket.getValue();
  }
 }
 throw runtime_error("Key not found");
}

/**
 * Method: keys
* returns a std::vector with all of the keys currently in the table
*/
std::vector<std::string> HashTable::keys() const {

}

/**
* alpha returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity, which
* are size_t, to avoid size_teger division. You can cast a size_t num to a double
* in C++ like:
                  static_cast<double>(num)
 The time complexity
* for this method must be O(1).
 */
double HashTable::alpha() const {

}

/**
* capacity returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/
size_t HashTable::capacity() const {

}

/**
* The size method returns how many key-value pairs are in the hash table. The
* time complexity for this method must be O(1)
*/
size_t HashTable::size() const {

}

