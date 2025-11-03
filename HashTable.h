/**
 * Name: Jordan Wilson
 * Project 4: Hashtable
 * File: HashTable.h
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <optional>
#include <string>
#include <vector>
using namespace std;

/**
 * Class - BucketType
 */
enum class BucketType {NORMAL, ESS, EAR};

/**
 * Class - HashTableBucket
 */
class HashTableBucket {
// default constructor
HashTableBucket();

// parameterized constructor
HashTableBucket(const std::string& key, const size_t& value);
};

/**
 * Class - HashTable
 */
class HashTable {
// Private Variables
private:
    vector<HashTableBucket> table;
    size_t tCapacity;
    size_t count;

// Public Variables
public:
    HashTable (size_t initCapacity = 8);
    bool insert(const std::string& key, const size_t& value);
    bool remove(const std::string& key);
    bool contains(const string& key) const;
    optional<size_t> get(const string& key) const;
    size_t& operator[](const string& key);
    vector<std::string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;


};

#endif