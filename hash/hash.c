#include "hash.h"

size_t strlen( char *str )
{
   size_t size = 0;
   while( str[size] != '\0' )
      size++;
   return size;
}

void *memcpy( void *dest, void *source, size_t size )
{
   char *dest1 = dest;
   char *source1 = source;

   while( size-- )
      dest1[size] = source1[size];

   return dest1;
}


int strcmp( const char *str1, const char *str2 )
{
   size_t i;
   for( i = 0; str1[i] != '\0' && str2[i] != '\0'; i++ )
      if( str1[i] != str2[i] )
         break;
   return str1[i] - str2[i];
}

char *strdup( char *str1 )
{
   size_t len = strlen( str1 );
   char *ret = calloc( len, sizeof( char ) );
   memcpy( ret, str1, len );

   return ret;
}

/*copied from http://www.cse.yorku.ca/~oz/hash.html*/
static unsigned long sdbm( char *str )
{
    unsigned long hash = 0;
    int c;

    while ( ( c = *str++ ) != 0x00 )
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

hash_table *new_hash_table()
{
   hash_table *table = calloc( 1, sizeof( hash_table ) );
   if( table == NULL )
      return NULL;

   size_t i;
   for( i = 0; i < MAX_BUCKETS; i++ )
      table->buckets[i] = NULL;

   return table;
}

void free_hash_table( hash_table *table, void(*func)( void *content ) )
{
   if( table->size > 0 )
   {
      size_t i;
      for( i = 0; i < MAX_BUCKETS; i++ )
      {
         if( func )
         {
            func( table->buckets[i]->content );
         }
         free( table->buckets[i] );
      }
   }
   free( table );
   return;
}

int hash_add( void *content, char *key, hash_table *table )
{
   unsigned long hash = sdbm( key );
   hash %= MAX_BUCKETS;
   hash_bucket *bucket;
   if( table->size >= MAX_BUCKETS ) /*Hash table is full*/
      return 1;
   while( ( bucket = table->buckets[hash] ) != NULL )
   {
      if( !strcmp( key, bucket->key ) )
         break;
      else
         hash = (hash + 1 ) % MAX_BUCKETS;
   }

   if( bucket == NULL )/*new*/
   {
      bucket = calloc( 1, sizeof( hash_bucket ) );
      if( bucket == NULL )
         return 2;
      bucket->key = strdup( key );
      bucket->content = content;
      bucket->hash = hash;
      table->buckets[hash] = bucket;
      table->size++;
   }
   else
   {
      bucket->content = content;
   }

   return 0;
}

void hash_mod( void *content, char *key, hash_table *table )
{
   hash_del( key, table );
   hash_add( content, key, table );
   return;
}

void *hash_get( char *key, hash_table *table )
{
   unsigned long hash = sdbm( key );
   hash_bucket *bucket;
   hash %= MAX_BUCKETS;

   while( ( bucket = table->buckets[hash] ) != NULL && hash < MAX_BUCKETS )
   {
      if( !strcmp( key, bucket->key ) )
         break;
      else
         hash = (hash + 1 ) % MAX_BUCKETS;
   }

   if( bucket == NULL )
      return NULL;

   return bucket->content;
}

void hash_del( char *key, hash_table *table )
{
   unsigned long hash = sdbm( key );
   hash %= MAX_BUCKETS;
   hash_bucket *bucket;
   if( table->size == 0 )
      return;
   while( ( bucket = table->buckets[hash] ) != NULL && hash < MAX_BUCKETS )
   {
      if( !strcmp( key, bucket->key ) )
         break;
      else
         hash = (hash + 1 ) % MAX_BUCKETS;
   }

   if( bucket == NULL )
      return;
   else
      free( table->buckets[hash] );
   table->size--;
   table->buckets[hash] = NULL;
   return;
}
