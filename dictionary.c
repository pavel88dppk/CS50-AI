// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


const int N = 650;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *table[N];

//how many words were loaded to dictionary
int count = 0;


unsigned int hash(const char *word)
{
    unsigned int onechar = (tolower(word[0])+1 - 'a')*26;
    if (word[1] != 0)
    {
        onechar += (tolower(word[1]) + 1 - 'a');
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
        count ++;
        int x = hash(word);

        //memory for new word
        node *newword = malloc(sizeof(node));
        //insert words into table
        if (table[x] != NULL)
        {
            for (int i = 0; word[i]; i++)
            {
                newword->word[i] = word[i];
            }

            //insert node in the linked list
            newword->next = table[x];
            table[x] = newword;

        }
        else
        {
            table[x] = newword;

            //pass word from buffer to node
            for (int i = 0; word[i]; i++)
            {
                newword->word[i] = word[i];
            }

            newword->next = NULL;
        }

    }
    fclose(file);
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

    char tmpword[LENGTH + 1] = {'\0'};

    for (int i = 0; word[i]; i++)
    {
        tmpword[i] = tolower(word[i]);
    }
    int x = hash(tmpword);
    node *cursor = table[x];

    while(cursor != NULL)
    {
        for (int i = 0; i <= LENGTH; i++)
        {
            if (cursor->word[i] != tmpword[i])
            {
                break;
            }
            if (i == LENGTH)
            {
                return true;
            }
        }
        cursor = cursor->next;
    }
    return false;
}
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i = 0;
    while (i < N)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        i++;
    }
    return true;
}