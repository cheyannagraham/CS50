// Solve collatz using recursion
// Cheyanna Graham
// July 4, 2019

#include <stdio.h>


int collatz(int n);

int main()
{
    int x;
    printf("Enter integer\n");
    scanf("%i", &x);
    printf("%i\n", collatz(x));
}

int collatz(int n)
{
    // Base condition
    if (n == 1)
        return 0;
    
    // Recursive even condtion
    if (n % 2 == 0)
        return 1 + collatz(n / 2);
    
    // Recursive odd condtion
    return 1 + collatz(3 * n + 1);
}