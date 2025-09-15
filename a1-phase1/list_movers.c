/*
 * list_movers.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stddef.h>
#include <stdio.h>

#include <list.h>


/*
 * counts the number of items in the LIST
 *
 * returns the integer tally of items in the LIST
 * returns -1 on error
 */
int ListCount(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListCount: invalid parameter list\n");
    return -1;
  }
  printf("Got to procedure ListCount()\n");
  return 0;
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
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListFirst: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListFirst()\n");
  return NULL;
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
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListLast: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListLast()\n");
  return NULL;
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
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListNext: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListNext()\n");
  return NULL;
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
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListPrev: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListPrev()\n");
  return NULL;
}


/*
 * Checks the current element in the LIST
 *
 * returns a pointer to the current item in the LIST (may be NULL)
 * returns NULL on error
 */
void *ListCurr(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListCurr: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListCurr()\n");
  return NULL;
}


/*
 * Performs a search along a LIST
 *
 * The comparator argument will be passed each element in the list (along with
 * comparisonArg) and when (if) the return is 0, that element is set as the
 * "current" element. If no results are ever found, the "current" element is set
 * to NULL
 *
 * returns a pointer to the "current" element at the end of the search (which
 *   will be the found item, or NULL
 * returns NULL on error
 */
void *ListSearch(LIST *list, Comparator comparator, void *comparisonArg)
{
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
  if (comparisonArg == NULL)
  {
    fprintf(
      stderr,
      "Error in procedure ListSearch: invalid parameter comparisonArg\n"
    );
    return NULL;
  }
  printf("Got to procedure ListSearch()\n");
  return NULL;
}

