/*
 * filename.(c/h)
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdio.h>

#include <list.h>


int mock_comparator(void *item, void *comparisonArg)
{
  /* Dispeling compiler warnings */
  int x;
  x = 3;
  item = &x;
  comparisonArg = item;
  item = comparisonArg;
  return 0;
}


void mock_itemFreer(void *item)
{
  /* Dispeling compiler warnings */
  int x;
  x = 3;
  item = &x;
  if (item)
  {
    return;
  }
  return;
}


int main(int argc, char **argv)
{
  LIST *list1, *list2;
  int item1, item2, item3;

  int result, item;
  LIST *my_list, *my_list2;
  LIST local_list2;
  ItemFreer item_free;
  Comparator comparator;

  /* dispell compiler complaints */
  argc++;
  argv[0][0] = 'a';

  /* list_adders.c tests */
  list1 = ListCreate(); /* ListCreate happy path */
  list2 = ListCreate();

  ListAdd(NULL, &item); /* 1 ListAdd unhappy path (list) */
  ListAdd(list1, NULL); /* 2 ListAdd unhappy path (item) */
  result = 0;
  item1 = 42;
  item2 = 777;
  item3 = 1;

  result += ListAdd(list1, &item1); /* 3 ListAdd happy path */
  result += ListAdd(list1, &item1); /* 4 ListAdd happy path */
  list1->current = list1->first; /* (relatively) safe to -> at low counts */
  result += ListAdd(list1, &item2); /* 5 ListAdd happy path */
  if (
    list1->current->item != &item2 ||
    list1->current->prev->item != &item1
  )
  {
    result += 1;
  }
  

  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListAdd, non-zero return");
  }
  

  my_list = ListCreate();
  ListAdd(list2, &item3);

  ListInsert(NULL, &item); /* ListInsert unhappy path (list) */
  ListInsert(my_list, NULL); /* ListInsert unhappy path (item) */
  result = ListInsert(my_list, &item); /* ListInsert happy path */
  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListInsert, non-zero return");
  }

  ListAppend(NULL, &item); /* ListAppend unhappy path (list) */
  ListAppend(my_list, NULL); /* ListAppend unhappy path (item) */
  result = ListAppend(my_list, &item); /* ListAppend happy path */
  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListAppend, non-zero return");
  }

  ListPrepend(NULL, &item); /* ListPrepend unhappy path (list) */
  ListPrepend(my_list, NULL); /* ListPrepend unhappy path (item) */
  result = ListPrepend(my_list, &item); /* ListPrepend happy path */
  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListPrepend, non-zero return");
  }

  my_list2 = &local_list2;
  ListConcat(NULL, my_list); /* ListPrepend unhappy path (list1) */
  ListConcat(my_list, NULL); /* ListPrepend unhappy path (list2) */
  ListConcat(my_list, my_list); /* ListPrepend unhappy path (list1 == list2) */
  result = ListConcat(my_list, my_list2); /* ListPrepend happy path */
  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListConcat, non-zero return");
  }


  my_list = ListCreate();
  item = 42;

  /* list_removers.c tests */
  ListRemove(NULL); /* ListRemove unhappy path (list) */
  ListRemove(my_list); /* ListRemove happy path */

  item_free = mock_itemFreer;
  ListFree(NULL, item_free); /* ListFree unhappy path (list) */
  ListFree(my_list, NULL); /* ListFree unhapp apth (itemFree) */
  ListFree(my_list, item_free); /* ListFree happy path */

  ListTrim(NULL); /* ListTrim unhappy path (list) */
  ListTrim(my_list); /* ListTrim happy path */

  /* list_movers.c tests */
  ListCount(NULL); /* ListCount unhappy path (list) */
  ListCount(my_list); /* ListCount happy path */

  ListFirst(NULL); /* ListFirst unhappy path (list) */
  ListFirst(my_list); /* ListFirst happy path */

  ListLast(NULL); /* ListLast unhappy path (list) */
  ListLast(my_list); /* ListLast happy path */

  ListNext(NULL); /* ListNext unhappy path (list) */
  ListNext(my_list); /* ListNext happy path */

  ListPrev(NULL); /* ListPrev unhappy path (list) */
  ListPrev(my_list); /* ListPrev happy path */

  ListCurr(NULL); /* ListCurr unhappy path (list) */
  ListCurr(my_list); /* ListCurr happy path */

  comparator = mock_comparator;
  /* &item is passed as the comparator, anything goes, (even NULL) */
  ListSearch(NULL, comparator, &item); /* ListSearch unhappy path (list) */
  ListSearch(my_list, NULL, &item); /* ListSearch unhappy path (comparator) */
  ListSearch(my_list, comparator, &item); /* ListSearch happy path */

  return 0;
}

