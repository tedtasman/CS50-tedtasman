// Implements a dictionary's functionality
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"
// initialize word count
unsigned int count;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 99999;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word
    unsigned int index = hash(word);
    // initialize temp node
    node *tmp = table[index];
    // follow correct list until word matches
    while(tmp != NULL)
    {
        // if on the word
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        // update temp node
        tmp = tmp->next;
    }
    // word never matched
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int index;
    char input[strlen(word)];
    strcpy(input, word);
    // if less than 4 characters
    if(strlen(input) < 3)
    {
        index = toupper(input[0]) - 65;
    }
    else
    {
        unsigned int product = 1;
        for (int i = 0; i < 3; i++)
        {
            product = product * (toupper(input[i]) - 63) + 1;
        }
        index = (product % 100000);
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary
    FILE *file = fopen(dictionary, "r");
    // check that file opened
    if (file == NULL)
    {
        return false;
    }
    // initialize word
    char word[LENGTH + 1];
    // read words until none left
    while(fscanf(file, "%s", word) != EOF)
    {
        // allocate space for node
        node *n = malloc(sizeof(node));
        // check allocation success
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, word);
        // set next to NULL
        n->next = NULL;
        // use hash to find where to insert
        int index = hash(word);
        // insert node
        n->next = table[index];
        table[index] = n;
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //TODO
    // if there is any words
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // initialize freeing nodes
    node *cursor = table[0];
    // iterate over hash table
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor = table[i];
            //until cursor reaches the end
            while (cursor != NULL)
            {
                // tmp takes over pointer
                node *tmp = cursor;
                // cursor moves along
                cursor = cursor->next;
                // tmp is freed
                free(tmp);
            }
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
