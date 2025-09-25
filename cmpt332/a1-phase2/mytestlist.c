/*
 * mytestlist.c
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
  LIST *list1, *list2, *list3, *list4, *list5, *list6;
  int item1, item2, item3, item4;
  int result, i;
  void *result_ptr;

  printf("Welcome to the tests!\n\n"
          "If you see \"Error\" that means an API function was successfully\n"
          "forced into generating an expected error.\n\n"
          "If you see \"Err\" that means the test suite is reporting errors\n"
          "in the API\n\n\n");

  /* list_adders.c tests */

  printf("\nBegin ListCreate()\n\n");

  list1 = ListCreate(); /* 1 ListCreate */
  list2 = ListCreate();
  list3 = ListCreate(); /* 2 ListCreate */

  if (list1 == NULL || list2 == NULL || list3 == NULL)
  {
    fprintf(stderr, "Err ListCreate: ListCreate NULL return\n");
  }

  printf("\nBegin ListAdd()\n\n");

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

  if (result != 0)
  {
    fprintf(stderr, "Err ListAdd: non-zero returns\n");
  }

  list4 = &llist1;
  result = ListAdd(list4, &item1); /* 8 ListAdd */
  if (result != -1)
  {
    fprintf(stderr, "Err ListAdd: does not report errors correctly\n");
  }

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

  printf("\nBegin ListInsert()\n\n");

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

  result += ListInsert(list4, &item1); /* 8 ListInsert */
  if (result != -1)
  {
    fprintf(stderr, "Err ListInsert: not reporting errors\n");
  }

  printf("\nBegin ListAppend()\n\n");

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

  if (result != 0)
  {
    fprintf(stderr, "Err ListAppend: non-zero returns\n");
  }

  result = ListAppend(list4, &item3); /* 6 ListAppend */
  if (result != -1)
  {
    fprintf(stderr, "Err ListAppend: not reporting errors\n");
  }

  printf("\nBegin ListPrepend()\n\n");

  result = 0;
  result += ListPrepend(NULL, &item1); /* 1 ListPrepend */
  result += ListPrepend(list3, NULL); /* 2 ListPrepend */
  if (result != -2)
  {
    fprintf(stderr, "Err ListPrepend: not reporting errors\n");
  }

  result = 0;
  result += ListPrepend(list3, &item1); /* 3 ListPrepend */
  result += ListPrepend(list3, &item2); /* 4 ListPrepend */
  /* List should be (c[2] -> 1) */
  if (ListCurr(list3) != &item2 || ListFirst(list3) != &item2)
  {
    fprintf(stderr, "Err ListPrepend: ListFirst wrong ptr return\n");
  }
  if (ListNext(list3) != &item1 || ListLast(list3) != &item1)
  {
    fprintf(stderr, "Err ListPrepend: ListLast wrong ptr return\n");
  }

  result += ListPrepend(list3, &item3); /* 5 ListPrepend */
  /* List should be (c[3] -> 2 -> 1) */
  if (ListCurr(list3) != &item3 || ListFirst(list3) != &item3)
  {
    fprintf(stderr, "Err ListPrepend: ListFirst wrong ptr return\n");
  }
  if (ListNext(list3) != &item2)
  {
    fprintf(stderr, "Err ListPrepend: ListNext wrong ptr return\n");
  }

  if (result != 0)
  {
    fprintf(stderr, "Err ListPrepend: non-zero returns\n");
  }

  result += ListPrepend(list4, &item4);
  if (result != -1)
  {
    fprintf(stderr, "Err ListPrepend: not reporting errors\n");
  }

  printf("\nBegin ListConcat()\n\n");

  result = 0;
  result += ListConcat(NULL, list1); /* 1 ListConcat */
  result += ListConcat(list1, NULL); /* 2 ListConcat */
  result += ListConcat(list1, list1); /* 3 ListConcat */
  if (result != -3)
  {
    fprintf(stderr, "Err ListConcat: not reporting errors\n");
  }

  list5 = ListCreate();
  list6 = ListCreate();
  result = 0;
  result += ListConcat(list5, list6); /* 4 ListConcat */
  if (ListFirst(list5) != NULL || ListLast(list5) != NULL)
  {
    fprintf(stderr, "Err ListConact: failed on two empty lists\n");
  }

  list6 = ListCreate();
  result += ListConcat(list2, list5); /* 5 ListConcat */

  return 0;
}

