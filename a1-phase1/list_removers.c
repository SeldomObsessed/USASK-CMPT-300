/*
 * list_removers.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stddef.h>

#include <list.h>


/*
 * Access the "current" item and take it out of the list. If there is no
 * "current" item, nothing gets removed
 *
 * LIST *list: the LIST from which an item will be removed
 *
 * returns a pointer to the "current" item
 * returns NULL if the list is empty or there is no "current" item
 */
void *ListRemove(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListRemove: invalid parameter list\n");
    return NULL;
  }
  return NULL;
}


/*
 * Frees each item in the LIST using itemFree() and then frees the LIST.
 *
 * LIST *list: the LIST to empty and free
 * ItemFreer itemFree: the function which will handle freeing LIST items
 */
void ListFree(LIST *list, ItemFreer itemFree)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListFree: invalid parameter list\n");
    return;
  }
  if (itemFree == NULL)
  {
    fprintf(
      stderr, 
      "Error in procedure ListFree: invalid parameter itemFree\n"
    );
    return;
  }
  return;
}


/*
 * Removes the last item from the LIST and returns it.
 *
 * LIST *list: the LIST to remove the item from
 *
 * returns a pointer to the removed item
 * returns NULL on error or on empty list
 */
void *ListTrim(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListTrim: invalid parameter list\n");
    return NULL;
  }
  return NULL;
}

