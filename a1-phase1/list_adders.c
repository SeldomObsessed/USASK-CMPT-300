/*
 * list_adders.c
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
  return 0;
}

