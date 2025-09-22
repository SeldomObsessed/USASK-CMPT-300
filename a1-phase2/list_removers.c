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
  ptrdiff_t shift;

  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListRemove: invalid parameter list\n");
    return NULL;
  }

  printf("Got to procedure ListRemove()\n");

  /* access true LIST *ptr */
  for (i = 0; i < nli; i++)
  {
    if (list == maps[i].user_key)
    {
       list = maps[i].real_ptr;
       break;
    }
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

  /* the NODE after the initial current, which needs to be the final current */
  tmp_node = list->current->next;
  item = list->current->item;

  /* access and "cover up" the current node */
  memmove(list->current, nodes + nni - 1, sizeof(NODE));
  nni--;

  /* update all references to the moved [nni - 1] NODE */
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

  /* update LIST current */
  list->current = tmp_node;

  /* check if the NODEs need to be shrunk. Per design html, it says if you
   * using LESS than half and since nli is the NEXT ptr, this is not off by one 
   */
  if (nni < node_count / 2)
  {
    node_count /= 2;
    tmp_node = realloc(nodes, node_count * sizeof(NODE));
    if (tmp_node == NULL)
    {
      node_count *= 2;

      fprintf(
        stderr,
        "List_Remove could not reallocate from %lu to %lu NODEs\n",
        node_count,
        node_count / 2
      );
      /* no program abort, just try again later */
      return item;
    }

    /* update all NODE pointers*/
    if (nodes != tmp_node)
    {
      shift = tmp_node - nodes;
      /* from NODE to NODE */
      for (i = 0; i < nni; i++)
      {
        /* this might look sketchy, updating random garbage values, but due
         * to the fact that < nni is used, only active NODEs are touched */
        tmp_node[i].prev += tmp_node[i].prev == NULL ? 0 : shift;
        tmp_node[i].next += tmp_node[i].next == NULL ? 0 : shift;
      }
      /* from LIST to NODE */
      for (i = 0; i < nli; i++)
      {
        /* same as above, not touching garbage */
        lists[i].first += lists[i].first == NULL ? 0 : shift;
        lists[i].last += lists[i].last == NULL ? 0 : shift;
        lists[i].current += lists[i].current == NULL ? 0 : shift;
      }
    }
  }

  /* forget old block */
  nodes = tmp_node;

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
  NODE *walker, *tmp_node, *next;
  ptrdiff_t shift;
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
      node_count /= 2;
      tmp_node = realloc(nodes, node_count * sizeof(NODE));
      if (tmp_node == NULL)
      {
        node_count *= 2;

        fprintf(
          stderr,
          "List_Remove could not reallocate from %lu to %lu NODEs\n",
           node_count,
          node_count / 2
        );
        /* no program abort, just try again later */
        return;
      }

      /* update all NODE pointers*/
      if (nodes != tmp_node)
      {
        shift = tmp_node - nodes;
        /* from NODE to NODE */
        for (i = 0; i < nni; i++)
        {
          /* this might look sketchy, updating random garbage values, but due
           * to the fact that < nni is used, only active NODEs are touched */
          tmp_node[i].prev += tmp_node[i].prev == NULL ? 0 : shift;
          tmp_node[i].next += tmp_node[i].prev == NULL ? 0 : shift;
        }
        /* from LIST to NODE */
        for (i = 0; i < nli; i++)
        {
          /* same as above, not touching garbage */
          lists[i].first += lists[i].first == NULL ? 0 : shift;
          lists[i].last += lists[i].last == NULL ? 0 : shift;
          lists[i].current += lists[i].current == NULL ? 0 : shift;
        }
      }
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
  /* check that correct type and range of parameter values have been passed */
  if (list == NULL)
  {
    fprintf(stderr, "Error in procedure ListTrim: invalid parameter list\n");
    return NULL;
  }
  printf("Got to procedure ListTrim()\n");
  return NULL;
}

