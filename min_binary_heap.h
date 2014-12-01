#ifndef MIN_BINARY_HEAP_H_INCLUDED
#define MIN_BINARY_HEAP_H_INCLUDED

typedef int boolean;

#define NMAX 1000
#define TRUE 1
#define FALSE 0

boolean insert(int i, int *size_of_heap, float key, int pq[], float keys[]);
void swim(int k, int pq[], float keys[]);
boolean greater(int i, int j, int pq[], float keys[]);
void exch(int i, int j, int pq[]);
void swim_simple(int k, int pq[], float keys[]);
int delete_min(int *size_of_heap, int pq[], float keys[]);
void sink(int k, int *size_of_heap, int pq[], float keys[]);
void sink_simple(int k, int *size_of_heap, int pq[], float keys[]);
boolean decrease_key(int i, int *size, float key, int pq[], float keys[]);

#endif // MIN_BINARY_HEAP_H_INCLUDED
