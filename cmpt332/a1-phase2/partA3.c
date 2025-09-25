/*
 * partA3.c
 * Logan Fossenier & William Morris
 * hzv143 & wjm625                
 * 11343891 & 11278140           
 * CMPT332 Fall 2025            
 *
 * This file implements the main executable for partA3. This executable
 * creates multiple threads which perform the same action until a deadline, 
 * without synchronization between processes/threads. number of threads, 
 * length of deadline, and maximum integer size are to be command-line 
 * parameters. The package of threads used is POSIX threads.
 *
 * By time of submission, partA3 will be a fully implemented solution
 * - caller responsible for valid input, but also callee will perform input
 *   validation.                               
 */ 

#include <square.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 1024

void *invoke_square(void *param);

typedef struct
{
  int thread_id;
  int size;
  volatile int *square_count;
  volatile int *progress_count;
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
  /* int cpu_time; */
  ThreadArg arg[MAX_THREADS];
  volatile int square_count[MAX_THREADS];
  volatile int progress_count[MAX_THREADS+1];
  clock_t start_time[MAX_THREADS];
  clock_t end_time[MAX_THREADS];
  /* POSIX thread handle array */
  pthread_t handle[MAX_THREADS];
  int iret[MAX_THREADS];

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
  progress_count[MAX_THREADS] = 1;
  for (i=0;i<threads;i++)
  {
    /* initialize thread ard*/
    arg[i].size=size;
    arg[i].thread_id=i;
    arg[i].progress_count=progress_count;
    arg[i].start_time=start_time;
    arg[i].end_time=end_time;
    arg[i].square_count=square_count;
    /* Record time */
    start_time[i]=clock();
    /*TODO:Create thread*/
    iret[i] = pthread_create(
      /* handle */
      &handle[i],
      /* attributes - generic */
      NULL,
      /* function pointer */
      invoke_square,
      /* Single argument */
      (void *)&arg[i]
    );
    if (iret[i])
    {
      printf("Error in procedure: main\n pthread_create() failed\n");
      exit(1);
    }
  }
  
  /* Sleep for deadline */
  /* use of unistd.h */
  sleep((unsigned int)deadline);
  progress_count[MAX_THREADS]=0;
  for (i=0;i<threads;i++)
  {    
    /* TODO: Kill children*/
    end_time[i] = clock();
    /* set flag */
    progress_count[1024] = 0;
  }
  
  /* Report progress */
  /* for (i=0;i<threads;i++)
  {
    if (progress_count[i]<size)
    {
    cpu_time = ((double)(end_time[i]-start_time[i]))/CLOCKS_PER_SEC;
    printf("Thread %d progress: %d/%d\n",i,progress_count[i],size);
    printf("Thread %d executed for %d seconds \n",i,cpu_time);
    }
  } */
  printf("square() invoked total of  %d times\n",square_counter);
  return 0;
  /*Great success*/
}

/* Thread function */
void *invoke_square(void* param)
{
  int i;
  int cpu_time;
  
  ThreadArg *arg = (ThreadArg*)param;
  /* printf("Got to procedure invoke_square()"); */
  
  for (i=0;i<arg->size;i++)
  {
    /* Thread works until the flag is set to 0 */
    if (arg->progress_count[MAX_THREADS])
    {
      arg->progress_count[arg->thread_id]++;
      arg->square_count[arg->thread_id]++;
      square(i);
    }
    else
    {
      /**/
      printf("Thread %d terminated before completion\n",arg->thread_id);
      cpu_time = ((int)(arg->end_time[i]-arg->start_time[i]))/CLOCKS_PER_SEC;
      printf("Thread %d progress: %d/%d\n",arg->thread_id,
             arg->progress_count[arg->thread_id],arg->size);
      printf("Thread %d executed for %d seconds\n",arg->thread_id,cpu_time);
      printf("Thread %d invoked square() %d times\n",i,arg->square_count[i]);
      pthread_exit(NULL);
      /* success */
    }
  }
    printf("Thread %d finished exection\n",arg->thread_id); 
  cpu_time=((double)(arg->end_time[arg->thread_id]-
           arg->start_time[arg->thread_id]))/CLOCKS_PER_SEC;
  printf("Thread %d progress: %d/%d\n",arg->thread_id,
          arg->progress_count[arg->thread_id],arg->size);
  printf("Thread %d executed for %d seconds\n",arg->thread_id,cpu_time);   
  printf("Thread %d invoked square() %d times\n",arg->thread_id,
          arg->square_count[arg->thread_id]); 
  /* Great success */
  return NULL;
}

