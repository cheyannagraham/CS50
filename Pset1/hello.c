// Get user input and Greet user
// Cheynna Graham
// 06/14/2019

#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <ctype.h>

string getName(void);
string capitalize(string name);

int main(void)
{
    string user_name = capitalize(getName());
    printf("\nHello %s!\n", user_name);
    sleep(1);
    printf("It's very nice to meet you! :)\n\n");
}

// Prompt user for name
string getName(void) 
{
    return get_string("\nHi! What is your name?\n");
}

// Capitilize the first letter of the name
string capitalize(string name)
{
    if (islower(name[0]))
    {    
        name[0] = toupper(name[0]);
    }
    return name;
}
