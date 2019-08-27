#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;
    
    // Send address 
    swap(&x,&y);
    printf("x = %i\ny = %i\n", x,y);
}

void swap(int *a, int *b)
{
    // assign to t value pointed to by a
    int t = *a;
    // assign value pointed to by a to value pointed to by b
    *a = *b;
    // assign value pointed to by b(not b(pointer) itself)
    // the value of t
    *b = t;
}