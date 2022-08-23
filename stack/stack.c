/*************************************************************
 * another : Noam Hadad
 * Stack data structure implementation
 *
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack
{
   size_t top;
   size_t capacity;
   size_t size_of_element;
   void *data;
};

stack_ty *StackCreate(size_t capacity, size_t size_of_element)
{
   stack_ty *stack = NULL;
   stack = malloc(sizeof(stack_ty));

   if (NULL == stack)
   {
      return NULL;
   }
   stack->data = malloc(capacity * size_of_element);

   if (NULL == stack->data)
   {
      free(stack);
      return NULL;
   }
   stack->top = 0;
   stack->capacity = capacity;
   stack->size_of_element = size_of_element;

   return stack;
}

void StackDestroy(stack_ty *ptr)
{
   assert(NULL != ptr);
   free(ptr->data);
   free(ptr);
}

void StackPush(stack_ty *ptr, void *element)
{
   void *free_stack = NULL;
   assert(NULL != ptr);
   assert(NULL != element);

   if (ptr->top == ptr->capacity)
   {
      assert(NULL);
   }
   assert(NULL != ptr);
   assert(NULL != element);

   free_stack = (char *)ptr->data + (ptr->top * ptr->size_of_element);

   memcpy(free_stack, element, ptr->size_of_element);

   ptr->top++;
}

void StackPop(stack_ty *ptr)
{
   assert(NULL != ptr);

   ptr->top--;
}

void *StackPeek(const stack_ty *ptr)
{
   void *source = NULL;

   assert(NULL != ptr);

   source = (char *)ptr->data + ((ptr->top - 1) * ptr->size_of_element);

   return source;
}

int StackIsEmpty(const stack_ty *ptr)
{
   assert(NULL != ptr);

   return (ptr->top == 0);
}

size_t StackSize(const stack_ty *stack)
{
   assert(NULL != stack);

   return stack->top;
}

size_t StackCapacity(const stack_ty *stack)
{
   assert(NULL != stack);

   return stack->capacity;
}
