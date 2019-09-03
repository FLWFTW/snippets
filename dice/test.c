#include <stdio.h>
#include "dice.h"


int main( int argc, char *argv[] )
{
   if( argc < 2 )
   {
      fprintf( stderr, "Supply a dice equation <num>d<size><mod><num> ie: 5d6+3 for the sum of the roll of 5, 6 sided dice + 3\n" );
      return -1;
   }
   srand( time( NULL ) );

   fprintf( stdout, "%s = %zu\n", argv[1], dice( argv[1] ) );
   return 0;
}

