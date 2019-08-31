#include <stdio.h>
#include <string.h>
#include "hash.h"

int main( int argc, char *argv[] )
{
   hash_table *table = new_hash_table();
   
   if( hash_add( strdup( "This is the first content." ), "first", table ) != 0 )
      fprintf( stdout, "Error!" );
   hash_add( strdup( "This is the second content." ), "second", table );
   hash_add( strdup( "This is the third content." ), "third", table );

   fprintf( stdout, "First content: %s\n", (char *)hash_get( "first", table ) );
   fprintf( stdout, "Second content: %s\n", (char *)hash_get( "second", table ) );
   fprintf( stdout, "Third content: %s\n", (char *)hash_get( "third", table ) );

   fprintf( stdout, "\n**Deleting entry 'second'**\n" );
   hash_del( "second", table );
   fprintf( stdout, "**Modifying entry 'third'**\n\n" );
   hash_mod( strdup( "This has been modified." ), "third", table );

   fprintf( stdout, "First content: %s\n", (char *)hash_get( "first", table ) );
   fprintf( stdout, "Second content: %s\n", (char *)hash_get( "second", table ) );
   fprintf( stdout, "Third content: %s\n", (char *)hash_get( "third", table ) );

   free_hash_table( table, NULL );

   return 0;
}
   
