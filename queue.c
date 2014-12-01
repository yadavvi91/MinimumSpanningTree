#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "queue.h"

/** \brief Create an empty queue.
 *
 * \return queue* - The queue instance.
 */
queue *queue_create()
{
    queue *queue_inst = (queue *) malloc(sizeof(queue));
    queue_inst->first = NULL;
    queue_inst->size = 0;
    return queue_inst;
}

/** \brief Add an edge to the queue.
 *
 * \param queue_inst queue* - The queue instance.
 * \param edge_inst edge* - The edge to add to the queue.
 * \return void
 */
void queue_add(queue *queue_inst, edge *edge_inst)
{
    queue_node *queue_node_inst = (queue_node *) malloc(sizeof(queue_node));
    queue_node_inst->edges = edge_inst;
    queue_node_inst->prev = NULL;
    queue_node_inst->next = NULL;
    (queue_inst->size)++;

    if (queue_inst->first == NULL) {
        queue_inst->first = queue_node_inst;
        return;
    }

    queue_node *queue_node_inst_temp = queue_inst->first;
    while (queue_node_inst_temp->next != NULL) {
        queue_node_inst_temp = queue_node_inst_temp->next;
    }
    queue_node_inst->prev = queue_node_inst_temp;
    queue_node_inst_temp->next = queue_node_inst;
    return;
}

/** \brief Remove a node from the queue.
 *
 * \param queue_inst queue* - The queue instance.
 * \return edge* - The edge that was added in the queue.
 */
edge *queue_remove(queue *queue_inst)
{
    if (queue_inst->first == NULL)
        return NULL;

    queue_node *queue_node_inst = queue_inst->first;
    edge *edge_inst = (edge *) malloc(sizeof(edge));
    edge_inst->from = queue_node_inst->edges->from;
    edge_inst->to = queue_node_inst->edges->to;
    edge_inst->weight = queue_node_inst->edges->weight;

    queue_inst->first = queue_inst->first->next;
    if (queue_inst->first != NULL)
        queue_inst->first->prev = NULL;
    (queue_inst->size)--;

    free(queue_node_inst);
    return edge_inst;
}

/** \brief Check if the queue is empty.
 *
 * \param queue_inst queue* - The queue instance.
 * \return boolean - TRUE if queue is empty, FALSE otherwise.
 */
boolean queue_is_empty(queue *queue_inst)
{
    return (queue_inst->first == NULL) ? TRUE : FALSE;
    // OR
    // return (!queue_inst->size) ? TRUE : FALSE;
}

/** \brief Deallocate all the space of the queue.
 *
 * \param queue_inst queue* - The queue instance.
 * \return void
 */
void queue_destroy(queue *queue_inst)
{
    queue_node *queue_node_inst, *queue_node_inst_temp;
    queue_node_inst = queue_inst->first;

    while (queue_node_inst != NULL) {
        queue_node_inst_temp = queue_node_inst;
        queue_node_inst = queue_node_inst->next;
        free(queue_node_inst_temp);
    }

    free(queue_inst);
}
