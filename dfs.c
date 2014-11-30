#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "stack.h"

/** \brief Perform a Depth-First Traversal of the given adjacency list.
 *
 * \param adjacency_list adj_list* - An Adjacency List of all the graph edges.
 * \return void
 */
void perform_dfs(FILE *output, adj_list *adjacency_list)
{
    int vertex = 0, no_of_vertex_left;
    boolean marked[NMAX] = {FALSE};
    stack *stack_inst = stack_init();
    int connected_graph[NMAX][2];
    int disjoint_set = 0;
    int stack_value, connected_graph_index = 0;

    no_of_vertex_left = adjacency_list->no_vert;

    while (no_of_vertex_left > 0) {
        for (int i = 0; i < adjacency_list->no_vert; i++) {
            if (marked[i] == FALSE) {
                stack_push(stack_inst, i);
                break;
            }
        }

        stack_push(stack_inst, 0);
        while (!(stack_is_empty(stack_inst) /* && (no_of_vert_left > 0) */)) {
            stack_value = stack_pop(stack_inst);

            if (stack_value == INT_MAX)                 break;
            if (marked[stack_value] == TRUE)            continue;

            fprintf(output, "%5d", stack_value);
            connected_graph[connected_graph_index][0] = stack_value;
            connected_graph[connected_graph_index][1] = disjoint_set;
            connected_graph_index++;

            marked[stack_value] = TRUE;
            no_of_vertex_left--;

            bag *bag_of_vertex = adjacency_list->bags[stack_value];
            node *node_of_vertex = bag_of_vertex->first;
            while (node_of_vertex) {
                stack_push(stack_inst, node_of_vertex->to);
                node_of_vertex = node_of_vertex->next;
            }
        }

        fprintf(output, "\n");
        if (stack_is_empty(stack_inst)) {
            disjoint_set++;
        }
    }

    fprintf(output, "The sets are: (In reverse order)\n");
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        fprintf(output, "%5d%5d\n", connected_graph[i][0], connected_graph[i][1]);
    }

    stack_destroy(stack_inst);
}

/** \brief Find if there are any cycles in the graph and print them.
 *
 * \param adjacency_list adj_list* - An Adjacency List of all the graph edges.
 * \return boolean - TRUE - if a cycle was found, FALSE - otherwise.
 */
boolean find_a_cycle(FILE *output, adj_list *adjacency_list)
{
    stack *stack_inst = stack_init();
    int no_of_vertices = adjacency_list->no_vert;
    int vertex;

    boolean marked[NMAX] = {FALSE}; // If a vertex has been visited, it is marked TRUE.
    int edge_to[NMAX];  // It stores the 'from' vertex from where we have
                        // an edge to this 'to' vertex. i.e.
                        // edge_to[1] = 2 means there is a vertex from 2 to 1.
    int graph_cycle[NMAX], graph_index = 0;
    boolean cycle_found = FALSE;

    bag *bag_of_vertex;
    node *node_of_vertex;

    // First element is - one where the first edges start from.
    // find first element
    for (int i = 0; i < adjacency_list->no_vert; i++) {
        bag_of_vertex = adjacency_list->bags[i];
        if (!bag_of_vertex)         return FALSE;
        if (bag_of_vertex->first)   break;
    }
    if (!bag_of_vertex->first)                          return FALSE;

    stack_push(stack_inst, bag_of_vertex->first->from);
    no_of_vertices--;
    marked[bag_of_vertex->first->from] = TRUE;
    edge_to[bag_of_vertex->first->from] = bag_of_vertex->first->from;

    fprintf(output, "\nThe cycle is:\n");
    while (no_of_vertices > 0) {
        // If a cycle is already found break out of this loop.
        // Do not further check for any cycles by push-pop on stack.
        if (cycle_found)
            break;

        vertex = stack_pop(stack_inst);
        bag_of_vertex = adjacency_list->bags[vertex];
        node_of_vertex = bag_of_vertex->first;

        while (node_of_vertex) {
            if (marked[node_of_vertex->to] == TRUE) {
                int i = node_of_vertex->from;
                int initial_node = node_of_vertex->to;
                graph_cycle[graph_index++] = node_of_vertex->to;
                graph_cycle[graph_index++] = node_of_vertex->from;

                while (i != initial_node) {
                    graph_cycle[graph_index++] = edge_to[i];
                    i = edge_to[i];
                }
                cycle_found = TRUE;
                break;
            }
            edge_to[node_of_vertex->to] = node_of_vertex->from;
            marked[node_of_vertex->to] = TRUE;
            stack_push(stack_inst, node_of_vertex->to);
            no_of_vertices--;
            node_of_vertex = node_of_vertex->next;
        }
    }

    for (int i = graph_index - 1; i >= 0; i--) {
        fprintf(output, "%5d", graph_cycle[i]);
    }
    return FALSE;
}

















