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
#include <strsafe.h>                                                             
                                                                                
/*TODO update after testing*/                                                   
#define MAX_THREADS 1024                                                        
                                                                                
DWORD WINAPI invoke_square(LPVOID);                                                                                                                
/*                                                                            
 * Main entry point.                                                            
 *                                                                              
 * Will take 3 parameters, only accepts integers:                               
 *   1: no. of threads to spawn                                                 
 *   2: length of deadline                                                      
 *   3: parameter passed to square()                                            
 */                                                                             
                                                                                
int main (int argc, char *argv[])                                           
{                   
  int threads;
  int deadline;
  int size;

  /*input validation*/                                                         
  if (argc < 3)                                                                 
  {                                                                             
    printf("Usage: expecting 3 parameters\n");                                  
    exit(1);                                                                    
  }                                                                             
                                                                                
  int args[argc-1];                                                             
  /*input validation done*/

  /*Converts args to integers*/                                                 
  for (int i =1; i<argc; i++)                                                   
  {                                                                             
    if (!is_valid(argv[i]))
    {                                                                           
      fprintf(stderr, "Error: argument '%s' is not an integer\n", argv[i]);     
    }             
    if (i==1 && argv[i]>1024)
      {
        fprintf(stderr, "Error:'%s' threads is not within thread limit
        of 1024\n",argv[i]);
      }                                                              
    args[i-1] = atoi(argv[i]);    

  }                                                              
  /*args[] contain parsed integer parameters*/    

  threads = args[0];
  deadline = args[1];
  size = args[2];                                                 
  /*TODO write function calls*/

  /*h_thread is an arr of thread handles, to allow
    interaction of threads
    thread_id is an array of, put simply, 
    thread identifiers.*/

  HANDLE h_thread[threads];
  DWORD thread_id[threads];
  for (i=0;i<threads;i++)
  {
    hThread[i] = CreateThread(
        NULL,
        0,
        invoke_square,
        (LPVOID)size,
        0,
        &thread_id[i];
    );

    if (h_thread[i]==NULL)
    {
        printf("Error creating thread %d\n", i)
        return 1;
    }
  }
                                                                                
}                                    

/*Thread function, entry point for CreateThread()*/
/*each thread will only go through this function once*/
DWORD WINAPI invoke_square(LPVOID goal)
{
    int progress=0;
    int limit = (int)(intptr_t)goal;
    for (progress; progress<limit; progress++)
    {
      square(progress);
    }
    return (DWORD)progress;
}  
 
