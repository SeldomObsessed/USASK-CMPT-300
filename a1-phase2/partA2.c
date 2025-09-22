/*
 * partA2.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625                
 * 11343891 & 11278140           
 * CMPT332 Fall 2025            
 *
 * This file implements the main executable for partA2. This executable
 * creates multiple threads which perform the same action until a deadline, 
 * without synchronization between processes/threads. number of threads, 
 * length of deadline, and maximum integer size are to be command-line 
 * parameters. The package of threads used is UBC pthreads.
 *
 * At time of submission, this code should compile and work as expected.
 *
 * - caller responsible for valid input, but also callee will perform input
 *   validation.                                                          
 */ 

#include <square.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <standards.h>
#include <os.h>

#define MAX_THREADS 1024

void invoke_square(int size);

typedef struct
{
  int thread_id;
  int size;
  volatile int *square_count; 
  volatile int *progress_count;
  /* New: so child can print stats */
  clock_t *start_time;
  clock_t *end_time;
} ThreadArg;

int main(int argc, char* argv)
{
  int i;
  int threads;
  int deadline;
  int size;
  int args[3];
  double cpu_time;
  volatile int square_count[MAX_THREADS];
  volatile int progress_count[MAX_THREADS];
  clock_t start_time[MAX_THREADS];
  clock_t end_time[MAX_THREADS];
  PID handle[MAX_THREADS];
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
    ThreadArg arg = malloc(sizeof(ThreadArg));
    arg->size=size;
    arg->thread_id=i;
    arg->progress_count=progress_count;
    arg->start_time=start_time;
    arg->end_time=end_time;
    arg->square_count=square_count;
    handle[i] = Create(
      invoke_square,
      16000,
      "child"
      arg,
      NORM,
      USR
    );
    

  }
  
  /*Sleep for deadline*/
  sleep(deadline);
  
  for (i=0;i<threads;i++)
  {    
    /* TODO: Kill children*/
    if(progress_count[i]<size)
    {
      end_time[i] = clock();
      Kill(handle[i]);
    }
  /* Report progress */
    if (progress_count[i]<size)
    {
      printf("Thread %d terminated before completion\n",i);
      cpu_time = ((double)(end_time[i]-start_time[i]))/CLOCKS_PER_SEC;
      printf("Thread %d progress: %d/%d\n",i,progress_count[i],size);
      printf("Thread executed for %f seconds \n",cpu_time);
    }
  printf("square() invoked %d times\n",square_counter);
  return 0;
  /*Great success*/
}

/* Thread function */
void invoke_squre(void* param)
{
  int i
  int cpu_time;
  printf("Got to procedure invoke_square()");
  ThreadArg arg = (ThreadArg*)param;
  for (i=0;i<arg->size;i++)
  {
    square_counter++;
    arg->square_count[i]++;
    arg->progress_count[arg->thread_id]++;
    square(i);
  }
  free(arg);
  printf("Thread %d finished exection\n");
  cpu_time=((double)(arg->end_time[thread_id]-arg->start_time[thread_id]))
           /CLOCKS_PER_SEC;
  printf("Thread %d progress: %d/%d\n",thread_id,size,size);
  printf("Thread executed for %f seconds \n",cpu_time); 
  return 0;
  /* Great success */
}

