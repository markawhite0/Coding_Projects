//enee140_hashtable.h
//Header file for a hash table library.

#ifndef ENEE140_HASHTABLE_H_
#define ENEE140_HASHTABLE_H_

#define NBUCKETS        50021   // prime number, for better hash uniformity
#define MAX_STRING      80

//Function prototypes for the public hashtable API.
void hash_initialize();

float hash_load_factor();

int hash_put(char key[], int value);

int hash_get(char key[]);

int hash_lookup(char key[]);

int next_word(const char line[], char word[], int size);

int get_option(int choice);

void lowercase_string(char word[]);

int get_max_chain_length();

float get_avg_chain_length();

int hash_remove(const char* key);

void print_hash();

#endif /* ENEE140_HASHTABLE_H_ */
