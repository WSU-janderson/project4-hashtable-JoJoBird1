/**
 * Name: Jordan Wilson
 * Project 4: Hashtables
 * File: HashTableDebug.cpp
 *
 * Tests
 */
#include <iostream>
#include <optional>
#include "HashTable.h"
using namespace std;

int main() {
    // creates hash-table named ht1
    HashTable ht1;

    ht1.insert("Jordan", 42);
    ht1.insert("Herbert", 120);
    ht1.insert("Katie", 22);
    ht1.insert("Alfred", 87);
    ht1.insert("Bravo",7);

    cout << ht1 << endl;
    cout << "Size: " << ht1.size() << endl;
    cout << "Capacity: " << ht1.capacity() << endl;
    cout << "Alpha Load Factor: " << ht1.alpha() << endl;


    return 0;
}