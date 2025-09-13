/*
 * filename.(c/h)
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stddef.h>

#include <list.h>


LIST *ListCreate()
{
  return NULL;
}


int ListAdd(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || item == NULL)
  {
    return 1;
  }
  return 0;
}


int ListInsert(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || item == NULL)
  {
    return 1;
  }
  return 0;
}


int ListAppend(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || item == NULL)
  {
    return 1;
  }
  return 0;
}


int ListPrepend(LIST *list, void *item)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || item == NULL)
  {
    return 1;
  }
  return 0;
}


int ListConcat(LIST *list1, LIST *list2)
{
  /* check that correct type and range of parameter values have been passed */
  if (list1 == NULL || list2 == NULL)
  {
    return 1;
  }
  return 0;
}


NODE *get_node()
{
  return NULL;
}

