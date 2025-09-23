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
#include <os.h>

#define MAX_THREADS 1024

void invoke_square(void *param);

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

int main(int argc, char* argv[])
{
  int i;
  int threads;
  int deadline;
  int size;
  int args[3];
  long cpu_time;
  ThreadArg arg[MAX_THREADS];
  volatile int square_count[MAX_THREADS];
  volatile int progress_count[MAX_THREADS];
  long start_time[MAX_THREADS];
  long end_time[MAX_THREADS];
  PID handle[MAX_THREADS];
  /* printf("Got to procedure main\n"); */
  
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
 
  /* printf("Got to procedure Create()\n"); */
  /* Create Threads */
  for (i=0;i<threads;i++)
  {
    arg[i].size=size;
    arg[i].thread_id=i;
    arg[i].progress_count=progress_count;
    arg[i].start_time=start_time;
    arg[i].end_time=end_time;
    arg[i].square_count=square_count;
    /* Record time */
    start_time[i] = Time();
    /* Create Thread */
    handle[i] = Create(
      (void(*)()) invoke_square,
      16000,
      "child",
      (void *)&arg[i],
      NORM,
      USR
    );
  }
  /*Sleep for deadline*/
  Sleep(deadline*100);
  
  for (i=0;i<threads;i++)
  {    
    /* TODO: Kill children*/
    if(progress_count[i]<size)
    {
      end_time[i] = Time();
      Kill(handle[i]);
    }
  /* Report progress */
    if (progress_count[i]<size)
    {
      printf("Thread %d terminated before completion\n",i);
      cpu_time = ((end_time[i]-start_time[i]));
      printf("Thread %d progress: %d/%d\n",i,progress_count[i],size);
      printf("Thread %d executed for %ld seconds \n",i,cpu_time);
      printf("Thread %d invoked square() %d times\n",i,square_count[i]);
    }
  }
  printf("square() invoked %d times in total\n",square_counter);
  return 0;
  /*Great success*/
}

/* Thread function */
void invoke_square(void *param)
{
  int i;
  long cpu_time;
  ThreadArg *arg = (ThreadArg*)param;
  int id = arg->thread_id;
  /* printf("Got to procedure invoke_square()"); */
  for (i=0;i<arg->size;i++)
  {
    square_counter++;
    arg->square_count[id]++;
    arg->progress_count[id]++;
    square(i);
  }
  arg->end_time[id] = Time();
  printf("Thread %d finished exection\n",id);
  cpu_time=((arg->end_time[id]-arg->start_time[id]));
  printf("Thread %d progress: %d/%d\n",id,arg->size,arg->size);
  printf("Thread %d executed for %ld seconds \n",id,cpu_time); 
  /* Great success */
}

