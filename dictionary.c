// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
int count = 0;
const unsigned int N = 26;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    
    node* cursor = malloc(sizeof(node)); 
    cursor = table[hash(word)]->next;
    while(cursor != NULL)
    {
        
        if (strcasecmp(cursor->word,word)==0)
        {
            return true;
        }

        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return (tolower(word[0]) - 'a');
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    FILE* file = fopen(dictionary, "r");
    {
        if (file == NULL)
        {
            return 1;
        }

        char word[LENGTH + 1];


        while (fscanf(file, "%s", word) != EOF)
        {
                node* newword = malloc(sizeof(node));
                if (newword == NULL)
                {
                    return 1;
                }
                strcpy (newword->word,word);
                count++;
                int x = hash(word);

                if (table[x] != NULL)
                {
                    newword->next = table[x];
                    table[x] = newword;
                }
                else
                {
                    table[x] = newword;
                    newword->next = NULL;
                }
            }

    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        // initiate a cursor
        node *cursor;

        // place the cursor inside the hashtable
        cursor = table[i];

        while (cursor)
        {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            return true;
        }

        // clean the hashtable
        table[i] = NULL;
    }

    return false;
}
