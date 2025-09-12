/*
 * list.h
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#ifndef LIST_H
#define LIST_H

typedef int (*Comparator)(void *item, void *comparisonArg);
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
void list_free(LIST *list);
void node_free(NODE *node);

#endif

