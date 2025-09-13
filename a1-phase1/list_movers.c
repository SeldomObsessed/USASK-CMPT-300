/*
 * list_movers.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stddef.h>

#include <list.h>


int ListCount(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return -1;
  }
  return 0;
}


void *ListFirst(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}


void *ListLast(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}


void *ListNext(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}


void *ListPrev(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}


void *ListCurr(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}


void *ListSearch(LIST *list, Comparator comparator, void *comparisonArg)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || comparator == NULL || comparisonArg == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}

