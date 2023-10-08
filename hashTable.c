#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Define a structure for a key-value pair
struct KeyValue {
    char* key;
    int value;
    struct KeyValue* next;
};

// Define the hash table structure
struct HashTable {
    struct KeyValue* table[TABLE_SIZE];
};

// Function to create a new key-value pair
struct KeyValue* createKeyValue(const char* key, int value) {
    struct KeyValue* newPair = (struct KeyValue*)malloc(sizeof(struct KeyValue));
    newPair->key = strdup(key);
    newPair->value = value;
    newPair->next = NULL;
    return newPair;
}

// Function to compute the hash value for a given key
int hash(const char* key) {
    int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable* ht, const char* key, int value) {
    int index = hash(key);
    struct KeyValue* newPair = createKeyValue(key, value);
    
    // Insert at the beginning of the linked list at the computed index
    newPair->next = ht->table[index];
    ht->table[index] = newPair;
}

// Function to retrieve the value associated with a key
int get(struct HashTable* ht, const char* key) {
    int index = hash(key);
    struct KeyValue* current = ht->table[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    // Key not found
    return -1;
}

int main() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    
    // Insert some key-value pairs
    insert(ht, "apple", 10);
    insert(ht, "banana", 20);
    insert(ht, "cherry", 30);
    
    // Retrieve values
    printf("Value for 'apple': %d\n", get(ht, "apple"));
    printf("Value for 'banana': %d\n", get(ht, "banana"));
    printf("Value for 'cherry': %d\n", get(ht, "cherry"));
    
    // Clean up memory
    free(ht);
    
    return 0;
}
