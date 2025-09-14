/*
 * filename.(c/h)
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stddef.h>

#include <list.h>

/*
 * makes a new list and returns the reference to the user for later access in
 * the API
 *
 * tags the pointer for internal handling, making the pointer potentially
 * invalid when dereferenced outside of the API
 *
 * returns a pointer to a new empty LIST
 */
LIST *ListCreate()
{
  return NULL;
}

/*
 * adds an element to the LIST after the "current" position in the LIST and the
 * new element becomes the "current" position
 *
 * LIST *list: the LIST which will be added onto
 * void *item: the item to be added
 *
 * returns 0 on success
 * returs -1 on failure
 */
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

