#include <stdio.h>

int swap(int a, int b);

int main(void)
{
    int *x;
    // printf("%d",*x);
    
    int y;
    // printf("%i", y);
    
    char *s = "a";
    
    int i = 0;
    
    while (1)
    {
        printf("((%i))", i);
        
        /* This line does not cause a 
        seg fault because it only reads
        the addresses outside of allocated
        memory, not access the values stored
        there */
        printf("%p", &s[i]);
        
        /* This line causes seg fault because it
        accesses values outside of allowed
        (allocated memory space) */
        printf("%c", s[i]);
        i++;
    }
}