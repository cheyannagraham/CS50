#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    typedef struct person
    {
        int age;
        char *name;
        struct person *child;

    }
    person;

    struct person *chey = malloc(sizeof(person));

    //cannont be null, its int, not a pointer;??
    chey->age = 27;
    chey->name = NULL;
    chey->child = NULL;

    struct person *cg = chey;

    struct person *gray = NULL;

    struct person *kid = chey->child;

    kid = gray;

    // printf("%p %p \n", &chey->child, &cg->child);
    // printf("%p %p \n", chey->child, cg->child);
    // printf("%p %p \n", chey, cg);
    // printf("%p %p \n", gray, &gray);

    printf("%p\n", gray);

    struct person *gt = malloc(sizeof(person));
    if(!gray)
    {
        gray = gt;
    }

    printf("%p\n", gray);
    printf("%p\n", gt);
    kid = gray;


    // printf("%p %p \n", &chey->child, &cg->child);
    // printf("%p %p \n", chey->child, cg->child);
    // printf("%p %p \n", chey, cg);
    // printf("%p %p \n", gray, &gray);

    // printf("%p %p %p\n",&gt, &chey,&cg);
    // printf("%p %p %p\n",&(*gt), &(*chey),&(*cg));
    // printf("%p %p %p\n",gt, chey,cg);
    free(gt);
    free(chey);

        printf("%p \n", chey);
}