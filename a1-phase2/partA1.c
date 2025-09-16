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
#include <stdlib.h>                                                             
                                                                                
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
    int i;                                                                
    int threads;                                                                
    int deadline;                                                               
    int size;                                                                   
    int args[3];  
    /* Thread handle array */                                                   
    HANDLE h_thread[MAX_THREADS];                                                   
    /* Shared progress array */                                                 
    volatile int progress_count[MAX_THREADS];                                                               
                                                                                
    printf("Got to procedure main\n");                                            
                                                                                
    /* argc validation */                                                       
    /* TODO: check argc, print usage, exit if not enough args*/                   
    if (argc != 4)                                                              
    {                                                                           
      printf("Error in procedure main: invalid number of parameters\n"); 
      return 1;         
    }                                                                           
    /* argc validation done */                                                  
                                                                                
    /* Convert args to integers */                                              
    for (i=1; i<argc; i++)                                                  
    {                                                                           
      if (!is_valid(argv[i]))                                                   
      {                                                                         
        printf("Error in procedure main: Invalid parameter %d\n/3",i);  
        return 1;            
      }                                                                         
      else                                                                      
      {                                                                         
        args[i-1] = atoi(argv[i]);                                              
      }                                                                         
    }                                                                           
    /* args[] contains parsed integer parameters */                             
                                                                                
    if (args[0] > 1024)                                                         
    {                                                                           
      printf("Error in procedure main: invalid parameter 1\n");  
      return 1;                 
    }                                                                           
    threads = args[0];                                                          
    deadline = args[1];                                                         
    size = args[2];                                                             
                                                                                
                                          
                                                                                
    /* Create threads */                                                        
    for (i=0; i<threads; i++)                                               
    {                                                                           
        /* TODO: allocate ThreadArg and call CreateThread() */                 
        ThreadArg *arg = malloc(sizeof(ThreadArg));                             
        if (!arg)                                                               
        {                                                                       
          printf("Error in procedure main: malloc failed at ThreadArg\n");   
          return 1;     
        }                                                                       
        arg->thread_id = i;                                                     
        arg->size = size;                                                       
        arg->progress_count = progress_count;                                   
        printf("Got to procedure CreateThread()\n");                              
        h_thread[i] = CreateThread(                                             
          NULL,                                                                 
          0,                                                                    
          invoke_square,                                                        
          arg,                                                                  
          0,                                                                    
          NULL);                                                                   
        if (h_thread[i]==NULL)                                                  
        {                                                                       
          printf("Error in procedure CreateThread: CreateThread failed\n");       
          return 1;                                                             
        }                                                                       
                                                                                
    }                                                                           
                                                                                
                                                                                
    /* Wait until deadline */                                                   
    /* TODO: Sleep for deadline in ms */                                           
                                                                                
    Sleep((DWORD)(1000*deadline));                                                       
    /* Close thread handles */                                                  
    for (i=0; i<threads; i++)                                               
    {                                                                           
        /* TODO: CloseHandle */                                                    
        printf("Got to procedure CloseHandle()\n");                               
        CloseHandle(h_thread[i]);                                               
    }                                                                           
                                                                                
    /* Report progress */                                                       
    for (i=0; i<threads; i++)                                               
    {                                                                           
        /* TODO: print progress_count[i] */                                        
    }                                                                           
                                                                                
    return 0;  /* success */                                                    
}                                                                               
                                                                                
/* Thread function */                                                           
DWORD WINAPI invoke_square(LPVOID param)                                        
{                
    int i;  
  /*Stop complaining mr gcc*/                                                               
    (void)param; 
    printf("Got to procedure invoke_square\n");                                   
    ThreadArg arg = (ThreadArg)param;
    for (i=0; i<arg->size; i++)
    {
      arg->progress++;
      square(i);
    }
    /* TODO: cast param to ThreadArg                                            
       TODO: run loop up to size                                                
       TODO: call square()                                                      
       TODO: update progress_count                                              
       TODO: free ThreadArg  */             
    int ret = arg->progress;                                      
    free(arg);                                                                
    return ret;
}     
