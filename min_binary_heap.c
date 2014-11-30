#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "min_binary_heap.h"

boolean insert(int i, int *size, float key, int pq[], float keys[])
{
    if (i < 0 || i > NMAX)          return FALSE;

    (*size)++;
    pq[*size] = i;
    keys[i] = key;
    // swim(size, pq, keys);
    swim_simple(*size, pq, keys);
    return TRUE;
}

void swim(int k, int pq[], float keys[])
{
    while (k > 1 && greater(k/2, k, pq, keys)) {
        exch(k, k/2, pq);
        k = k/2;
    }
}

boolean greater(int i, int j, int pq[], float keys[])
{
    if (keys[pq[i]] > keys[pq[j]])      return TRUE;
    else                                return FALSE;
}

void exch(int i, int j, int pq[])
{
    int swap = pq[i];
    pq[i] = pq[j];
    pq[j] = swap;
}

void swim_simple(int k, int pq[], float keys[])
{
    if (k == 1)             return;

    while (k > 1 && greater(k/2, k, pq, keys)) {
        exch(k, k/2, pq);
        k = k/2;
    }
}

int delete_min(int *size, int pq[], float keys[])
{
    if ((*size) <= 0) {
        return INT_MAX;
    }

    int min = pq[1];
    exch(1, (*size)--, pq);
    // sink(1, size, pq, keys);
    sink_simple(1, size, pq, keys);

    return min;
}

/** \brief Sink an element to its proper position after deleting some element.
 *
 * \param
 * \param
 * \return
 *
 */
void sink(int k, int *size, int pq[], float keys[])
{
    while (2 * k <= (*size)) {
        int j = 2 * k;
        if (j < (*size) && greater(j, j+1, pq, keys))   j++;
        if (!greater(k, j, pq, keys))                   break;
        exch(k, j, pq);
        k = j;
    }
}

void sink_simple(int k, int *size, int pq[], float keys[])
{
    if ((*size) == 0)
        return;

    if (k == (*size))       // There were 2 elements, but now after deletion only 1 element is left.
        return;

    int i, j;

    while (k <= (*size)) {
        i = 2 * k;
        j = i + 1;

        if (i > (*size))
            return;

        if (j > (*size)) {
            if (greater(k, i, pq, keys)) {
                exch(k, i, pq);
                k = i;
                continue;
            } else {
                break;
            }
        }

        if (!greater(i, j, pq, keys)) {
            if (greater(k, i, pq, keys)) {
                exch(k, i, pq);
                k = i;
            } else {
                break;
            }
        } else {
            if (greater(k, j, pq, keys)) {
                exch(k, j, pq);
                k = j;
            } else {
                break;
            }
        }
    }
}

boolean decrease_key(int i, int *size, float key, int pq[], float keys[])
{
    if (i < 0 || i > NMAX)              return FALSE;
    keys[i] = key;
    swim(i, pq, keys);
    return TRUE;
}






















