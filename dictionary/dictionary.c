#include "string.h"
#include "dictionary.h"

dictionary *alloc_dictionary()
{
   dictionary *d = calloc( 1, sizeof( dictionary ) );
   d->keys = alloc_list();
   d->table = new_hash_table();

   return d;
}

void free_dictionary( dictionary *d )
{
   free_list( d->keys );
   free_hash_table( d->table );
   free( d );

   return;
}

int dictionary_add( void *content, char *key, dictionary *d )
{
   if( !hash_add( content, key, d->table ) )
      return 1;
   if( !list_append( strdup( key ), d->keys ) )
      return 1;

   return 0;
}

void *dictionary_remove( char *key, dictionary *d )
{
   void *ret = hash_get( key, d->table );
   if( ret == NULL )
      return NULL;
   
   char *c;
   reset_list_iterator( d->keys );
   while( ( c = (char *)next_in_list( d->keys ) ) != NULL )
      if( !strcmp( c, key ) )
         break;

   if( c )
   {
      list_remove( c, d->keys );
      free( c );
   }

   return ret;
}


void *dictionary_get( char *key, dictionary *d )
{
   return hash_get( key, d->table );
}

void dictionary_foreach( int (*func)( const void * ), dictionary *d )
{
   reset_list_iterator( d->keys );
   char *key;

   while( ( key = next_in_list( d->keys ) ) != NULL )
      func( hash_get( key, d->table ) );

   return;
}
