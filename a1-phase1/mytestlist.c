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
  int result, item;
  LIST *my_list, *my_list2;
  LIST local_list, local_list2;
  ItemFreer item_free;

  /* dispell compiler complaints */
  argc++;
  argv[0][0] = 'a';

  /* list_adders.c tests */
  my_list  = ListCreate(); /* ListCreate happy path */

  item = 42;
  ListAdd(my_list, &item); /* ListAdd unhappy path (list) */
  my_list = &local_list;
  ListAdd(my_list, NULL); /* ListAdd unhappy path (item) */
  result = ListAdd(my_list, &item); /* ListAdd happy path */
  if (result != 0)
  {
    fprintf(stderr, "Error in procedure ListAdd, non-zero return");
  }

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

  /* list_removers.c tests */
  ListRemove(NULL); /* ListRemove unhappy path (list) */
  ListRemove(my_list); /* ListRemove happy path */

  item_free = mock_itemFreer;
  ListFree(NULL, item_free); /* ListFree unhappy path (list) */
  ListFree(my_list, NULL); /* ListFree unhapp apth (itemFree) */
  ListFree(my_list, item_free); /* ListFree happy path */

  ListTrim(NULL); /* ListTrim unhappy path (list) */
  ListTrim(my_list); /* ListTrim happy path */

  return 0;
}

