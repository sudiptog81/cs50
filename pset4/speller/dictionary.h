// declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// function prototypes
bool load(const char *dictionary);
unsigned int size(void);
bool check(const char *word);
bool unload(void);

#endif // DICTIONARY_H
