/*
 * partA4.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625                
 * 11343891 & 11278140           
 * CMPT332 Fall 2025            
 *
 * This file implements the main executable for partA4. This executable
 * creates multiple processes which execute the same task until a deadline, 
 * without synchronization between processes. number of processes, 
 * length of deadline, and maximum integer size are to be command-line 
 * parameters. Process package used is UNIX processes.
 *
 * At this point, only skeletons with no full implementation will be present.
 *
 * - caller responsible for valid input, but also callee will perform input
 *   validation.                                                          
 */ 

#include <square.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_THREADS 1024

void invoke_square(int size);

typedef struct
{
  int thread_id;
  int size;
  volatile int *progress_count;
} ThreadArg

int main(int argc, char* argv)
{
  int i;
  int threads;
  int deadline;
  int size;
  int args[3];
  volatile int progress_count[MAX_THREADS];
  clock_t start_time[MAX_THREADS];
  clock_t end_time[MAX_THREADS];
  printf("Got to procedure main\n");
  
  /* argc validation */
  if (argc!=4)
  {
    printf("Error in procedure main: invalid number of params\n");
    return 1;
  }  

  /* convert args to integers */
  for (i=1;i<argc;i++)
  {
    if (!is_valid(argv[i]))
    {
      printf("Error in procedure main: invalid parameter %d\n/3",i);
      return 1;
    }
    else
    {
      args[i-1] = atoi(argv[i]);
    }
    /*args contain parsed parameters*/
  }

  if (args[0] >1024)
  {
    printf("Error in procedure main: invalid parameter 1\n");
    return 1;
  }
  threads = args[0];
  deadline = args[1];
  size = args[2];
 
  printf("Got to procedure Create()\n");
  /* Create Threads */
  for (i=0;i<threads;i++)
  {
    /* Record time */
    start_time[i] = clock();
    /*TODO:Create thread*/
    
  }
  
  /*Sleep for deadline*/
  sleep(deadline);
  
  for (i=0;i<threads;i++)
  {    
    /* TODO: Kill children*/
    end_time[i] = clock();
  }
  
  /* Report progress */
  for (i=0;i<threads;i++)
  {
    cpu_time = ((double)(end_time[i]-start_time[i]))/CLOCKS_PER_SEC;
    printf("Thread %d progress: %d/%d\n",i,progress_count[i],size);
    printf("Thread executed for %f seconds \n",cpu_time);
  }
  printf("square() invoked %d times\n",square_counter);
  return 0;
  /*Great success*/
  
}

/* Thread function */
/* Type invoke_squre(void* param)
 * {
 *   int i
 *   printf("Got to procedure invoke_square()");
 *   ThreadArg arg = (ThreadArg*)param;
 *   for (i=0;i<arg->size;i++)
 *   {
 *     arg->progress_count[arg->thread_id]++;
 *     square(i);
 *   }
 *   free(arg);
 *   printf("Got to end of invoke_square()");
 *   return 0;
 *   Great success
 *   
 * }*/
 
