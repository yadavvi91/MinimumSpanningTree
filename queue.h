#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct edge
{
    int from, to;
    float weight;
} edge;

typedef struct queue_node
{
    int value;
    edge *edges;
    struct queue_node *prev, *next;
} queue_node;

typedef struct queue
{
    struct queue_node *first;
    int size;
} queue;

typedef int boolean;
#define TRUE 1
#define FALSE 0

queue *queue_create();
void queue_add(queue *queue_inst, edge *edge_inst);
edge *queue_remove(queue *queue_inst);
boolean queue_is_empty(queue *queue_inst);
void queue_destroy(queue *queue_inst);

#endif // QUEUE_H_INCLUDED
