// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
const int N = 675;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *table[N];
unsigned int count = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    unsigned int onechar = (tolower(word[0]) - 'a')*25;
    
    if (word[1] != 0)
    {
        onechar += tolower((word[1]) - 'a');
    }
    
    return onechar;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        int position = hash(word);

        //memory for new word
        node *newword = malloc(sizeof(node));
        memset(newword->word, '\0', sizeof(word));
        count ++;


        //insert words into table
        if (table[position])
        {
            //pass word from buffer to node
            for (int i = 0; word[i]; i++)
            {
                newword->word[i] = word[i];
            }

            //insert node in the linked list
            newword->next = table[position];
            table[position] = newword;

        }
        else
        {
            table[position] = newword;

            //pass word from buffer to node
            for (int i = 0; word[i]; i++)
            {
                newword->word[i] = word[i];
            }

            newword->next = NULL;
        }

    }


    printf("Loaded %u words\n", count);
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int x = hash(word);
    node* cursor = table[x];
    
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == true)
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


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}