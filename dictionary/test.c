#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int upper( const void *c )
{
   char *C = (char *)c;
   size_t i = 0;
   for( i = strlen( C ); i; i-- )
   {
      C[i] = toupper( C[i] );
   }
   C[0] = toupper( C[0] );

   return 0;
}

int print( const void *c )
{
   char *C = (char *)c;
   fprintf( stdout, "%s\n", C );
   return 0;
}

int main( int argc, char *argv[] )
{
   dictionary *d = alloc_dictionary();
   dictionary_add( strdup( "this is a test" ), "Test", d );
   dictionary_add( strdup( "this is also a test" ), "Test2", d );

   dictionary_add( strdup( "aaAAaaAAaaAA" ), "123", d );

   dictionary_foreach( upper, d );
   dictionary_foreach( print, d );

   fprintf( stdout, "\n*Removing key '123'*\n" );
   dictionary_remove( "123", d );
   dictionary_foreach( print, d );

   return 0;
}
