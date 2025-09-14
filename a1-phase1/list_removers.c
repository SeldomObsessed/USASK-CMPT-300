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
    return NULL;
  }
  return NULL;
}

void ListFree(LIST *list, ItemFreer itemFree)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL || itemFree == NULL)
  {
    return;
  }
  return;
}

void *ListTrim(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    return (void *)-1;
  }
  return NULL;
}

void list_free(LIST *list)
{
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
  return;
  }
  return;
}

void node_free(NODE *node)
{
  /* check that correct type and range of parameter values have been passed */
  if (node == NULL)
  {
    return;
  }
  return;
}

