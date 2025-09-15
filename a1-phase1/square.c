/*
 * square.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 *
 * This file implements the Square function and the is_valid function. 
 * Square is the recursive procedure to keep the CPU busy. 
 *
 * is_valid is a parsing check that verifies if the argument passed
 * is a valid number: >0 and not a string or float.
 */

#include <stdlib.h>
#include <stddef.h>

/*Global variable to increment Square invocation*/
int square_counter = 0;

int square(int N)
{

  square_counter++;
  if (N==0)
  { 
    return 0;
  }
  else 
  {
    return (square(N-1) + N + N -1);
  }
}


/**/
int is_valid(char *argv)
{
  
  int num;
  /*string check*/
  if (!(strtol (argv, NULL, 10)))
  {
    return 0;
  }
  
  num = strtol(argv,NULL,10);
  /*negative number check*/
  if (num<0)
  {
    return 0;
  }
  return 1;
}
