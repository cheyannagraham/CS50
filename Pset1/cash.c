// Print the least amount of coins needed to equal the correct change
// Cheyanna Graham
// January 27, 2019

#include <stdio.h>
#include <math.h>
#include <cs50.h>


float get_change(void);
int calc_change(float change);

int main(void)
{
    float change = get_change();
    printf("%i\n", calc_change(change));
}

// Ask user for amount owed
float get_change(void)
{
    float change;
    
    do
    {
        change = get_float("Please enter the amount of change owed.\n");
    }
    while (change <= 0);
    
    return change;
}

// Calculate the minimun number of coins using a greedy algorithm
int calc_change(float change)
{
    int coins = 0;
    
    while (round(change * 100) / 100 >= 0.25) 
    {
        change -= 0.25;
        coins ++;
    } 

    while (round(change * 100) / 100 >= 0.10) 
    {
        change -= 0.10;
        coins ++;
    }   

    while (round(change * 100) / 100 >= 0.05) 
    {
        change -= 0.05;
        coins ++;
    }

    while (round(change * 100) / 100 >= 0.01)
    {
        change -= 0.01;
        coins ++;
    }
    
    return coins;    
}
