/*************************************************************
 * another : Noam Hadad
 * Stack data structure API
 *
 *************************************************************/


#ifndef STACK_H
#define STACK_H

typedef struct stack stack_ty;

stack_ty *StackCreate(size_t capacity, size_t size_of_element); 

void StackDestroy(stack_ty *ptr);

void StackPush(stack_ty* ptr, void *element);

void StackPop(stack_ty* ptr);

void *StackPeek(const stack_ty* ptr);

int StackIsEmpty(const stack_ty* ptr);

size_t StackSize(const stack_ty *stack);

size_t StackCapacity(const stack_ty *stack);

#endif /* STACK_H */










