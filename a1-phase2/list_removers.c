/*
 * list_removers.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include <list_mem.h>

extern NODE *nodes;
extern LIST *lists;
extern MAP *maps;
extern unsigned long int node_count;
extern unsigned long int nli;
extern unsigned long int nni;


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
  unsigned long int i;
  void *item;
  NODE *tmp_node;
  bool flag;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListRemove: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListRemove()\n");

  flag = false;
  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       flag = true;
       break;
    }
  }

  if (flag != true)
  {
    fprintf(
      stderr,
      "Error in procedure ListRemove: was given an inactive list\n"
    );
    return NULL;
  }

  /* no removal occurs if there is no current NODE */
  if (list->current == NULL)
  {
    return NULL;
  }

  /* update the nodes next to current */
  if (list->current->next != NULL)
  {
    list->current->next->prev = list->current->prev;
  }
  if (list->current->prev != NULL)
  {
    list->current->prev->next = list->current->next;
  }

  /* update last and first when necessary */
  if (list->current == list->first)
  {
    list->first = list->current->next;
  }
  if (list->current == list->last)
  {
    list->last = list->current->prev;
  }

  /* the NODE after the initial current, which needs to be the final current */
  tmp_node = list->current->next;
  item = list->current->item;
  
  flag = false; /* if you are moving what you are deleting, DON'T TOUCH */
  if (list->current == nodes + nni - 1)
  {
    flag = true;
  }
  /* access and "cover up" the current node */
  memmove(list->current, nodes + nni - 1, sizeof(NODE));
  nni--;
  list->count--;

  /* update all references to the moved [nni - 1] NODE */
  if (!flag)
  {
    if (tmp_node == nodes + nni)
    {
      tmp_node = list->current;
    }
    if (list->current->next != NULL)
    {
      list->current->next->prev = list->current;
    }
    if (list->current->prev != NULL)
    {
      list->current->prev->next = list->current;
    }
    /* check in LISTs too */
    for (i = 0; i < nli; i++)
    {
      if (lists[i].first == nodes + nni)
      {
        lists[i].first = list->current;
      }
      if (lists[i].last == nodes + nni)
      {
        lists[i].last = list->current;
      }
      if (lists[i].current == nodes + nni)
      {
        lists[i].current = list->current;
      }
    }
  }

  /* update LIST current */
  list->current = tmp_node;

  /* check if the NODEs need to be shrunk. Per design html, it says if you
   * using LESS than half and since nli is the NEXT ptr, this is not off by one 
   */
  if (nni < node_count / 2)
  {
    /* doesn't really matter if there's an error, just try again later */
    resize_nodes(false);
  }

  /* update item count */
  return item;
}


/*
 * Frees each item in the LIST using itemFree() and then frees the LIST.
 *
 * LIST *list: the LIST to empty and free
 * ItemFreer itemFree: the function which will handle freeing LIST items
 */
void ListFree(LIST *list, ItemFreer itemFree)
{
  long unsigned int i;
  NODE *walker, *next;
  LIST *user_key;

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

  printf("Got to procedure ListFree()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
      user_key = list;
      list = maps[i].real_ptr;
      break;
    }
  }


  /* delete all NODEs and free all items along the way */
  walker = list->first;
  while (walker != NULL)
  {
    /* track the next step */
    next = walker->next;

    itemFree(walker->item);
    /* access and "cover up" the current node */
    memmove(walker, list + nni - 1, sizeof(NODE));
    nni--;

    /* update all references to the moved [nni - 1] NODE */
    if (walker->next != NULL)
    {
      walker->next->prev = walker;
    }
    if (walker->prev != NULL)
    {
      walker->prev->next = walker;
    }
    /* check in LISTs too */
    for (i = 0; i < nli; i++)
    {
      if (lists[i].first == nodes + nni)
      {
        lists[i].first = walker;
      }
      if (lists[i].last == nodes + nni)
      {
        lists[i].last = walker;
      }
      if (lists[i].current == nodes + nni)
      {
        lists[i].current = walker;
      }
    }

    /* check if the NODEs need to be shrunk. Per design html, it says if you
     * are using LESS than half and since nli is the NEXT ptr, this is not off
     * by one */
    if (nni < node_count / 2)
    {
      /* result doesn't matter, on error just try again later */
      resize_nodes(false);
    }
    /* step to the next node to free */
    walker = next;
  }

  /* not checking the return, because pass or fail I don't really care if the
   * resize worked right now, again finite retrying */
  delete_list(user_key);

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
  void *item;
  unsigned long int i;
  NODE *tmp_node;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListTrim: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListTrim()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
      list = maps[i].real_ptr;
      break;
    }
  }

  /* no removal occurs if there is no last NODE */
  if (list->last == NULL)
  {
     return NULL;
  }

  /* update the NODE next to last */
  if (list->last->prev != NULL)
  {
    list->last->prev->next = NULL;
  }

  /* the new last NODE */
  tmp_node = list->last->prev;
  item = list->last->item;

  /* access and "cover up" the last NODE */
  memmove(list->last, nodes + nni - 1, sizeof(NODE));
  nni--;
  list->count--;

  /* update all references to the moved [nni - 1] NODE */
  if (list->last->next != NULL)
  {
    list->last->next->prev = list->last;
  }
  if (list->last->prev != NULL)
  {
    list->last->prev->next = list->last;
  }
  /* check in LISTs too */
  for (i = 0; i < nli; i++)
  {
    if (lists[i].first == nodes + nni)
    {
      lists[i].first = list->last;
    }
    if (lists[i].last == nodes + nni)
    {
      lists[i].last = list->last;
    }
    if (lists[i].current == nodes + nni)
    {
      lists[i].current = list->last;
    }
  }

  /* update LIST last */
  list->last = tmp_node;


  /* check if the NODEs need to be shrunk. Per design html, it says if you
   * using LESS than half and since nli is the NEXT ptr, this is not off by one 
   */
  if (nni < node_count / 2)
  {
    /* result doesn't matter on fail, just try again later */
    resize_nodes(false);
  }

  return item;
}

