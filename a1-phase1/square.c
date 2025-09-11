/*
 * square.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

#include <stdlib.h>


int Square(int N)
{
  if (N==0)
  { 
    return 0;
  }
  else 
  {
    return (Square(N-1) + N + N -1);
  }
}


/**/
int is_valid(char *argv)
{
  return (strtol (argv, NULL, 10));
}
