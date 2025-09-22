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
#include <string.h>

#include <list.h>
#include <list_mem.h>

extern NODE *nodes;
extern LIST *lists;
extern MAP  *maps;
extern unsigned long int node_count;
extern unsigned long int list_count;
extern unsigned long int nli;
extern unsigned long int nni;


/*
 * takes a LIST and returns it to the supply of free LISTs. The LIST will no
 * longer be able to be used in the API
 *
 * will dynamically resize the amount of space allocated to LISTs when there are
 * too many of them
 *
 * returns 0 on success
 * returns -1 on failure
 * calls exit(2) on specific realloc fail
 */
int delete_list(LIST *list)
{
  LIST *new_location;
  long unsigned int i;
  ptrdiff_t shift;

  /* get rid of the lookup entry */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
      /* copy the last LIST entry to the location of the LIST to be deleted */
      new_location = maps[i].real_ptr;
      memmove(new_location, lists + nli - 1, sizeof(LIST));
      /* copy the last lookup entry here */
      memmove(maps + i, maps + nli - 1, sizeof(MAP));

      /* now we need to make the lookup table we just moved point to the right
       * LIST. We choose not to use this fact, but it just so happens that due
       * to the implementation, the real_ptr will be at the same idx in lists as
       * the map entry in maps. You could question the implementation and say it
       * could JUST use that but, eh, whatever it's more extensible like this */
      maps[i].real_ptr = lists + i;

      nli--;
    }
  }

  /* see if the allocation needs to be halved. Per design html, it says if you
   * are using LESS than half and since nli is the NEXT ptr, this is not off by
   * one */
  if (nli < list_count / 2)
  {
    list_count /= 2;
    new_location = realloc(lists, list_count * sizeof(LIST));
    if (new_location == NULL)
    {
      list_count *= 2;

      fprintf(
        stderr,
        "delete_list could not reallocate from %lu to %lu LISTs\n",
        list_count,
        list_count / 2
      );
      /* no program abort, just try again later */
      return -1;
    }
    maps = realloc(maps, list_count * sizeof(MAP));
    if (maps == NULL)
    {
      /* this is a really bad place to be. We only have list_count LISTs but
       * list_count * 2 MAPs, which means the program will lose this memory. We
       * could fix this with finite retying, per ListCreate's comment on the
       * matter */
      fprintf(
        stderr,
        "delete_list could not reallocate from %lu to %lu MAPs\n",
        list_count / 2,
        list_count
      );
      exit(2);
    }

    /* update all LIST pointers (inside of the lookup table) */
    if (lists != new_location)
    {
      shift = new_location - lists;
      for (i = 0; i < nli; i++)
      {
        /* you might say "lo! it could touch garbage!" but it won't. This loop
         * only ever triggers on a halving, and only touches in use (nli) */
        maps[i].real_ptr += shift;
      }
    }
    /* great, now forget about the old block */
    lists = new_location;
  }

  return 0;
}


/* I would have really appreciated a get_node() function which performed all the
 * copy-pasted code at the start of every adder function, then went into the
 * logic seen below in resize_nodes. Makaroff said not to do that, so my other
 * code is therefore less DRY */
/* get_node() */


/*
 * will double or halve the supply of NODEs.
 *
 * returns 0 on success
 * returns -1 on failure
 * calls exit(2) on specific realloc fail
 */
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

