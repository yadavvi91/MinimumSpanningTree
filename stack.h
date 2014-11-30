#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stack_node
{
    int value;
    struct stack_node *prev;
} stack_node;

typedef struct stack
{
    int size;
    stack_node *top;
} stack;

typedef int boolean;

#define TRUE 1
#define FALSE 0
#define NMAX 1000

stack* stack_create();
void stack_push(stack *stack_inst, int value);
int stack_pop(stack *stack_inst);
boolean stack_is_empty(stack *stack_inst);
void stack_destroy(stack *stack_inst);

#endif // STACK_H_INCLUDED
