/*************************************************************
 * another : Noam Hadad
 * Stack data structure implementation
 *
 *************************************************************/

#include <stdio.h>
#include "stack.h"

/************************* #define ***************************/

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n\n", name, actual == expected ? GREEN "Pass" WHITE : RED "Fail" WHITE)

#define SIZE 50

/*************************** main ******************************/

int main(void)
{
    size_t i = 0;

    stack_ty *stack = StackCreate(SIZE, sizeof(int));

    printf(CYAN "\tTest Stack\n\n" WHITE);

    TEST("StackCreate(5)", (stack ? 1 : 0), 1);

    TEST("StackIsEmpty(stack)", StackIsEmpty(stack), 1);

    for (i = 0; i < SIZE; i++)
    {
        StackPush(stack, &i);
    }

    printf("StackSize = %ld\n", StackSize(stack));

    for (i = 0; i < SIZE; i++)
    {
        printf("StackPeek = %d\n", *((int *)StackPeek(stack)));
        
        StackPop(stack);

    }
    printf("StackSize = %ld\n", StackSize(stack));

    StackDestroy(stack);

    printf(CYAN"\tEnd Test Stack\n\n"WHITE); 

    return 0;
}
