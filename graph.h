#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct node
{
    struct node *next;
    float weight;
    int to, from;
} node;

typedef struct bag
{
    node *first;
    int size;
} bag;

typedef struct adj_list
{
    int no_vert;
    int no_edges;
    bag **bags;
} adj_list;

adj_list *graph_create(int no_vert);
void graph_add_edge(adj_list *adjacency_list, int from, int to, float weight);
void graph_destroy(adj_list *adjacency_list);

#endif // GRAPH_H_INCLUDED
