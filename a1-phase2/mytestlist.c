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

int main(void)
{
  LIST llist1;
  LIST *list1, *list2, *list3, *list4;
  int item1, item2, item3, item4;
  int result, i;
  void *result_ptr;


  /* list_adders.c tests */

  list1 = ListCreate(); /* 1 ListCreate */
  list2 = ListCreate();
  list3 = ListCreate(); /* 2 ListCreate */

  if (list1 == NULL || list2 == NULL || list3 == NULL)
  {
    fprintf(stderr, "Err ListCreate: ListCreate NULL return\n");
  }

  result = 0;
  item1 = 1;
  item2 = 2;
  item3 = 3;
  item4 = 4;
  result += ListAdd(NULL, &item1); /* 1 ListAdd */
  result += ListAdd(list1, NULL); /* 2 ListAdd */

  if (result != -2)
  {
    fprintf(stderr, "Err ListAdd: ListAdd wrong return value (-2)\n");
  }
  result = 0;

  result += ListAdd(list1, &item1); /* 3 ListAdd */
  result += ListAdd(list1, &item2); /* 4 ListAdd */
  /* list should be (1 -> c[2]) */
  result_ptr = ListCurr(list1);
  if (result_ptr != &item2)
  {
    fprintf(stderr, "Err ListAdd: ListCurr wrong ptr return\n");
  }
  result_ptr = ListPrev(list1);
  if (result_ptr != &item1)
  {
    fprintf(stderr, "Err ListPrev: ListPrev wrong ptr return\n");
  }
  result_ptr = ListFirst(list1);
  if (result_ptr != &item1)
  {
    fprintf(stderr, "Err ListAdd: ListFirst wrong ptr return\n");
  }
  result_ptr = ListLast(list1);
  if (result_ptr != &item2)
  {
    fprintf(stderr, "Err ListAdd: ListLast wrong ptr return\n");
  }
  

  ListFirst(list1);
  /* list should be (c[1] -> 2) */
  result += ListAdd(list1, &item3); /* 5 ListAdd */
  /* list should be (1 -> c[3] -> 2) */
  if (*(int *)ListCurr(list1) != 3)
  {
     fprintf(stderr, "Err ListAdd: ListAdd wrong current value (3)\n");
  }

  result_ptr = ListRemove(list1);
  /* list should be (1 -> c[2]) */
  if (*(int *)ListCurr(list1) != 2)
  {
    fprintf(stderr, "Err ListAdd: ListCurr wrong ptr return\n");
  }
  if (result_ptr != &item3)
  {
    fprintf(stderr, "Err ListAdd: ListRemove wrong ptr return\n");
  }
  /* demonstrate shrink ability */
  result_ptr = ListRemove(list1);
  /* list should be c[](1) */
  if (result_ptr != &item2)
  {
    fprintf(stderr, "Err ListAdd: ListRemove wrong ptr return\n");
  }
  if (ListCurr(list1) != NULL)
  {
    fprintf(stderr, "Err ListAdd: ListCurr wrong ptr return\n");
  }
  if (ListFirst(list1) != &item1)
  {
    fprintf(stderr, "Err ListAdd: ListFirst wrong ptr return\n");
  }
  if (ListLast(list1) != &item1)
  {
    fprintf(stderr, "Err ListAdd: ListLast wrong ptr return\n");
  }
  if (ListPrev(list1) != NULL)
  {
    fprintf(stderr, "Err ListAdd: ListPrev wrong ptr return\n");
  }
  ListFirst(list1);
  if (ListNext(list1) != NULL)
  {
    fprintf(stderr, "Err ListAdd: ListPrev wrong ptr return\n");
  }

  result_ptr = ListLast(list1);
  /* list should be (c[1]) */
  if (result_ptr != &item1)
  {
    fprintf(stderr, "Err ListAdd: ListLast wrong ptr return\n");
  }
  result += ListAdd(list1, &item2);
  /* list should be (1 -> c[2]) */

  result += ListAdd(list1, &item3); /* 6 ListAdd */
  /* list should be (1 -> 2 -> c[3]) */
  if (*(int *)ListCurr(list1) != 3)
  {
    fprintf(stderr, "Err ListAdd: ListCurr wrong ptr return\n");
  }

  result_ptr = ListNext(list1);
  /* list should be c[](1 -> 2 -> 3) */
  if (result_ptr != NULL)
  {
    fprintf(stderr, "Err ListAdd: ListNext wrong ptr return\n");
  }

  result += ListAdd(list1, &item4); /* 7 ListAdd */
  /* list should be (1 -> 2 -> 3 -> c[4]) */
  result_ptr = ListCurr(list1);
  if (result_ptr != &item4)
  {
    fprintf(stderr, "Err ListAdd: ListCurr wrong ptr return\n");
  }

  list4 = &llist1;
  ListAdd(list4, &item1); /* 8 ListAdd */

  ListFirst(list1);
  for (i = 4; i > 0; i--)
  {
    ListRemove(list1);
  }
  if (ListLast(list1) != NULL || ListFirst(list1) != NULL ||
      ListCurr(list1) != NULL)
  {
    fprintf(stderr, "Err ListAdd: ListRemove did not clear list\n");
  }

  if (result !=  0)
  {
    fprintf(stderr, "Err ListAdd: non-zero returns\n");
  }

  result = 0;
  result += ListInsert(NULL, &item1); /* 1 ListInsert */
  result += ListInsert(list1, NULL); /* 2 ListInsert */
  if (result != -2)
  {
    fprintf(stderr, "Err ListInsert: ListInsert not reporting errors\n");
  }  

  result = 0;
  result += ListInsert(list1, &item1); /* 3 ListInsert */
  result += ListInsert(list1, &item2); /* 4 ListInsert */
  /* list should be (c[2] -> 1) */
  if (ListCurr(list1) != &item2)
  {
    fprintf(stderr, "Err ListInsert: ListCurr wrong ptr return\n");
  }
  if (ListLast(list1) != &item1)
  {
    fprintf(stderr, "Err ListInsert: ListLast wrong ptr return\n");
  }

  ListFirst(list1);
  /* list should be (c[2] -> 1) */
  result += ListInsert(list1, &item3); /* 5 ListInsert */
  /* list should be (c[3] -> 2 -> 1) */
  if (ListCurr(list1) != &item3)
  {
    fprintf(stderr, "Err ListInsert: ListCurr wrong ptr return\n");
  }
  if (ListLast(list1) != &item1)
  {
    fprintf(stderr, "Err ListInsert: ListFirst wrong ptr return\n");
  }

  ListRemove(list1);
  ListLast(list1);
  /* list should be (3 -> c[2]) */
  result += ListInsert(list1, &item1); /* 6 ListInsert */
  /* list should be (3 -> c[1] -> 2) */
  if (ListCurr(list1) != &item1)
  {
    fprintf(stderr, "Err ListInsert: ListCurr wrong ptr return\n");
  }
  if (ListFirst(list1) != &item3)
  {
    fprintf(stderr, "Err ListInsert: ListFirst wrong ptr return\n");
  }
  if (ListNext(list1) != &item1 || ListNext(list1) != &item2 ||
      ListNext(list1) != NULL)
  {
    fprintf(stderr, "Err ListInsert: List not joined properly\n");
  }

  /* list should be c[](3 -> 1 -> 2) */
  result += ListInsert(list1, &item4); /* 7 ListInsert */
  /* list should be (c[4] -> 3 -> 1 -> 2) */
  if (ListCurr(list1) != &item4)
  {
    fprintf(stderr, "Err ListInsert: ListCurr wrong ptr return\n");
  }
  if (ListNext(list1) != &item3)
  {
    fprintf(stderr, "Err ListInsert: ListNext wrong ptr return\n");
  }

  if (result != 0)
  {
    fprintf(stderr, "Err ListInsert: non-zero returns\n");
  }

  result = 0;
  result += ListAppend(NULL, &item1); /* 1 ListAppend */
  result += ListAppend(list2, NULL); /* 2 ListAppend */
  if (result != -2)
  {
    fprintf(stderr, "Err ListAppend: ListAppend not reporting errors\n");
  }

  result = 0;
  result += ListAppend(list2, &item1); /* 3 ListAppend */
  result += ListAppend(list2, &item2); /* 4 ListAppend */
  /* list should be (1 -> c[2]) */
  if (ListCurr(list2) != &item2)
  {
    fprintf(stderr, "Err ListAppend: ListCurr wrong ptr return\n");
  }
  if (ListNext(list2) != NULL)
  {
    fprintf(stderr, "Err ListAppend: ListNext shows not linked right\n");
  }
  if (ListLast(list2) != &item2)
  {
    fprintf(stderr, "Err ListAppend: ListLast wrong ptr return\n");
  }
  if (ListPrev(list2) != &item1 || ListPrev(list2) != NULL)
  {
    fprintf(stderr, "Err ListAppend: ListPrev shows not linked right\n");
  }
  if (ListFirst(list2) != &item1)
  {
    fprintf(stderr, "Err ListAppend: ListFirst wrong ptr return\n");
  }

  ListLast(list2);
  ListRemove(list2);
  /* list should be c[](1) */
  ListAppend(list2, &item3); /* 5 ListAppend */
  /* list should be (1 -> c[3]) */
  if (ListCurr(list2) != &item3)
  {
    fprintf(stderr, "Err ListAppend: ListCurr wrong ptr return\n");
  }
  if (ListPrev(list2) != &item1)
  {
    fprintf(stderr, "Err ListAppend: ListPrev shows not linked right\n");
  }
  if (ListPrev(list2) != NULL)
  {
    fprintf(stderr, "Err ListAppend: ListPrev shows not linked right\n");
  }

  ListAppend(list4, &item3); /* 6 ListAppend */

  return 0;
}


int mainp(int argc, char **argv)
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

