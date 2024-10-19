#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;  // Hash table to store the values
    int currentSize;         // Current size of the table
    int count;               // Number of elements in the table
    const int MAX_PROBING = 5; // Maximum probing limit

    // Helper function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i <= std::sqrt(n); i++) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n;
            n++;
        }
    }

    // Resize the table to at least double its previous size
    void resize() {
        int newSize = nextPrime(currentSize * 2);
        std::vector<int> newTable(newSize, -1); // New hash table initialized with -1

        for (int i = 0; i < currentSize; i++) {
            if (table[i] != -1) {
                int key = table[i];
                int index = key % newSize;
                int probingAttempts = 0;

                // Quadratic probing to insert the key into the new table
                while (newTable[index] != -1 && probingAttempts < MAX_PROBING) {
                    probingAttempts++;
                    index = (index + probingAttempts * probingAttempts) % newSize;
                }

                if (probingAttempts < MAX_PROBING) {
                    newTable[index] = key;
                }
            }
        }

        table = std::move(newTable);
        currentSize = newSize; // Update current size to the new size
    }

public:
    // Constructor to initialize the hash table
    HashTable(int size) : currentSize(nextPrime(size)), count(0) {
        table.resize(currentSize, -1); // Initialize the table with -1
    }

    // Function to insert a value into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (count >= currentSize / 2) { // Check load factor threshold
            resize();
        }

        int index = key % currentSize;
        int probingAttempts = 0;

        // Quadratic probing to insert the key
        while (table[index] != -1 && probingAttempts < MAX_PROBING) {
            probingAttempts++;
            index = (index + probingAttempts * probingAttempts) % currentSize;
        }

        if (probingAttempts < MAX_PROBING) {
            table[index] = key;
            count++;
        } else {
            std::cout << "Max probing limit reached!" << std::endl;
        }
    }

    // Function to remove a value from the hash table
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }

        table[index] = -1; // Mark the slot as empty
        count--;
    }

    // Function to search for a value in the hash table
    int search(int key) {
        int index = key % currentSize;
        int probingAttempts = 0;

        // Quadratic probing to find the key
        while (table[index] != -1 && probingAttempts < MAX_PROBING) {
            if (table[index] == key) {
                return index; // Key found
            }
            probingAttempts++;
            index = (index + probingAttempts * probingAttempts) % currentSize;
        }

        return -1; // Key not found
    }

    // Function to print the hash table
    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (table[i] != -1) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
};
