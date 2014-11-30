#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack.h"

/** \brief Create a new Stack.
 *
 * \return stack* - A new instance of stack.
 */
stack *stack_create()
{
    stack *stack_inst = (stack *) malloc(sizeof(stack));
    stack_inst->size = 0;
    stack_inst->top = NULL;
    return stack_inst;
}

/** \brief Push a new Node on the Stack.
 *
 * \param stack_inst stack* - Stack instance.
 * \param value int - Value of the new node.
 * \return void
 */
void stack_push(stack *stack_inst, int value)
{
    stack_node *stack_node_inst = (stack_node *) malloc(sizeof(stack_node));
    stack_node_inst->value = value;
    stack_node_inst->prev = stack_inst->top;
    stack_inst->top = stack_node_inst;
}

/** \brief Pop a Node from the Stack.
 *
 * \param stack_inst stack* - Stack instance.
 * \return int - Value of the removed/popped node.
 */
int stack_pop(stack *stack_inst)
{
    stack_node *stack_node_inst = stack_inst->top;
    int value = stack_node_inst->value;

    stack_inst->top = stack_inst->top->prev;
    free(stack_node_inst);
    return value;
}

/** \brief Check if the stack is empty.
 *
 * \param stack_inst stack* - Stack instance.
 * \return boolean - TRUE if stack is empty, FALSE otherwise.
 *
 */
boolean stack_is_empty(stack *stack_inst)
{
    return (stack_inst->top == NULL && stack_inst->size == 0) ? TRUE : FALSE;
}

/** \brief Free all the memory allocated for the stack.
 *
 * \param stack_inst stack* - Stack instance.
 * \return void
 */
void stack_destroy(stack *stack_inst)
{
    stack_node *stack_node_inst = stack_inst->top;
    stack_node *stack_node_inst_temp;

    while (stack_node_inst) {
        stack_node_inst_temp = stack_node_inst;
        stack_node_inst = stack_node_inst->prev;
        free(stack_node_inst_temp);
    }

    free(stack_inst);
}


















