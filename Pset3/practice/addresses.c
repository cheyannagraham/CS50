// show memory addresses
// 07/01/2019
// Cheyanna Graham

#include <stdio.h>
#include <string.h>

int main(void)
{
    char *name = "Cheyanna Graham";
    
    for (int i = 0, len = strlen(name); i <= len; i++)
    {
        printf("%c => %p\n", name[i], &name[i]);
    }
    
    // Address of string
    printf("%s => %p\n", name, name);
    
    // Address of pointer
    printf("char *name => %p\n", &name);
    
}