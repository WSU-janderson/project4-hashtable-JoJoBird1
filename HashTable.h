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
// private variables
private:
    string key;
    size_t value;
    BucketType type;

// public variables
public:

// default constructor
    HashTableBucket() : key(" "), value(0), type(BucketType::ESS) {

    }

// parameterized constructor
    HashTableBucket(const std::string& k, const size_t& v)
        : key(k), value(v), type(BucketType::NORMAL) {

    }

    void load(const std:: string& k, const size_t& v) {
        key = key;
        value = value;
        type = BucketType::NORMAL;
    }

    bool isEmpty() const {
        return type == BucketType::ESS || type == BucketType::EAR;
    }

// getters
    string& getKey() const;
    size_t getValue() const;

// setters
    void makeNormal() {
        type = BucketType::NORMAL;
    }

    void makeEss () {
        type = BucketType::ESS;
    }

    void makeEar () {
        type = BucketType::EAR;
    }

// method to check if empty since start
    bool isEmptySinceStart () {
       return type == BucketType::ESS;
    }

// method to check if empty after removal
    bool isEmptyAfterRemove () {
        return type == BucketType::EAR;
    }

// friend output operator
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);
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

// friend output operator
    friend ostream& operator<<(ostream& os, const HashTable& ht);
};

#endif