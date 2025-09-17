/*
 * list.h
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#ifndef LIST_H
#define LIST_H

/* represents a user's item in a LIST */
typedef struct node {
  void *item;        /* the item, always a pointer, must be homogenous */
  struct node *prev; /* the previous NODE, will be NULL at front of list */
  struct node *next; /* the next NODE, will be NULL at end of list */
} NODE;

/* contains a linked list of NODEs */
typedef struct list {
  int count;     /* number of NODEs in the list */
  NODE *current; /* the current element in the list */
  NODE *first;   /* head of the linked list */
  NODE *last;    /* tail of the linked liste */
} LIST;

/* user passed comparison function to search a LIST */
typedef int (*Comparator)(void *item, void *comparisonArg);
/* user passed item free() function to "release" items upon LIST deletion */
typedef void (*ItemFreer)(void *item);

/* adders */
LIST *ListCreate();
int ListAdd(LIST *list, void *item);
int ListInsert(LIST *list, void *item);
int ListAppend(LIST *list, void *item);
int ListPrepend(LIST *list, void *item);
int ListConcat(LIST *list1, LIST *list2);
NODE *get_node();

/* movers */
int ListCount(LIST *list);
void *ListFirst(LIST *list);
void *ListLast(LIST *list);
void *ListNext(LIST *list);
void *ListPrev(LIST *list);
void *ListCurr(LIST *list);
void *ListSearch(LIST *list, Comparator comparator, void *comparisonArg);

/* removers */
void *ListRemove(LIST *list);
void ListFree(LIST *list, ItemFreer itemFree);
void *ListTrim(LIST *list);

#endif

