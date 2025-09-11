/*
 * partA1.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 *
 * This file implements the main executable for A.1. This executable creates
 * multiple threads which perform the same action until a deadline, without 
 * synchronization between processes/threads. number of threads, length of
 * deadline, and maximum integer size are to be command-line parameters.
 *
 * At this point, only skeletons with no full implementation will be present.
 * 
 * - caller responsible for valid input, but also callee will perform input 
 *   validation.
 * /
 

#include <square.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include strsafe.h>

/*TODO update after testing*/
#define MAX_THREADS 1024 

DWORD WINAPI MyThreadsFunction( LPVOID lpParam);
void ErrorHandler(LPCSTR lpszFunction); 

/*
 * Main entry point.
 *
 * Will take 3 parameters, only accepts integers: 
 *   1: no. of threads to spawn
 *   2: length of deadline
 *   3: parameter passed to square()
 */

int main void(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Usage: expecting 3 parameters\n");
    exit(1);
  }

  int args[argc-1];
  
  /*Converts args to integers*/
  for (int i =1; i<argc; i++)
  {
    if !(is_valid(argv[i]))
    /*TODO write int is_valid(int x) in square.c and add sign to square.h*/
    {
      fprintf(stderr, "Error: argument '%s' is not an integer\n", argv[i]);
    }
    args[i-1] = atoi(argv[i]);
  }

  /*args[] contain parsed integers*/

  /*TODO write function calls*/  
  
}
