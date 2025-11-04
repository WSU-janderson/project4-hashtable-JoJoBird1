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
 size_t index = hash<std::string>{} (key) % tCapacity;               // home bucket using built-in string hash
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;                          // next probe position

  HashTableBucket& bucket = table[pIndex];                          // grab reference to that bucket
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
 size_t index = hash<std::string>{}(key) % tCapacity;          // home bucket using built-in string hash
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;                    // next probe position
  HashTableBucket& bucket = table[pIndex];                    // grab reference to that bucket
// if condition to check if spot was never used
  if (bucket.isEmptySinceStart()) {
   return false;
  }
// if condition found key
  if (bucket.isNormal() && bucket.getKey() == key) {
   bucket.makeEar();                                       // mark as "empty after removal"
   count--;
   return true;
  }
 }
 return false;                                             // key not found
}

/**
 * Method: contains
 * Will return true if key is in table
 * Otherwise, will return false
*/
bool HashTable::contains(const string& key) const {
 size_t index = hash<std::string>{}(key) % tCapacity;                  // home bucket using built-in string hash
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + 1) % tCapacity;                             // next probe position
  const HashTableBucket& bucket = table[pIndex];                       // grab reference to that bucket
//if condition to check if spot was never used
  if (bucket.isEmptySinceStart()) {
   return false;
  }
// if condition found key
  if (bucket.isNormal() && bucket.getKey() == key) {
   return true;
  }
 }
 return false;                                              // key not found
}

/**
 *Method: get
* If the key is found in the table, find will return the value associated with
* that key. If the key is not in the table, find will return something called
* nullopt.
*/
std::optional<size_t> HashTable::get(const string& key) const {
 size_t index = hash<std::string>{}(key) % tCapacity;                // home bucket using built-in string hash
// for loop iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index +1) % tCapacity;                            // next probe position
  const HashTableBucket& bucket = table[pIndex];                     // grab reference to that bucket
// if condition to check if reached empty slot
  if (bucket.isEmptySinceStart()) {
   return std::nullopt;
  }
// if condition to check if key was found
  if (bucket.isNormal() && bucket.getKey() == key) {
   return bucket.getValue();                       // return value at specified key
  }
 }
 return std::nullopt;                              // key not found
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
 size_t index = hash<std::string>{}(key) % tCapacity;                // home bucket using built-in string hash
// for loop to iterate through hash
 for (size_t i = 0; i < tCapacity; i++) {
  size_t pIndex = (index + i) % tCapacity;                           // next probe position
  HashTableBucket& bucket = table[pIndex];                           // grab reference to that bucket
// if condition to check key found
  if (bucket.isNormal() && bucket.getKey() == key) {
   return bucket.getValue();                                        // return value at specified key
  }
 }
 throw runtime_error("Key not found");
}

/**
 * Method: keys
* returns a std::vector with all of the keys currently in the table
*/
std::vector<std::string> HashTable::keys() const {
 vector<string> allKeys;
// for loop
 for (const auto& bucket : table) {
// if condition
  if (bucket.isNormal()) {
   allKeys.push_back(bucket.getKey());
  }
 }
 return allKeys;                               // returns keys in table
}

/**
 * Method: alpha
 * returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity.
 The time complexity
* for this method must be O(1).
 */
double HashTable::alpha() const {
 return static_cast<double>(count) / static_cast<double>(tCapacity);
}

/**
 * Method: capacity
* returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/
size_t HashTable::capacity() const {
 return tCapacity;
}

/**
 * Method: size
* returns how many key-value pairs are in the hash table. The
* time complexity for this method must be O(1)
*/
size_t HashTable::size() const {
 return count;
}

/**
 * Method: resize
 * resizes the hash-table
 */
void HashTable::resize() {
 size_t newCapacity = tCapacity * 2;                // sets new capacity
 vector<HashTableBucket> newTable(newCapacity);     // creates new table with updated capacity
// for loop
 for (auto& bucket : table) {
  if (bucket.isNormal()) {                          // if condition for a key-value pair
   size_t index = hash<std::string>{}(bucket.getKey()) % newCapacity;     // new hash index on updated capacity
// for loop for linear probing
   for (size_t i = 0; i < newCapacity; i ++) {
    size_t pIndex = (index + i) % newCapacity;      // probe index calculation
// if condition to check if it's empty
    if (newTable[pIndex].isEmpty()) {
     newTable[pIndex].load(bucket.getKey(), bucket.getValue());      // inserts the key-value pair
     break;    // break to the next bucket
    }
   }
  }
 }
 table = move(newTable);        // replace old table with the new updated table
 tCapacity = newCapacity;           // updates the new capacity
}


/**
 * Method: operator
 * prints out hash-table
 */
ostream& operator<<(ostream& os, const HashTable& ht1) {
 // for loop iterate through table
 for (size_t i = 0; i < ht1.tCapacity; i++) {
  const HashTableBucket& bucket = ht1.table[i];
// if condition checks for a key-value pair
  if (bucket.isNormal()) {
   // print statement
   os << "Bucket " << i << ": " << bucket.getKey() << ", " << bucket.getValue() << endl;
  }
 }
 return os;        // return print statement
}

/**
 * Method: operator single bucket
 * prints out single bucket
 */
ostream& operator<<(ostream& os, const HashTableBucket& bucket) {
 // if condition check for a key-value pair
 if (bucket.isNormal()) {
  // print statement
  os << "< " << bucket.getKey() << ", " << bucket.getValue() << " >" << endl;
 }
 return os;      // return print statement
}
