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
 */

#include <square.h>                                                             
#include <stdio.h>                                                             
#include <windows.h>                                                            
                     
#define MAX_THREADS 1024                                                        
                                                                                
DWORD WINAPI invoke_square(LPVOID);   

/* ThreadArg type to be passed into CreatThread */
typedef struct
{
  int thread_id;
  int size;
  volatile int *progress_count;
} ThreadArg;   

int main (int argc, char *argv[])                                           
{                   
    int threads;
    int deadline;
    int size;

    /* argc validation */
    // TODO: check argc, print usage, exit if not enough args

    int args[argc-1];                                                             
    /* argc validation done */

    /* Convert args to integers */
    // TODO: loop through argv, validate, convert to int, store in args[]
    /* args[] contains parsed integer parameters */

    threads = args[0];
    deadline = args[1];
    size = args[2];                                                 

    /* Thread handle array */
    HANDLE h_thread[threads];

    /* Shared progress array */
    volatile int progress_count[threads];

    /* Create threads */
    for (int i=0; i<threads; i++)
    {
        // TODO: allocate ThreadArg and call CreateThread()
    }

    /* Wait until deadline */
    // TODO: Sleep for deadline in ms

    /* Close thread handles */
    for (int i=0; i<threads; i++)
    {
        // TODO: CloseHandle
    }                      

    /* Report progress */
    for (int i=0; i<threads; i++)
    {
        // TODO: print progress_count[i]
    }     

    return 0;  /* success */
}                                    

/* Thread function */
DWORD WINAPI invoke_square(LPVOID param)
{
    // TODO: cast param to ThreadArg
    // TODO: run loop up to size
    // TODO: call square()
    // TODO: update progress_count
    // TODO: free ThreadArg

    return 0;  /* success */
}

