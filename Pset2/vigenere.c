// Encrypt plaintext using Vigenere's Cipher
// Cheyanna Graham
// 06/14/2019

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string key);


int main(int argc, string argv[])
{
    if (argc == 2) 
    {
        string key = argv[1];
        
        // Reject invalid key
        if (!valid(key))
        {
            return 1;
        }
        
        string p_text = get_string("plaintext: ");
        int plength = strlen(p_text);
        int klength = strlen(key);
        
        printf("ciphertext: ");
        
        for (int i = 0, j = 0; i < plength; i++) 
        {
            // Restart key
            if (j == klength) 
            {
                j = 0;
            }
            
            int shift = toupper(key[j]) - 65;
            int p_char = p_text[i];
                       
            // Rotate Uppercase letters
            if (isupper(p_char)) 
            {
                int ciph = p_char + shift;
                if (ciph > 90)
                {
                    ciph = 64 + (ciph - 90);
                }
                printf("%c", ciph);
                j++;
            }
            
            // Rotate Lowercase letters
            else if (islower(p_char)) 
            {
                int ciph = p_char + shift;
                if (ciph > 122)
                {
                    ciph = 96 + (ciph - 122);
                }
                printf("%c", ciph);
                j++;                
            }
            
            // Print non-alphabetic characters
            else
            {
                printf("%c", p_char);
            }
        }
        printf("\n");
    }
    else 
    {
        return 1;
    }
}

// Validate key
bool valid(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        // Reject key if it contains non-alpha characters
        if (!(isupper(key[i]) || islower(key[i])))
        {
            return false;
        }
    }
    return true;
}

