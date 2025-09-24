/*
 * list_adders.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <list.h>
#include <list_mem.h>

unsigned long int list_count = MIN_LISTS; /* currently allocated # LISTs */
unsigned long int node_count = MIN_NODES; /* currently allocated # NODEs */
unsigned long int nli = 0;      /* idx of next free LIST */
unsigned long int nni = 0;      /* idx of next free NODE */

NODE *nodes;                /* array of NODEs to fill LISTs */
LIST *lists;                /* array of LISTs to be passed out to users */
MAP *maps;                  /* array of MAPs to be a lookup table */

bool init = false;          /* whether initial mallocs have been run */


/*
 * makes a new LIST and returns the reference to the user for later access in
 * the API
 *
 * will initialize all initial data structures required to support the API.
 * pointers given may be tagged, which is for internal handling, and as such
 * the pointers given should only be used via the API. Will dynamically resize
 * the amount of space allocated to LISTs when there are not enough of them
 *
 * returns a pointer to a new empty LIST
 * returns NULL on recoverable failure
 * calls exit(1) if malloc fails (only risks occuring on first use)
 * calls exit(2) on specific realloc fail
 */
LIST *ListCreate()
{
  LIST *new_lists; /* head of new array, on realloc */
  ptrdiff_t shift; /* block's diff in mem offset to shift old references */
  u_int16_t tag;    /* 16 bit tag for distinguishing duplicate LIST pointers */
  bool new_tag;
  unsigned long int i;

  printf("Got to procedure ListCreate()\n");

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
  if (nli >= list_count)
  {
    list_count *= 2;
    new_lists = realloc(lists, list_count * sizeof(LIST));
    if (new_lists == NULL)
    {
      list_count /= 2;

      fprintf(
        stderr,
        "ListCreate could not reallocate %lu LISTs\n",
        list_count
      );
      /* it isn't worth aborting over a realloc failure, just try later */
      return NULL;
    }
    maps = realloc(maps, list_count * sizeof(MAP));
    if (maps == NULL)
    {
       /* this is a really bad place to be. We have list_count LISTs but only
        * list_count / 2 MAPs, which means the program is going to fail very
        * shortly without any rectification taking place. I could code this, but
        * c'mon, how often does realloc fail? I don't think we need this level
        * of robustness, but it could be added with finite retrying */
       fprintf(
         stderr,
         "ListCreate could not reallocate %lu MAPs\n",
         list_count
       );
       exit(2);
    }

    printf(
      "ListCreate() realloc'ed space from %lu to %lu LISTs\n",
      list_count / 2,
      list_count
    );

    /* update all LIST pointers (inside of the lookup table) */
    if (lists != new_lists)
    {
      shift = new_lists - lists;
      for (i = 0; i < list_count / 2; i++)
      {
        /* you might say "lo! it could touch garbage!" but it won't. This loop
         * only ever triggers on a doubling, when all MAPs are in use, and after
         * the doubling we can still go to [list_count / 2 - 1] safely */
        maps[i].real_ptr += shift;
      }
    }
    /* great, now forget about the old block */
    lists = new_lists;
  }

  /* hand back a list to the user plus get rid of garbage */
  lists[nli].count = 0;
  lists[nli].current = NULL;
  lists[nli].first = NULL;
  lists[nli].last = NULL;

  /* tag if it is in the lookup table. This is VERY VERY slow if there is a huge
   * number of LISTs in the lookup table with the same handed out pointer. Like,
   * by comparison anyway. 20 of the same tagged original ptr and 8,0000 LISTs
   * would lead to 160,000 steps through maps. But this is necessary, otherwise
   * luck could have it that you hand out (LIST *)2000 multiple times and things
   * would break. Makaroff told me to just explain that I know this could be
   * slow if the code loses the rng gambit, but the fix would be out of the
   * scope of this project (having excess memory on the side to go through all
   * the MAPs and collect all tags on the root pointer at once as opposed to
   * counting one by one, then go through that list quickly to find the 
   * smallest tag available) */
  tag = 0;
  new_tag = false;
  while (true)
  {
    new_tag = true; /* assume we can stop here and tag, until proven wrong */
    for (i = 0; i < list_count ; i++)
    {
      /* huzzah! we were about to hand out this existing user held pointer. As
       * a note, the TAG_MASK just sets the high 16 bits to zero, leaving the
       * pointer which is 48 bits on our amd64 system */
      if (
           ((uintptr_t)maps[i].user_key & TAG_MASK) ==
           ((uintptr_t)(lists + nli) & TAG_MASK)
      )
      {
        /* shift 48 bits out of the user held pointer to look at its tag, if the
         * tag there is equal to our current increment of tag, we'll have to
         * loop through again. THIS is the slow part, like if the next free tag
         * for a given pointer is 20, here's where it will loop through a stupid
         * amount of times, but realistically this tag shouldn't ever get too
         * high */
        if ((uint16_t)((uintptr_t)maps[i].user_key >> 48) == tag)
        {
          /* sidenote, this will fail if there is ever 2^16 duplicates... but I
           * think that's an acceptably unreasonable situation to not deal with
           * it */
          tag += 1;
          new_tag = false;
          break;
        }
      }
    }
    if (!new_tag)
    {
      continue;
    }

    /* great, tag is now equal to the required tag (probably 0). What this code
     * does is take the REAL LIST pointer and slaps the tag in the high 16 bits
     * by shifting our tag variable 48 bits up */
    maps[nli].user_key = (
      (LIST *)(((uintptr_t)(lists + nli)) | ((uintptr_t)tag << 48))
    );

    /* finish the map entry and return the user_key pointer we just made */
    maps[nli].real_ptr = lists + nli;
    nli += 1;
    return maps[nli - 1].user_key;
  }
}


/*
 * adds an element to the LIST after the "current" position in the LIST and the
 * "current" position becomes the new element. When "current" position is not
 * set, then this operation behaves like an append
 *
 * the element MUST be the same type as all the other elements in the LIST. Will
 * dynamically resize the amount of space allocated to NODEs when there are not
 * enough of them
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListAdd(LIST *list, void *item)
{
  unsigned long int i;
  int flag;
  bool active_list;

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

  /* determine true LIST * This is done first since the LIST may be bad, in
   * which case we shouldn't double NODEs */
  active_list = false;
  for (i = 0; i < nli; i++)
  {
    if (maps[i].user_key == list)
    {
      active_list = true;
      list = maps[i].real_ptr;
      break;
    }
  }

  /* the user gave a LIST which was freed */
  if (!active_list)
  {
    fprintf(stderr, "ListAdd was given an inactive list\n");
    return -1;
  }

  /* if the NODE supply has run out double it */
  if (nni >= node_count)
  {
    flag = resize_nodes(true);
    if (flag != 0)
    {
      fprintf(stderr, "Error in procedure ListAdd: unable to double NODE\n");
      return -1;
    }
  }

  /* build the NODE we're using */
  nodes[nni].item = item;
  nodes[nni].next = NULL;
  nodes[nni].prev = NULL;

  /* when the LIST is empty, perform append */
  if (list->count == 0)
  {
    list->first = nodes + nni;
    list->last = nodes + nni;
  }
  /* when current is NULL, perform append */
  else if (list->current == NULL)
  {
    list->last->next = nodes + nni;
    nodes[nni].prev = list->last;
    list->last = nodes + nni;
  }
  /* otherwise, put in the middle */
  else
  {
    nodes[nni].prev = list->current;
    nodes[nni].next = list->current->next;
    if (list->current->next != NULL)
    {
      list->current->next->prev = nodes + nni;
    }
    /* otherwise, this is the new last element */
    else
    {
      list->last = nodes + nni;
    }
    list->current->next = nodes + nni;
  }
  list->current = nodes + nni;
  list->count++;
  nni++;

  return 0;
}


/*
 * adds an element to the LIST before the "current" position in the LIST and the
 * "current" position becomes the new element. When "current" position is not
 * set, then this operation behaves like a prepend
 *
 * the element MUST be the same type as all the other elements in the LIST. Will
 * dynamically resize the amount of space allocated to NODEs when there are not
 * enough of them
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListInsert(LIST *list, void *item)
{
  unsigned long int i;
  int flag;
  bool active_list;

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

  /* determine true LIST * This is done first since the LIST may be bad, in
   * which case we shouldn't double NODEs */
  active_list = false;
  for (i = 0; i < list_count; i++)
  {
    if (maps[i].user_key == list)
    {
      active_list = true;
      list = maps[i].real_ptr;
      break;
    }
  }

  /* the user gave a LIST which was freed */
  if (!active_list)
  {
    fprintf(stderr, "ListInsert was given an inactive list\n");
    return -1;
  }

  /* if the NODE supply has run out double it */
  if (nni >= node_count)
  {
    flag = resize_nodes(true);
    if (flag != 0)
    {
      fprintf(stderr, "Error in procedure ListInsert: unable to double NODE\n");
      return -1;
    }
  }

  /* build the NODE we're using */
  nodes[nni].item = item;
  nodes[nni].next = NULL;
  nodes[nni].prev = NULL;

  /* when the LIST is empty, perform prepend */
  if (list->count == 0)
  {
    list->first = nodes + nni;
    list->last = nodes + nni;
  }
  /* when current is NULL, perform prepend */
  else if (list->current == NULL)
  {
    nodes[nni].next = list->first;
    list->first->prev = nodes + nni;
    list->first = nodes + nni;
  }
  /* otherwise, put in the middle */
  else
  {
    nodes[nni].next = list->current;
    nodes[nni].prev = list->current->prev;
    if (list->current->prev != NULL)
    {
      list->current->prev->next = nodes + nni;
    }
    /* otherwise, this is the new first element */
    else
    {
      list->first = nodes + nni;
    }
    list->current->prev = nodes + nni;
  }
  list->current = nodes + nni;
  list->count++;
  nni++;

  return 0;
}


/*
 * adds an element to the end of the LIST and the "current" position becomes the
 * new element
 *
 * the element MUST be the same type as all the other elements in the LIST. Will
 * dynamically resize the amount of space allocated to NODEs when there are not
 * enough of them
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListAppend(LIST *list, void *item)
{
  unsigned long int i;
  int flag;
  bool active_list;

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

  /* determine true LIST * This is done first since the LIST may be bad, in
   * which case we shouldn't double NODEs */
  active_list = false;
  for (i = 0; i < list_count; i++)
  {
    if (maps[i].user_key == list)
    {
      active_list = true;
      list = maps[i].real_ptr;
      break;
    }
  }

  /* the user gave a LIST which was freed */
  if (!active_list)
  {
    fprintf(stderr, "ListAppend was given an inactive list\n");
    return -1;
  }

  /* if the NODE supply has run out double it */
  if (nni >= node_count)
  {
    flag = resize_nodes(true);
    if (flag != 0)
    {
      fprintf(stderr, "Error in procedure ListAppend: unable to double NODE\n");
      return -1;
    }
  }

  /* build the NODE we're using */
  nodes[nni].item = item;
  nodes[nni].next = NULL;

  /* if the LIST is empty, slap this NODE in */
  if (list->count == 0)
  {
    list->first = nodes + nni;
    nodes[nni].prev = NULL;
  }
  /* otherwise point the old last to the new NODE */
  else
  {
    list->last->next = nodes + nni;
    nodes[nni].prev = list->last;
  }
  list->last = nodes + nni;
  list->current = nodes + nni;
  list->count++;
  nni++;

  return 0;
}


/*
 * adds an element to the start of the LIST and the "current" position becomes
 * the new element
 *
 * the element MUST be the same type as all the other elements in the LIST. Will
 * dynamically resize the amount of space allocated to NODEs when there are not
 * enough of them
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returns -1 on failure
 */
int ListPrepend(LIST *list, void *item)
{
  unsigned long int i;
  int flag;
  bool active_list;

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

  /* determine true LIST * This is done first since the LIST may be bad, in
   * which case we shouldn't double NODEs */
  active_list = false;
  for (i = 0; i < list_count; i++)
  {
    if (maps[i].user_key == list)
    {
      active_list = true;
      list = maps[i].real_ptr;
      break;
    }
  }

  /* the user gave a LIST which was freed */
  if (!active_list)
  {
    fprintf(stderr, "ListPrepend was given an inactive list\n");
    return -1;
  }

  /* if the NODE supply has run out double it */
  if (nni >= node_count)
  {
    flag = resize_nodes(true);
    if (flag != 0)
    {
      fprintf(
        stderr,
        "Error in procedure ListPrepend: unable to double NODE\n"
      );
      return -1;
    }
  }

  /* build the NODE we're using */
  nodes[nni].item = item;
  nodes[nni].prev = NULL;

  /* if the LIST is empty, slap this NODE in */
  if (list->count == 0)
  {
    list->last = nodes + nni;
    nodes[nni].next = NULL;
  }
  else
  {
    list->first->prev = nodes + nni;
    nodes[nni].next = list->first;
  }
  list->first = nodes + nni;
  list->current = nodes + nni;
  nni++;

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
  unsigned long int i;
  int flag, active_list;

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

  /* determine true LIST * This is done first since the LIST may be bad, in
   * which case we shouldn't continue */
  active_list = 0;
  for (i = 0; i < nli; i++)
  {
    if (maps[i].user_key == list1)
    {
      active_list++;
      list1 = maps[i].real_ptr;
    }
    else if (maps[i].user_key == list2)
    {
      active_list++;
      list2 = maps[i].real_ptr;
    }
    /* the search is complete, both lists were found, skip further comparison */
    if (active_list == 2)
    {
      continue;
    }
  }

  /* the user gave a LIST which was freed */
  if (active_list != 2)
  {
    fprintf(stderr, "ListConcat was given at least one inactive list\n");
    return -1;
  }

  /* perform concatenation */
  list1->last->next = list2->first;
  list1->last = list2->last;

  /* "free" list2 (scrub lookup table entry, maybe half memory) */
  flag = delete_list(list2);
  if (flag != 0)
  {
    /* this is actually okay, we have more memory than needed, but it will be
     * cleaned up (or at least an attempt will be made) next time delete_list
     * is called */
  }

  return 0;
}

