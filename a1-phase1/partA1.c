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
#include <stdio.h>                                                             
#include <windows.h>                                                            
                                                                                                                               
#define MAX_THREADS 1024                                                        
                                                                                
DWORD WINAPI invoke_square(LPVOID);   

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

  /*argc validation*/                                                         
  if (argc < 3)                                                                 
  {                                                                             
    printf("Usage: expecting 3 parameters\n");                                  
    exit(1);                                                                    
  }                                                                             
                                                                                
  int args[argc-1];                                                             
  /*argc validation done*/


  /*Converts args to integers*/                                                 
  for (int i =1; i<argc; i++)                                                   
  {                                                                             
    if (!is_valid(argv[i]))
    {                                                                           
      fprintf(stderr, "Error: argument '%s' is not an integer\n", argv[i]);     
    }             
                                                              
    args[i-1] = atoi(argv[i]);    
  }                                                              
  /*args[] contain parsed integer parameters*/    


  threads = args[0];
  if (threads>1024)
  {
    fprintf(stderr, "Error: arg 1, threads is not within thread limit
    of 1024\n");
  } 
  deadline = args[1];
  size = args[2];                                                 

  /*h_thread is an arr of thread handles, to allow
    interaction by sys calls */
  HANDLE h_thread[threads];
  /*shared array for ThreadArgs to access*/
  volatile int progress_count[threads];


  /*This for loop creates threads and */
  for (int i=0;i<threads;i++)
  {
    ThreadArg *arg = malloc(sizeof(ThreadArg));
    arg->thread_id=i;
    arg->size=size;
    /*pointer to the shared array*/
    arg->progress_count = progress_count;
    h_thread[i] = CreateThread(
        NULL,
        0,
        invoke_square,
        arg,
        0,
        i
    );

    if (h_thread[i]==NULL)
    {
        printf("Error creating thread %d\n", i);
        return 1;
    }

  }

  Sleep(1000*deadline);
  for (int i=0;i<threads; i++)
  {
    CloseHandle(h_thread[i]);
  }                      
  for (int i=0;i<threads;i++){
    printf("Thread %d reached %d\n",(i+1),progress_count[i]);
  }                                                     
}                                    

/*Thread function, entry point for CreateThread()*/
/*each thread will only go through this function once*/
DWORD WINAPI invoke_square(LPVOID param)
{
    ThreadArg *arg= (ThreadArg*)param;
    int limit = arg->size;
    for (int i=0; i<limit; i++)
    {
      square(i);
      arg->progress_count[arg->thread_id]=i;
    }
    free(arg);
    return (DWORD)arg->size;
}

