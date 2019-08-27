#include <stdio.h>

int main(void)
{
    // no conversion error b/c 'strings' or 
    // array of characters returns a pointer
    // whereas ints return values?
    // char *s = "chey";
    // printf("%s\n",s);
    
    
    // Pointers point to addresses, not values!
    // int *x = 6; wrong!
    
    int x = 6;
    // Have to explicitly assign address of variable
    int *y = &x;

    // var x is assigned value 6; y points to x
    printf("%i, %i\n", x, *y);
    x = 3;
    printf("%i, %i\n", x, *y);
    *y = 8;
    printf("%i, %i\n", x, *y);
}