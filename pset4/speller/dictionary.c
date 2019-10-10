/**
 * PSet 4a - Speller - Hashtable
 * Written by Sudipto Ghosh for CS50
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// represents number of buckets in hashtable
#define N 60000

// declaration of a node of hashtable
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// declaration for the hashtable
node *hashtable[N];

// counter for number of words in dictionary
unsigned long count = 0;

// hashes word to a number to minimize collision
unsigned int hash(const char *word)
{
    // folding hash function
    unsigned int hash = 256;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ (word[i] | 0x20);
    }
    return hash % N;
}

// loads dictionary into memory returning true if successful else false
bool load(const char *dictionary)
{
    // initialize hashtable
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // attempt to open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        unload();
        return false;
    }

    // insert words into hashtable
    for (char word[LENGTH + 1];
         fscanf(file, "%s", word) != EOF;
         count++)
    {
        // extract each word and calculate hash
        unsigned int hashed = hash(word);

        // construct a node
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->next = NULL;

        // handle collisions
        if (hashtable[hashed])
        {
            n->next = hashtable[hashed];
        }
        hashtable[hashed] = n;
    }

    // close dictionary after loading to hashtable
    fclose(file);

    // indicate successful loading of dictionary
    return true;
}

// returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// returns true if word is in dictionary else false
bool check(const char *word)
{
    // convert the word to lowercase
    char temp[LENGTH + 1] = {'\0'};
    for (int i = 0; word[i] != '\0'; i++)
    {
        temp[i] = tolower(word[i]);
    }

    // iterate over nodes of the linked list stored in the
    // array as specified by the first letter of the word
    for (node *n = hashtable[hash(word)]; n; n = n->next)
    {
        // check if the word is identical to the
        // information stored in the current node
        if (!strcmp(n->word, temp))
        {
            // indicate word is valid
            return true;
        }
    }

    // reject word if not in the list
    return false;
}

// unloads dictionary from memory returning true if successful else false
bool unload(void)
{
    // iterate over all buckets of hashtable
    for (int i = 0; i < N; i++)
    {
        // free memory allocated to each node
        for (node *list = hashtable[i]; list;)
        {
            node *temp = list->next;
            free(list);
            list = temp;
        }
    }
    return true;
}
