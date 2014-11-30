#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

void perform_dfs(FILE *output, adj_list *adjacency_list);
boolean find_a_cycle(FILE *output, adj_list *adjacency_list);

#endif // DFS_H_INCLUDED
