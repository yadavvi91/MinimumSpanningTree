#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "graph.h"
#include "stack.h"
#include "dfs.h"

/** \brief Main function to check if the graph has a cycle.
 *
 * \param argc int - Number of command line arguments.
 * \param argv[] char* - Command line arguments.
 * \return int - EXIT_SUCCESS if successful, EXIT_FAILURE if call fails.
 *
 */
int main(int argc, char* argv[])
{
    FILE *input, *output;
    int MAX_SIZE = 512;
    char array[MAX_SIZE];

    int no_vertices;
    int no_edges;

    int from, to;
    float weight;

    if (argc == 3) {
        output = fopen(argv[--argc], "w");
        input = fopen(argv[--argc], "r");
    } else {
        fprintf(stderr, "Number of arguments do not match");
        exit(EXIT_FAILURE);
    }

    if (fgets(array, MAX_SIZE, input) != NULL) {
        if (sscanf(array, "%d", &no_vertices) != 1) {
            fprintf(stderr, "Scanf read is bad");
            exit(EXIT_FAILURE);
        }
    } else if (feof(input)) {
        fprintf(stdout, "End Of File reached");
    } else if (ferror(input)) {
        fprintf(stdout, "Some error while reading");
        exit(EXIT_FAILURE);
    }

    if (fgets(array, MAX_SIZE, input) != NULL) {
        if (sscanf(array, "%d", &no_edges) != 1) {
            fprintf(stderr, "Scanf read is bad");
            exit(EXIT_FAILURE);
        }
    } else if (feof(input)) {
        fprintf(stdout, "End Of File reached");
    } else if (ferror(input)) {
        fprintf(stdout, "Some error while reading");
        exit(EXIT_FAILURE);
    }

    adj_list *adjacency_list = create_graph(no_vertices);

    int size_of_lines = 3;
    char *val;
    for (int j = 0; j < no_edges; j++) {
        if (fgets(array, MAX_SIZE, input) != NULL) {
            val = strtok(array, " \t\n\r");
            for (int i = 0; i < size_of_lines; i++) {
                switch (i) {
                case 0:
                    from = atoi(val);
                    break;
                case 1:
                    to = atoi(val);
                    break;
                case 2:
                    weight = atof(val);
                    break;
                default:
                    fprintf(stderr, "Some error");
                    exit(EXIT_FAILURE);
                }
                val = strtok(NULL, " \t\n\r");
            }
            add_edge(adjacency_list, from, to, weight);
        } else if (feof(input)) {
            fprintf(stdout, "End Of File reached");
        } else if (ferror(input)) {
            fprintf(stdout, "Some error while reading");
            exit(EXIT_FAILURE);
        }
    }

    // perform_dfs(adjacency_list);
    find_a_cycle(adjacency_list);
    return EXIT_SUCCESS;
}



























