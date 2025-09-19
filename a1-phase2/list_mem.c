/*
 * list_mem.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <list.h>

extern NODE *nodes;
extern LIST *lists;
extern unsigned long int node_count;
extern unsigned long int nli;
extern unsigned long int nni;

int resize_nodes(bool grow)
{
  NODE *new_nodes; /* head of new array, on realloc */
  ptrdiff_t shift; /* block's diff in mem offset to shift old references */
  unsigned long int i;

  /* do not shrink lower than minimum */
  if (!grow && node_count / 2 < MIN_NODES)
  {
     /* this is not an error case, just don't do it */
     return 0;
  }

  /* resize nodes */
  node_count = grow ? node_count * 2 : node_count / 2;
  new_nodes = realloc(nodes, node_count * sizeof(NODE));
  if (new_nodes == NULL)
  {
    /* if realloc failed, revert node_count change and return reporting error */
    node_count = grow ? node_count / 2 : node_count * 2;

    fprintf(
      stderr,
      "double_nodes could not reallocate from %lu to %lu NODEs\n",
      node_count,
      grow ? node_count * 2 : node_count / 2
    );
    return -1;
  }

  /* this is for updating all the references. NODEs might move in memory after
   * the realloc, but they will all move at once by a constant offset, not
   * changing the distance between any two NODEs in the address space. All
   * pointers thus may be adjusted by adding a constant */
  shift = new_nodes - nodes;

  /* update all in-use-LISTs' pointers to NODEs */
  for (i = 0; i < nli; i++)
  {
    if (lists[i].current != NULL)
    {
      lists[i].current += shift;
    }
    if (lists[i].count != 0)
    {
      lists[i].first += shift;
      lists[i].last += shift;
    }
  }

  /* update all in-use-NODEs' pointers to other NODEs */
  for (i = 0; i < nni; i++)
  {
    if (new_nodes[i].next != NULL)
    {
      new_nodes[i].next += shift;
    }
    if (new_nodes[i].prev != NULL)
    {
      new_nodes[i].prev += shift;
    }
  }

  /* forget about the head of the old block of NODEs */
  nodes = new_nodes;

  printf(
      "double_nodes reallocated from %lu to %lu NODEs\n",
      grow ? node_count / 2 : node_count * 2,
      node_count
    );

  return 0;
}

