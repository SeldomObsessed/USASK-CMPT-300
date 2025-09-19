/*
 * list_mem.h
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

/* 
 * This is a second .h file to hold the bonus question's helper functions 
 * and since I've made it anyway, I'm throwing all the non user-facing extern
 * variables in here 
 * */

#ifndef LIST_INTERNAL_H
#define LIST_INTERNAL_H

typedef struct map {
  LIST *user_key; /* what the program handed out, and what the user will use */
  LIST *real_ptr; /* where this list is in memory */
} MAP;

#endif

