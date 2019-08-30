#include <stdio.h>
#include <string.h>
#include "list.h"

int cmp( const void *a, const void *b )
{
   const char *A = a, *B = b;
   return( strcmp( A, B ) );
}

int main( int argc, char *argv[] )
{
   dllist *list = alloc_list();
   char *str = strdup( "Test" );

   list_attach_sorted( strdup( "AAA" ), list, cmp );
   list_attach_sorted( strdup( "CCC" ), list, cmp );
   list_attach_sorted( strdup( "BBB" ), list, cmp );
   list_attach_sorted( str, list, cmp );

   reset_list_iterator( list );

   char *c;
   fprintf( stdout, "Forwards:\n" );
   while( ( c = (char *) next_in_list( list ) ) != NULL )
   {
      fprintf( stdout, "%s\n", c );
   }

   fprintf( stdout, "Backwards:\n" );
   set_list_iterator( list, LIST_TAIL );

   while( ( c = (char*)prev_in_list( list ) ) != NULL )
   {
      fprintf( stdout, "%s\n", c );
   }

   list_remove( str, list );
   reset_list_iterator( list );
   fprintf( stdout, "\n**REMOVAL**\n" );
   free( str );
   fprintf( stdout, "Forwards:\n" );
   while( ( c = (char *) next_in_list( list ) ) != NULL )
   {
      fprintf( stdout, "%s\n", c );
   }

   fprintf( stdout, "Backwards:\n" );
   set_list_iterator( list, LIST_TAIL );

   while( ( c = (char*)prev_in_list( list ) ) != NULL )
   {
      fprintf( stdout, "%s\n", c );
   }

   return 0;
}
