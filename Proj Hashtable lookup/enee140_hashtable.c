//enee140_hashtable.c

#include "enee140_hashtable.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>


//Global variables
typedef struct _bucket {
    char key[MAX_STRING];
    int value;
} Bucket;

typedef Bucket Hashtable[NBUCKETS];

static Hashtable my_hash_table;
static int used_buckets;

static int max_chain_length = 0;
static int sum_chain_length = 0;


//Internal library functions
unsigned hash_function(char s[]) {
    unsigned hashval, i;
    for(hashval=0, i=0; s[i] != '\0'; i++) {
        hashval += s[i] + 31*hashval;
    }
    return hashval % NBUCKETS;
}


//Main hashtable API
float hash_load_factor(){
    int z;
    float load;
    float open_buckets = 0;
    float used_buckets = 0;

    for (z = 0; z < NBUCKETS; z++){
        if (my_hash_table[z].key[0] != '\0'){
            used_buckets++;
        }
        else{
            open_buckets++;
        }
    }
    if (open_buckets == 0) {
        printf("Hash table is full\n");
        return 1.0f;
    } else {
        load = used_buckets / NBUCKETS;
        printf("The load factor is %.2f\n", load);
        return 0.0f;
    }
}


int empty_checker(int index) {
    return my_hash_table[index].key[0] == '\0' && my_hash_table[index].key[1] == '\0';
}


void lowercase_string(char word[]) {
    for (int z = 0; word[z]; z++) {
        word[z] = tolower(word[z]);
    }
}


void hash_initialize() {
    int x;

    // Clear the content of the hash table
    for (x = 0; x < NBUCKETS; x++) {
        my_hash_table[x].key[0] = '\0';
        my_hash_table[x].value = 0;
    }
    used_buckets = 0;
    max_chain_length = 0;
    sum_chain_length = 0;
}


int hash_put(char key[], int value) {
    unsigned index = hash_function(key);
    int x, chain_length = 0;

    if (index == '\0') {
        return 0;
    }

    for (x = index; x < NBUCKETS; x++) {
        chain_length++;
        if (strcmp(my_hash_table[x].key, key) == 0) {
            my_hash_table[x].value = value;
            return 1;
        }
        if (empty_checker(x)) {
            strcpy(my_hash_table[x].key, key);
            my_hash_table[x].value = value;
            used_buckets++;
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
            sum_chain_length += chain_length;
            return 1;
        }
    }

    for (x = 0; x < index; x++) {
        chain_length++;
        if (strcmp(my_hash_table[x].key, key) == 0) {
            my_hash_table[x].value = value;
            return 1;
        }
        if (empty_checker(x)) {
            strcpy(my_hash_table[x].key, key);
            my_hash_table[x].value = value;
            used_buckets++;
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
            sum_chain_length += chain_length;
            return 1;
        }
    }
    return 0;
}


int hash_get(char key[]) {
    unsigned storage_value = hash_function(key);
    int x;

    if (my_hash_table[storage_value].key[0] == '\0') {
        return 0;
    }

    for (x = storage_value; x < NBUCKETS; x++) {
        if (strcmp(my_hash_table[x].key, key) == 0) {
            return my_hash_table[x].value;
        }
        if (my_hash_table[x].key[0] == '\0') {
            return 0;
        }
    }

    for (x = 0; x < storage_value; x++) {
        if (strcmp(my_hash_table[x].key, key) == 0) {
            return my_hash_table[x].value;
        }
        if (my_hash_table[x].key[0] == '\0') {
            return 0;
        }
    }
    return 0;
}


int hash_lookup(char key[]) {
    unsigned checker = hash_function(key);
    int x;

    if (checker == '\0') {
        return 0;
    }

    for (x = checker; x < NBUCKETS; x++) {
        if (strcmp(my_hash_table[x].key, key) == 0) {
            return my_hash_table[x].value;
        }
        if (empty_checker(x)) {
            return 0;
        }
    }

    for (x = 0; x < checker; x++) {
        if (strcmp(my_hash_table[x].key, key) == 0) {
            return my_hash_table[x].value;
        }
        if (empty_checker(x)) {
            return 0;
        }
    }

    return 0;
}


int next_word(const char line[], char word[], int size) {
    static int invocation_count = 0;
    int position = 0;
    int z;

    while(isspace(line[position]) || ispunct(line[position])) {
        position++; // skip over whitespace and punctuation at the beginning of the word
    }

    for(z = 0; z < size - 1 && line[position] != '\0'; z++) {
        if (!isalnum(line[position]) && line[position] != '\'' && !(line[position] == 's' && line[position - 1] == '\'')) {
            break; // stop at whitespace, punctuation, or invalid apostrophe
        }
        word[z] = tolower(line[position]); // convert to lowercase using tolower function
        position++;
    }

    word[z] = '\0'; // terminate the word array with '\0'

    invocation_count++;

    return (z > 0) ? 1 : 0; // return 1 if some characters were copied, 0 otherwise
}


int get_option(int choice){
    int num_;

    num_ = scanf("%d", &choice);
    while(num_ != 1 || !(choice >= 1 && choice <= 4)){
        printf("Sorry, that is not a valid option\n");
        printf("Enter your choice (1-4):");
        while (getchar() != '\n'); // clear input buffer
        num_ = scanf("%d", &choice);
    }
    return choice;
}



void print_hash(){
    FILE *out;
    out = fopen("try.txt", "w");

    for(int i = 0; i < NBUCKETS; i++){
        if(my_hash_table[i].value){
            fprintf(out, "Pos:%d, Key:%s, Value:%d\n", i, my_hash_table[i].key, my_hash_table[i].value);
        }
    }
}


int get_max_chain_length() {
    return max_chain_length;
}


float get_avg_chain_length() {
    if (used_buckets == 0) {
        return 0.0f;
    }
    return (float) sum_chain_length / used_buckets;
}


int hash_remove(const char* key) {
    unsigned hash_index = hash_function(key);
    int x;

    // Search for key in the collision chain
    for (x = hash_index; x < NBUCKETS; x++) {
        if (my_hash_table[x].key[0] != '\0' && strcmp(my_hash_table[x].key, key) == 0) {
            break;
        }
    }

    // Key not found in hash table
    if (x == NBUCKETS) {
        return 0;
    }

    // Remove the key-value pair from the hash table
    strcpy(my_hash_table[x].key, "");
    my_hash_table[x].value = 0;

    // Re-insert any key-value pairs that were displaced by the removal
    int next_index = (x + 1) % NBUCKETS;
    while (my_hash_table[next_index].key[0] != '\0') {

        const char* displaced_key = my_hash_table[next_index].key;
        int displaced_value = my_hash_table[next_index].value;

        strcpy(my_hash_table[next_index].key, "");
        my_hash_table[next_index].value = 0;

        hash_put(displaced_key, displaced_value);

        next_index = (next_index + 1) % NBUCKETS;
    }
    return 1;
}





