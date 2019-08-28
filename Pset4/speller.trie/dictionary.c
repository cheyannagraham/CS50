// Implements a dictionary's functionality using a trie
// Cheyanna Graham
// Aug 2019

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"


// Represents number of children for each node in a trie
#define N 27


// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;


// Function declarations
int letter_map(char c);
int initialize_node(struct node *n[N]);
int del_dict(struct node *n);
int count(struct node *n);


// Represents a trie
node *root;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    initialize_node(root->children);

    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {

        struct node *current_node = root;
        int index;

        for (int i = 0, len = strlen(word); i < len; i++)
        {
            index = letter_map(word[i]);

            // letter available
            if (current_node->children[index])
            {
                // Move to next node
                current_node = current_node->children[index];

                // check if word
                if (i == len - 1)
                {
                    current_node->is_word = true;
                }
            }

            // Letter not available
            else
            {
                // add rest of nodes
                while ( i < len)
                {
                    current_node->children[index] = malloc(sizeof(node));

                    // Validate space
                    if (!current_node->children[index])
                    {
                        unload();
                        return false;
                    }
                    current_node->children[index]->is_word = false;
                    initialize_node(current_node->children[index]->children);

                    // Move to next node
                    current_node = current_node->children[index];

                    // check if word
                    if (i == len - 1)
                    {
                        current_node->is_word = true;
                    }

                    // Increment i and get next index
                    i++;
                    index = letter_map(word[i]);
                }
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (root)
    {
        return count(root);
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    struct node *letter_node = root;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        int index = letter_map(word[i]);

        // Check if letter is not null
        if (!letter_node->children[index])
        {
            return false;
        }

        letter_node = letter_node->children[index];
    }

    if (letter_node->is_word == true)
    {
        return true;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (del_dict(root))
    {
        return true;
    }
    return false;
}

// ********* My Functions ************************

// Map letter to number
int letter_map(char c)
{
    if (c == 39)
    {
        return 26;
    }
    return tolower(c) - 97;
}

// Nullify child pointers
int initialize_node(node *n[N])
{
    for (int i = 0; i < N; i++)
    {
        n[i] = NULL;
    }
    return 1;
}

// Recursively delete dictionary
int del_dict(struct node *n)
{
    for (int i = 0; i < N; i++)
    {
        if (n->children[i])
        {
            del_dict(n->children[i]);
        }
    }
    free(n);
    return 1;
}

// Recursively count words in dictionary
int count(struct node *n)
{
    int total = (n->is_word == true) ? 1 : 0;

    for (int i = 0; i < N; i++)
    {
        if (n->children[i])
        {
            total += count(n->children[i]);
        }
    }
    return total;
}