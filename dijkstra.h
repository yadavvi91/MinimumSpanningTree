#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

/*
 * What is relaxation in Dijkstra's algorithm?
 * In general mathematically, 'relaxation' is making a change that reduces constraints.
 * When Dijkstra's algorithm examines an edge, it removes an edge from the pool, thereby
 * reducing the number of constraints.
 * Think about a vertex with a lot of edges coming into it. When you start, you you start
 * you know the solution has to include the weight from the first edge, the second edge,
 * and so on. In effect, for edges a, b, c, d and e, you start saying "the shortest path
 * must include a, b, c, d, e". Then you eliminate e, and now you know it must include
 * just "a, b, c, d". Each step is a "relaxation" because at each step you remove a
 * condition the current solution imposes.
 *
 *
 * <== As explained in Cormen ==>
 *
 * Single-Source shortest path algorithms use the technique of relaxation.
 * For each vertex (v belonging to V), we maintain an attribute 'v.d', which is an upper bound
 * on the weight of a shortest path from source 's' to 'v'. We call 'v.d' a shortest-path
 * estimate . We initialize the shortest-path estimates and predecessors by the following
 * procedure:
 *
 * INITIALIZE-SINGLE-SOURCE(G, s)
 *      for each vertex (v belonging to G.V)
 *          v.d = infinity
 *          v.pi = NIL      // pi - parent of node
 *      s.d = 0             // s - source
 *
 * After initialization, we have v.pi = NIL for all (v belonging to V), s.d = 0 and v.d = infinity
 * for (v belonging to V-{s}).
 *
 * The process of 'relaxing' an edge (u, v) consists of testign whether we can improve the shortest
 * path to 'v' found so far by going through 'u' and, if so, updating 'v.d' and 'v.pi'.
 * A relaxation step may decrease the value of the shortest-path estimate 'v.d' and update "v's"
 * predecessor attribute 'v.pi'. The following code performs a relaxation step on edge (u, v) in
 * O(1) time.
 *
 * RELAX(u, v, w)
 *      if v.d > u.d + w(u, v)
 *          v.d = u.d + w(u, v)
 *          v.pi = w
 */


void create_dijkstra_path(int start_vertex, adj_list *adjacency_list, float dist_to[], int edge_to[]);
void print_shortest_path(FILE *output, int start_vertex, adj_list *adjacency_list);
void relax(node *node_of_vertex, float dist_to[], int edge_to[], int *size_of_heap, int pq[], float keys[]);

#endif // DIJKSTRA_H_INCLUDED










