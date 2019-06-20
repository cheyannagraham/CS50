// Print a right aligned mario pyramid using the height given by user
// Cheyanna Graham
// January 26,2019

   
#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int height);

int main(void)
{
    int height = get_height();    
    print_pyramid(height);
}

// Prompt user for height and validate
int get_height(void)
{    
    int height;
    
    do
    {
        height = get_int("Please enter a nondecimal number between 1 and 8.\n");
    }
    while (height < 1 || height > 8);
    
    return height;
}

// Print hashes and space for pyramid
void print_pyramid(height) 
{
    for (int i = 1; i <= height; i++)
    {
        // Print spaces before hashes
        for (int k = height - i; k > 0; k--)
        {
            printf(" ");
        }
        
        // Print hash
        for (int j = i; j > 0; j --)
        {
            printf("#");
        }
        printf("\n");
    }
}
