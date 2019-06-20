// Encrypt messages using Ceasar's cipher
// Cheyanna Graham
// 06/12/2019

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int key = atoi(argv[1]) % 26; 
        string pt = get_string("plaintext: ");
        int length = strlen(pt);
        
        printf("ciphertext: ");
        
        for (int i = 0; i < length; i++) 
        {  
            int code = pt[i];
            
            // Rotate Uppercase letters
            if (code > 64 && code < 91)
            {
                int pc = pt[i] + key;
                
                // Wrap char back to a if pasts z
                if (pc > 90)
                {
                    int diff = pc - 90;
                    pc = 64 + diff;
                }
                printf("%c", pc);
            }
            
            // Rotate lowercase letters
            else if (code > 96 && code < 123)
            {
                int pc = pt[i] + key;
                
                // Wrap char back to a if pasts z
                if (pc > 122)
                {
                    int diff = pc - 122;
                    pc = 96 + diff;
                }
                printf("%c", pc);
            }
            
            // Print non alphabet characters
            else 
            {
                printf("%c", pt[i]);
            }
        }
        printf("\n");
    }
    else 
    {
        return 1;
    }
}
