#include <stdio.h>

int main(void)
{
    char s[] = "ayesha";
    char *t = "chey";
    char *u = t;
    
    printf("\nAddress where array s begins\n");
    printf("%p\n", s);
    
    printf("\nAddress of array s\n");
    printf("%p\n", &s);
    
    printf("s = %s\n", s);
    
    printf("\nAddress of t\n");
    printf("%p\n", &t);
    
    printf("\nAddress in t\n");
    printf("%p\n", t);
    
    printf("char *t = %s\n", t);
    
    printf("\nAddress in u\n");
    printf("%p\n",u);
    
    printf("\nAddress of u\n");
    printf("%p\n",&u);

    printf("char *u = t\n");
}