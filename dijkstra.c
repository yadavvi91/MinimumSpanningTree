#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "min_binary_heap.h"
#include "graph.h"
#include "dijkstra.h"
#include "queue.h"

void print_shortest_path(FILE *output, int start_vertex, adj_list *adjacency_list)
{
    int pq[NMAX + 1];
    float keys[NMAX];
    int size_of_heap = 0;

    float dist_to[NMAX];
    int edge_to[NMAX];

    for (int i = 0; i < adjacency_list->no_vert; i++) {
        dist_to[i] = INT_MAX;
        edge_to[i] = -1;
    }

    dist_to[start_vertex] = 0.0;
    edge_to[start_vertex] = 0;

    // Instead of inserting only the first element in the Priority Queue
    // we have to make the priority queue such that every element (with INT_MAX)
    // is there in the priority queue and then we change the priority depending
    // upon their distance from start_vertex.
    insert(start_vertex, &size_of_heap, dist_to[start_vertex], pq, keys);
    while (size_of_heap > 0) {
        int vertex = delete_min(&size_of_heap, pq, keys);
        // bag *bag_of_vertex = *(adjacency_list->bags + vertex * sizeof(bag *));
        bag *bag_of_vertex = adjacency_list->bags[vertex];
        node *node_of_vertex = bag_of_vertex->first;
        while (node_of_vertex) {
            relax(node_of_vertex, dist_to, edge_to, &size_of_heap, pq, keys);
            node_of_vertex = node_of_vertex->next;
        }
    }

    create_dijkstra_path(start_vertex, adjacency_list, dist_to, edge_to);
}

void relax(node *node_of_vertex, float dist_to[], int edge_to[], int *size_of_heap, int pq[], float keys[])
{
    int from, to;
    from = node_of_vertex->from;
    to = node_of_vertex->to;

    if (dist_to[to] > dist_to[from] + node_of_vertex->weight) {
        dist_to[to] = dist_to[from] + node_of_vertex->weight;
        edge_to[to] = from;
        insert(to, size_of_heap, dist_to[to], pq, keys);
    }
}

void create_dijkstra_path(int start_vertex, adj_list *adjacency_list, float dist_to[], int edge_to[])
{
    fprintf(stdout, "Something somethings\n");
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        if (dist_to[i] < INT_MAX) {
            fprintf(stdout, "%.2f\n", dist_to[i]);
        }
    }

    fprintf(stdout, "The edges are (In reverse order): \n");
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        int vertex = i;
        while (vertex != start_vertex) {
            fprintf(stdout, "%5d", vertex);
            vertex = edge_to[vertex];
        }
        fprintf(stdout, "%5d\n", vertex);
    }
}

/** \brief Create and print a minimum spanning tree.
 *
 * \param adjacency_list adj_list* - The Adjacency list of the graph.
 * \return void
 */
void minimum_spanning_tree(adj_list *adjacency_list)
{
    int pq[NMAX + 1];
    float keys[NMAX];
    int size_of_heap = 0;

    float node_key[NMAX];
    int node_parent[NMAX];

    for (int i = 0; i < adjacency_list->no_vert; i++) {
        node_key[i] = INT_MAX;
        node_parent[i] = -1;
        insert(i, &size_of_heap, node_key[i], pq, keys);
    }

    int start_vertex = 0;

    node_key[start_vertex] = 0.0;
    node_parent[start_vertex] = 0;
    decrease_key(start_vertex, &size_of_heap, node_key[start_vertex], pq, keys);

    while (size_of_heap > 0) {
        int vertex = delete_min(&size_of_heap, pq, keys);
        bag *bag_of_vertex = adjacency_list->bags[vertex];
        node *node_of_vertex = bag_of_vertex->first;
        while (node_of_vertex) {
            relax_min_span_tree(node_of_vertex, node_key, node_parent, &size_of_heap, pq, keys);
            node_of_vertex = node_of_vertex->next;
        }
    }

    // create_minimum_span_tree(start_vertex, adjacency_list, node_key, node_parent);
    create_minimum_span_tree_queue(adjacency_list, node_key, node_parent);
}

/** \brief Relax an edge in the minimum spanning tree.
 *
 * \param node_of_vertex node* - The actual edge.
 * \param node_key[] float - Length of all the edges in the graph.
 * \param node_parent[] int - Parents of vertices in an edge.
 * \param size_of_heap int*
 * \param pq[] int
 * \param keys[] float
 * \return void
 */
void relax_min_span_tree(node *node_of_vertex, float node_key[], int node_parent[], int *size_of_heap, int pq[], float keys[])
{
    int from, to;
    from = node_of_vertex->from;
    to = node_of_vertex->to;

    if (node_of_vertex->weight < node_key[to]) {
        node_key[to] = node_of_vertex->weight;
        node_parent[to] = from;
        decrease_key(to, size_of_heap, node_key[to], pq, keys);
    }
}

void create_minimum_span_tree(int start_vertex, adj_list *adjacency_list, float node_key[], int node_parent[])
{
    fprintf(stdout, "Node keys of every vertex\n");
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        if (node_key[i] < INT_MAX) {
            fprintf(stdout, "%.2f\n", node_key[i]);
        }
    }

    fprintf(stdout, "The edges are (In reverse order): \n");
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        int vertex = i;
        while (vertex != start_vertex) {
            fprintf(stdout, "%5d", vertex);
            vertex = node_parent[vertex];
        }
        fprintf(stdout, "%5d\n", vertex);
    }
}

/** \brief Create and print the minimum spanning tree.
 *
 * \param adjacency_list adj_list* - The Adjacency list of the graph.
 * \param node_key[] float - length of edges in the minimum spanning tree.
 * \param node_parent[] int - parents of a node in a given edge.
 * \return void
 */
void create_minimum_span_tree_queue(adj_list *adjacency_list, float node_key[], int node_parent[])
{
    queue *queue_inst = queue_create();

    for (int i = 0; i < adjacency_list->no_vert; i++) {
        edge *edge_inst = (edge *) malloc(sizeof(edge));
        edge_inst->from = node_parent[i];
        edge_inst->to = i;
        edge_inst->weight = node_key[i];

        queue_add(queue_inst, edge_inst);
    }

    fprintf(stdout, "The minimum spanning tree: \n");
    while (!queue_is_empty(queue_inst)) {
        edge *edge_inst = queue_remove(queue_inst);
        fprintf(stdout, "%2d ->%2d == %.2f\n", edge_inst->from, edge_inst->to, edge_inst->weight);
        free(edge_inst);
    }

    queue_destroy(queue_inst);
}
















