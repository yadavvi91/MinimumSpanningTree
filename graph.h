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

adj_list *create_graph(int no_vert);
void add_edge(adj_list *adjacency_list, int from, int to, float weight);

#endif // GRAPH_H_INCLUDED
