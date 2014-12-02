#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

/** \brief Create a graph - an adjacency list - with given number of vertices.
 *
 * \param no_vert int - Number of vertices.
 * \return adj_list* - An Adjacency List of edges.
 */
adj_list *graph_create(int no_vert)
{
    bag *bag_of_vertex;

    adj_list *adjacency_list = (adj_list *) malloc(sizeof(adj_list));
    adjacency_list->bags = (bag **) malloc(no_vert * sizeof(bag*));
    adjacency_list->no_vert = no_vert;
    adjacency_list->no_edges = 0;

    for (int i = 0; i < no_vert; i++) {
        bag_of_vertex = (bag *) malloc(sizeof(bag));
        bag_of_vertex->size = 0;
        bag_of_vertex->first = NULL;

        adjacency_list->bags[i] = bag_of_vertex;
    }

    return adjacency_list;
}

/** \brief Add an edge to the given Adjacency List
 *
 * \param adjacency_list adj_list* - Adjacency List of the graph.
 * \param from int - from vertex.
 * \param to int - to vertex.
 * \param weight float - weight of the edge.
 * \return void
 */
void graph_add_edge(adj_list *adjacency_list, int from, int to, float weight)
{
    node *new_node, *prev_node;
    bag *bag_of_vertex;

    new_node = (node *) malloc(sizeof(node));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = NULL;

    bag_of_vertex = adjacency_list->bags[from];
    assert(bag_of_vertex != NULL);  // bag_of_vertex shouldn't be NULL.
                                    // It is intialized when adjacency_list is created.
    (adjacency_list->no_edges)++;
    (bag_of_vertex->size)++;

    if (bag_of_vertex->first == NULL) {
        bag_of_vertex->first = new_node;
        return;
    }

    prev_node = bag_of_vertex->first;
    assert(prev_node != NULL);  // prev_node shouldn't be NULL.

    while (prev_node->next != NULL) {
        prev_node = prev_node->next;
    }
    prev_node->next = new_node;
    return;
}

/** \brief Deallocate all the space of the graph.
 *
 * \param adjacency_list adj_list* - Adjacency List of the graph.
 * \return void
 */
void graph_destroy(adj_list *adjacency_list)
{
    bag *bag_of_vertex;
    node *node_of_vertex, *node_of_vertex_temp;

    if (adjacency_list == NULL)             return;

    for (int i = 0; i < adjacency_list->no_vert; i++) {
        bag_of_vertex = adjacency_list->bags[i];
        if (bag_of_vertex == NULL)          continue;

        node_of_vertex = bag_of_vertex->first;
        while (node_of_vertex != NULL) {
            node_of_vertex_temp = node_of_vertex;
            node_of_vertex = node_of_vertex->next;
            free(node_of_vertex_temp);
        }
        free(bag_of_vertex);
    }
    free(adjacency_list);
}
