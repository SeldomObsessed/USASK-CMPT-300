/*
 * list_mem.h
 * Logan Fossenier & William Morris
 * hzv143 & wjm625
 * 11343891 & 11278140
 * CMPT332 Fall 2025
 */

/* 
 * This is a second .h file to hold the bonus question's helper functions 
 */

#ifndef LIST_INTERNAL_H
#define LIST_INTERNAL_H

#define TAG_MASK 0x0000FFFFFFFFFFFFUL /* this sets high 16 bits to 0 on & */

typedef struct map {
  LIST *user_key; /* what the program handed out, and what the user will use */
  LIST *real_ptr; /* where this list is in memory */
} MAP;

int delete_list(LIST *list);
int resize_nodes(bool grow);

#endif

