// Implements a dictionary's functionality using a Hash function
// Cheyanna Graham
// Aug 2019

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // make new node
        int index = hash(word);
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->word, word);

        // Index == NULL
        if (!hashtable[index])
        {
            new_node->next = NULL;
        }
        // Index == NODE, ADD Node & Shift
        else
        {
            new_node->next = hashtable[index];
        }
        hashtable[index] = new_node;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int total = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i])
        {
            node *curr = hashtable[i];
            while (curr)
            {
                total ++;
                curr = curr->next;
            }
        }
    }
    return total;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *curr_node = hashtable[hash(word)];

    if (!curr_node)
    {
        return false;
    }

    int i = 0, word_len = strlen(word);

    while ( i < word_len)
    {
        // if the words don't match, move to the next node
        if (word_len != strlen(curr_node->word) || tolower(curr_node->word[i]) != tolower(word[i]))
        {
            i = 0;
            curr_node = curr_node->next;

            // no more nodes
            if(!curr_node)
            {
                return false;
            }
        }
        // the letters do match, compare next letter
        else
        {
            i++;
        }
    }
    return true;
}



// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i])
        {
            node *curr = hashtable[i];
            while (curr)
            {
                node *next = curr->next;
                free(curr);
                curr = next;
            }
        }
    }
    return true;
}
