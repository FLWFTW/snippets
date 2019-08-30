#ifndef __LIST_H__
#define __LIST_H__
#include <stdlib.h>
#include <stdint.h>

#define LIST_HEAD 0
#define LIST_TAIL SIZE_MAX

typedef struct s_list dllist;
typedef struct s_list_node dllnode;


dllist *alloc_list();
void free_list( dllist *list );
int list_append( void *content, dllist *list );
int list_prepend( void *content, dllist *list );
int list_attach_sorted( void *content, dllist *list, int(*comp)( const void*, const void*) );
void *next_in_list( dllist *list );
void *prev_in_list( dllist *list );
void reset_list_iterator( dllist *list );
void set_list_iterator( dllist *list, size_t loc );

struct s_list
{
   dllnode *head;
   dllnode *tail;

   dllnode *iterator;
   size_t size;
};

struct s_list_node
{
   dllnode *prev;
   dllnode *next;

   void *content;
};
#endif
