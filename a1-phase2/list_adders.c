/*
 * list_adders.c
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
#include <list_mem.h>

unsigned long int list_count = MIN_LISTS; /* currently allocated # LISTs */
unsigned long int node_count = MIN_NODES; /* currently allocated # NODEs */
unsigned long int next_list_idx = 0;      /* idx of next free LIST */
unsigned long int next_node_idx = 0;      /* idx of next free NODE */

NODE *nodes;                /* array of NODEs to fill LISTs */
LIST *lists;                /* array of LISTs to be passed out to users */
MAP *maps;                  /* array of MAPs to be a lookup table */

bool init = false;          /* whether initial mallocs have been run */


/*
 * makes a new LIST and returns the reference to the user for later access in
 * the API
 *
 * tags the pointer for internal handling, making the pointer potentially
 * invalid when dereferenced outside of the API. Handles the case where the
 * next_list_idx >= list_count and will double the amount of space. Calls
 * exit(1) if malloc fails.
 *
 * returns a pointer to a new empty LIST
 * returns NULL on failure
 */
LIST *ListCreate()
{
  LIST *new_lists; /* head of new array, on realloc */

  if (init == false)
  {
    /* make the initial sized arrays */
    nodes = malloc(node_count * sizeof(NODE));
    if (nodes == NULL)
    {
      fprintf(
        stderr,
        "ListCreate could not allocate %lu NODEs\n",
        node_count
      );
      exit(1);
    }

    lists = malloc(list_count  * sizeof(LIST));
    if (lists == NULL)
    {
      fprintf(
        stderr,
        "ListCreate could not allocate %lu LISTs\n",
        list_count
      );
      exit(1);
    }

    maps = malloc(list_count * sizeof(MAP));
    if (maps == NULL)
    {
      fprintf(
        stderr,
        "ListCreate could not allocate %lu MAPs\n",
        list_count
      );
      exit(1);
    }

    printf(
      "ListCreate() malloc'ed space for %lu LISTs, %lu MAPs, and %lu NODES\n",
      list_count,
      list_count,
      node_count
    );

    init = true;
  }

  /* the array needs to be doubled */
  if (next_list_idx >= list_count)
  {
    list_count *= 2;
    new_lists = realloc(lists, list_count * sizeof(LIST));
    if (new_lists == NULL)
    {
      fprintf(
        stderr,
        "ListCreate could not reallocate %lu LISTs\n",
        list_count
      );
      /* It isn't worth aborting over a realloc failure, just try later */
      return NULL;
    }

    printf(
      "ListCreate() realloc'ed space from %lu to %lu LISTs\n",
      list_count / 2,
      list_count
    );
  }

  printf("Got to procedure ListCreate()\n");
  return NULL;
}


/*
 * adds an element to the LIST after the "current" position in the LIST and the
 * "current" position becomes the new element. When "current" position is not
 * set, then this operation behaves like an append
 *
 * the element MUST be the same type as all the other elements in the list
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListAdd(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListAdd: invalid parameter list\n");
    return -1;
  }
  if (item == NULL)
  {
    fprintf(stderr, "Error in procedure ListAdd: invalid parameter item\n");
    return -1;
  }
  printf("Got to procedure ListAdd()\n");
  return 0;
}


/*
 * adds an element to the LIST before the "current" position in the LIST and the
 * "current" position becomes the new element. When "current" position is not
 * set, then this operation behaves like a prepend
 *
 * the element MUST be the same type as all the other elements in the list
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListInsert(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListInsert: invalid parameter list\n");
    return -1;
  }
  if (item == NULL)
  {
    fprintf(stderr, "Error in procedure ListInsert: invalid parameter item\n");
    return -1;
  }
  printf("Got to procedure ListInsert()\n");
  return 0;
}


/*
 * adds an element to the end of the LIST and the "current" position becomes the
 * new element
 *
 * the element MUST be the same type as all the other elements in the list
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListAppend(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListAppend: invalid parameter list\n");
    return -1;
  }
  if (item == NULL)
  {
    fprintf(stderr, "Error in procedure ListAppend: invalid parameter item\n");
    return -1;
  }
  printf("Got to procedure ListAppend()\n");
  return 0;
}


/*
 * adds an element to the start of the LIST and the "current" position becomes
 * the new element
 *
 * the element MUST be the same type as all the other elements in the list
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListPrepend(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListPrepend: invalid parameter list\n");
    return -1;
  }
  if (item == NULL)
  {
    fprintf(stderr, "Error in procedure ListPrepend: invalid parameter item\n");
    return -1;
  }
  printf("Got to procedure ListPrepend()\n");
  return 0;
}


/*
 * adds all the elements of list2 to the end of list1, preserving order
 *
 * list2 will be deleted after this function is executed. The elements in both
 * lists MUST be of the same type
 *
 * LIST *list1: the LIST which will be grown
 * LIST *list2: the LIST which will be appended
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListConcat(LIST *list1, LIST *list2)
{
  /* check that correct type and range of parameter values have been passed */
  if (list1 == NULL)
  {
    fprintf(stderr, "Error in procedure ListConcat: invalid parameter list1\n");
    return -1;
  }
  if (list2 == NULL)
  {
    fprintf(stderr, "Error in procedure ListConcat: invalid parameter list2\n");
    return -1;
  }
  if (list1 == list2)
  {
    fprintf(
      stderr,
      "Error in procedure ListConcat: list1 must not equal list2\n"
    );
    return -1;
  }
  printf("Got to procedure ListConcat()\n");
  return 0;
}

