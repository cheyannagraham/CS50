#include <stdio.h>

int main(void)
{
    // int x;
    // printf("Enter value\n");
    // // Store input int at address of x
    // scanf("%i", &x);
    // printf("%i\n", x);
    
    // *s w/o initializaiton on reserves space for pointer variable,
    // not what it would point to. So it returns null
    // char *s = NULL;
    // printf("Enter string\n");
    // scanf("%s", s);
    // printf("%s\n", s);
    
    // s[n] Array of characters reserves space for 'string'
    char s[3];
    printf("Enter string\n");
    scanf("%s", s);
    printf("%s\n", s);
    
    
}