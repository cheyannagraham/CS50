// Guess password by brute force
// June 20, 2019
// Cheyanna Graham


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>

// Function Declarations;
int set_index(int index, char key[]);
int test_hash(string key);


// Global Variable
const string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int alpha_length = strlen(alpha);
string hash;
char salt[2];
bool match = false;


int main(int argc, string argv[])
{
    
    if (argc == 2)
    {   
        hash = argv[1];
        salt[0] = hash[0];
        salt[1] = hash[1];
        int permut_idx = 0;
        char key[10];
        
        while (!match)
        {
            set_index(permut_idx, key);
            if (!match)
            {
                // Match not found, increase length of key
                permut_idx++;
                
                // Password max 5 characters (0 - 4)
                if (permut_idx > 4)
                {
                    return 0;
                }
            }
        }
        return 0;
    }
    else
    {
        printf("Invalid Argument. \n");
        return 1;
    }
}

// Recursively permutate previous indices
int set_index(int index, char key[])
{
    // Break recursive cyle if match found
    if (match)
    {
        return 0;
    }
    else
    {
        
        for (int i = 0; i < alpha_length; i++)
        {
            key[index] = alpha[i];
        
            // Change previous index
            if (index > 0)
            {
                set_index(index - 1, key);
            }
            else
            {
                test_hash(key);
            }
        }
        return 0;
    }
}

// Test key against user hash
int test_hash(string key)
{
    int hash_len = strlen(hash);
    string hash2 = crypt(key, salt);
    
    for (int i = 0; i < hash_len; i++)
    {
        if (hash2[i] != hash[i])
        {
            return 1;
        }
    }
    match = true;
    printf("%s\n", key);
    return 0;
}