#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
#include "list.h"
#include "hash.h"

typedef struct s_dictionary dictionary;
typedef struct s_dictionary_entry dentry;

struct s_dictionary
{
   dllist      *keys;
   hash_table  *table;
};

struct s_dictionary_entry
{
   unsigned long int hash;
   char *key;
   void *content;
};

dictionary *alloc_dictionary();
void free_dictionary( dictionary *d );
int dictionary_add( void *content, char *key, dictionary *d );
void *dictionary_get( char *key, dictionary *d );
void dictionary_foreach( int (*func)( const void * ), dictionary *d );
void *dictionary_remove( char *key, dictionary *d );
#endif
