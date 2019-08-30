#ifndef __HASH_H__
#define __HASH_H__
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BUCKETS 4096  /*Adjust as necessary*/

typedef struct s_hash_table hash_table;
typedef struct s_hash_bucket hash_bucket;

struct s_hash_table
{
   size_t           size;
   hash_bucket    * buckets[MAX_BUCKETS];
};

struct s_hash_bucket
{
   unsigned long    hash;
   void           * content;
   char           * key;
};

hash_table *new_hash_table();
void free_hash_table( hash_table *table );
bool hash_add( void *content, char *key, hash_table *table );
void *hash_get( char *key, hash_table *table );
void hash_del( char *key, hash_table *table );
void hash_mod( void *content, char *key, hash_table *table );
#endif
