// enee140_lookup.c

#include "enee140_hashtable.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LINE 1000


int main(int argc, char *argv[]){

    int choice, value;
    int lineno;
    char word[MAX_STRING], line[MAX_LINE];
    FILE *file;


    if(argc < 2){
        fprintf(stderr, "Usage: %s filename \n", argv[0]);
        return -1;
    }

    file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Could not open the %s file.\n",argv[1]);
        exit(-1);
    }

    hash_initialize();

    // Read file line-by-line
    lineno = 1;
    while (fgets(line, MAX_LINE, file) != NULL) {
        const char* pos = line;
        while (next_word(pos, word, MAX_STRING)) {
            if (strlen(word) > 1 || (strlen(word) == 1 && (word[0] == 'a' || word[0] == 'i'))) { //exclude single letter words that are not 'i' or 'a'
                value = hash_get(word);
                value++;
                hash_put(word, value);
            }
            pos += strlen(word);
            while (*pos != '\0' && (isspace(*pos) || ispunct(*pos))) {
                pos++;
            }
        }
        lineno++;
    }


    printf("\nWelcome to the ENEE140 word lookup program!\n");
    printf("1. Print hash table statistics\n");
    printf("2. Look up a word\n");
    printf("3. Exit\n");
    printf("4. Remove a key-value\n");

    printf("\nEnter your choice (1-4):");
    choice = get_option(choice);


    if(choice == 1){
    hash_load_factor();
        printf("Maximum length of a collision chain: %d\n", get_max_chain_length());
        printf("Average length of a collision chain: %.2f\n", get_avg_chain_length());
    }
    if(choice == 2){
        printf("Enter a word:");
        scanf("%s", word);

        lowercase_string(word); //convert user input to lowercase since words stored in hashtable are lowercase

        int frequency = hash_lookup(word);
        if (frequency > 0) {
            printf("\"%s\" appears %d times in the input.\n", word, frequency);
        } else {
            printf("\"%s\" does not appear in the input.\n", word);
        }
    }
    if(choice == 3){
    exit(0);
    }
    if (choice == 4) {
        printf("Enter a word to remove:");
        while (getchar() != '\n');
        scanf("%s", word);

        lowercase_string(word); //convert user input to lowercase since words stored in hashtable are lowercase

        int removed = hash_remove(word);
        if (removed) {
            printf("\"%s\" was successfully removed from the hash table.\n", word);
        } else {
            printf("\"%s\" was not found in the hash table.\n", word);
        }
    }
}



