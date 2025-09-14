/*
 * filename.(c/h)
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdio.h>

#include <list.h>

int main(int argc, char **argv)
{
  int result, item;
  LIST *my_list;
  LIST local_list;

  /* dispell compiler complaints */
  argc++;
  argv[0][0] = 'a';

  my_list  = ListCreate();
  my_list = &local_list;
  item = 42;

  result = ListAdd(my_list, &item);
  if (result == 0)
  {
    printf("Hey that worked \n");
  }
  return 0;
}

