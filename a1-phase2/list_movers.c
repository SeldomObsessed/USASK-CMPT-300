/*
 * list_movers.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <list.h>
#include <list_mem.h>

extern NODE *nodes;
extern MAP *maps;
extern unsigned long int nli;
extern unsigned long int nni;


/*
 * counts the number of items in the LIST
 *
 * returns the integer tally of items in the LIST
 * returns -1 on error
 */
int ListCount(LIST *list)
{
  unsigned long int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListCount: invalid parameter list\n");
    return -1;
  }

  printf("Got to procedure ListCount()\n");

  /* access the true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
      list = maps[i].real_ptr;
      break;
    }
  }

  return list->count;
}


/*
 * makes the first item in the LIST the "current" element. If the LIST is empty,
 * NULL will be set as "current"
 *
 * returns a pointer to the first item in the list
 * returns NULL when the list is empty
 * returns NULL on errror
 */
void *ListFirst(LIST *list)
{
  unsigned int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListFirst: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListFirst()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  list->current = list->first;

  return list->current->item;
}


/*
 * makes the last item in the LIST the "current" element. If the LIST is empty,
 * NULL will be set as "current"
 *
 * returns a pointer for the last item in the LIST
 * returns NULL when the list is empty
 * returns NULL on error
 */
void *ListLast(LIST *list)
{
  unsigned int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListLast: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListLast()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  list->current = list->last;

  return list->current->item;
}


/*
 * makes the item which appears in the LIST after the "current" element the new
 * "current" element. If there is no "current" element, the first element in the
 * LIST becomes the "current" element. If the LIST is empty, NULL will be set as
 * "current". If the initial "current" element is the last element of the list,
 * NULL will be set as "current"
 *
 * returns a pointer to the next item in the LIST (may be NULL)
 * returns NULL when the list is empty
 * returns NULL on error
 */
void *ListNext(LIST *list)
{
  unsigned int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListNext: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListNext()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  if (list->current != NULL)
  {
    list->current = list->current->next;
  }

  return list->current->item;
}


/*
 * makes the item which appears in the LIST before the "current" element the new
 * "current" element. If there is no "current" element, the last element in the
 * LIST becomes the "current" element. If the LIST is empty, NULL will be set as
 * "current". If the inital "current" element is the first element of the list,
 * NULL will be set as "current"
 *
 * returns a pointer to the previous item in the LIST (may be NULL)
 * returns NULL when the list is empty
 * returns NULL on error
 */
void *ListPrev(LIST *list)
{
  unsigned int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListPrev: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListPrev()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  if (list->current != NULL)
  {
    list->current = list->current->prev;
  }

  return list->current->item;
}


/*
 * Checks the current element in the LIST
 *
 * returns a pointer to the current item in the LIST (may be NULL)
 * returns NULL on error
 */
void *ListCurr(LIST *list)
{
  unsigned int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListCurr: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListCurr()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  return list->current->item;
}


/*
 * Performs a search along a LIST
 *
 * The comparator argument will be passed each element in the list (along with
 * comparisonArg) and when (if) the return is 0, that element is set as the
 * "current" element. If no results are ever found, the "current" element is set
 * to NULL
 *
 * comparisonArg is allowed to be NULL, in contrast to other parameters
 *
 * returns a pointer to the "current" element at the end of the search (which
 *   will be the found item, or NULL
 * returns NULL on error
 */
void *ListSearch(LIST *list, Comparator comparator, void *comparisonArg)
{
  unsigned long int i;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListSearch: invalid parameter list\n");
    return NULL;
  }
  if (comparator == NULL)
  {
    fprintf(
      stderr,
      "Error in procedure ListSearch: invalid parameter comparator\n"
    );
    return NULL;
  }

  /* Dispel compiler warning */
  if (comparisonArg == NULL)
  {
  }

  printf("Got to procedure ListSearch()\n");

    /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
  }

  list->current = list->first;
  while (list->current != NULL)
  {
    if (comparator(list->current->item, comparisonArg) == 0)
    {
      break;
    }
  }

  return list->current->item;
}

