// Implements a dictionary's functionality using tries and linked lists
// Cheyanna Graham
// August 14, 2019

// Headers
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Custom header
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents longest word
#define LENGTH 45

// Depth of trie pathways
#define TRIE_DEPTH 3

// Represents a node in a trie
typedef struct trie_node
{
    bool is_word;
    struct trie_node *children[N];
    struct list_node *list;
}
trie_node;

// Represents linked list node
typedef struct list_node
{
    char word[LENGTH + 1];
    struct list_node *next;
}
list_node;

// Function declarations
int hash(const char *str);
struct trie_node *init_tnode(void);
int del_dict(struct trie_node *n);
int count(struct trie_node *n);

// Represents a trie
struct trie_node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = init_tnode();

    // Malloc error
    if (!root)
    {
        return false;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");

    // Validate file
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
        // Create trie pathways
        struct trie_node *current_node = root;
        int i = 0, word_len = strlen(word), index;

        while (i < word_len && i < TRIE_DEPTH)
        {
            index = hash(&word[i]);

            // Child node exists
            if (current_node->children[index])
            {
                // Move to next node
                current_node = current_node->children[index];
            }
            // Child node is NULL
            else
            {
                // Make & initialize child node
                current_node->children[index] = init_tnode();

                // Malloc Error
                if (!current_node->children[index])
                {
                    unload();
                    return false;
                }

                // Move to child node
                current_node = current_node->children[index];
            }
            i++;

            // Check if at end of word
            if (i == word_len)
            {
                current_node->is_word = true;
            }
        }

        // Add words longer than 3 chars to linked list at end of current trie path
        if (word_len > TRIE_DEPTH)
        {
            // Init new list node
            struct list_node *new_lnode = malloc(sizeof(list_node));
            strcpy(new_lnode->word, word);

            // Point current node to new node
            new_lnode->next = current_node->list;
            current_node->list = new_lnode;
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
    return count(root);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int word_len = strlen(word), i = 0;
    struct trie_node *curr_node = root;

    // Check trie for word
    while (i < TRIE_DEPTH && i < word_len)
    {
        // Check child node
        int index = hash(&word[i]);
        if (!curr_node->children[index])
        {
            return false;
        }

        // Move to next trie node
        curr_node = curr_node->children[index];
        i++;

        // Determine if word
        if (i == word_len && curr_node->is_word == true)
        {
            return true;
        }
    }

    // Check linked lists for word
    struct list_node *lnode = curr_node->list;

    // No linked list
    if (!lnode)
    {
        return false;
    }
    i = 0;

    while (i < word_len)
    {
        // Move to next node if word lengths or characters don't match
        if (word_len != strlen(lnode->word) || tolower(lnode->word[i]) != tolower(word[i]))
        {
            // Move to next node
            lnode = lnode->next;
            i = 0;

            // End of linked list
            if (!lnode)
            {
                return false;
            }
        }

        // Character matched, move to next
        else
        {
            i++;
        }
    }
    // All characters in word matched
    return true;
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

// Hash function
int hash(const char *str)
{
    // Check for apostrophe
    if (str[0] == 39)
    {
        return 26;
    }
    return tolower(str[0]) - 97;
}

// Create and initialize new trie node. Return node pointer.
struct trie_node *init_tnode(void)
{
    // Malloc space for new node and set default values
    struct trie_node *n = malloc(sizeof(trie_node));
    if (n == NULL)
    {
        return NULL;
    }
    n->is_word = false;
    n->list = NULL;
    for (int i = 0; i < N; i++)
    {
        n->children[i] = NULL;
    }
    return n;
}

// Recursively delete dictionary
int del_dict(struct trie_node *n)
{
    // Delete linked list nodes
    if (n->list)
    {
        struct list_node *curr_lnode = n->list;

        // Free current node and move to next
        while (curr_lnode)
        {
            struct list_node *next = curr_lnode->next;
            free(curr_lnode);
            curr_lnode = next;
        }
    }

    // Delete trie nodes
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
int count(struct trie_node *n)
{
    int total = (n->is_word == true) ? 1 : 0;

    // Count linked list nodes
    if (n->list)
    {
        struct list_node *lnode = n->list;

        // Add node to total and move to next
        while (lnode)
        {
            total++;
            lnode = lnode->next;
        }
    }

    // Recursively count words in trie
    for (int i = 0; i < N; i++)
    {
        if (n->children[i])
        {
            total += count(n->children[i]);
        }
    }
    return total;
}