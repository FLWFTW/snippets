#include "dice.h"

#define MAX_STRING_LENGTH 64

static size_t roll( size_t min, size_t max )
{
   /* see: http://www.iso-9899.info/wiki/Snippets#Ranged_Random_Number */
   return (int) ( ( ( max * rand() )/RAND_MAX ) + min );
}

size_t dice( char *str2 )
{
   size_t result = 0, num = 0, size = 0, mod = 0, i = 0, len = 0;
   char operator = '\0', buf[MAX_STRING_LENGTH], *str;
   strncpy( buf, str2, MAX_STRING_LENGTH );
   len = strlen( buf );
   str = buf;

   for( i = 0; i < len; i++ )
   {
      if( toupper( str[i] ) == 'D' )
      {
         str[i] = '\0';
         break;
      }
   }

   num = strtoul( str, NULL, 10 );
   i++;
   str += i;
   len = strlen( str );

   for( i = 0; i < len; i++ )
   {
      if( str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' )
      {
         operator = str[i];
         str[i] = '\0';
         break;
      }
   }

   size = strtoul( str, NULL, 10 );
   i++;
   str += i;
   mod = strtoul( str, NULL, 10 );

   if( num == 0 || size == 0 )
   {
      return 0;
   }

   for( i = 0; i < num; i++ )
   {
      result += roll( 1, size );
   }

   switch( operator )
   {
      case '+':
         result += mod;
         break;
      case '-':
         result -= mod;
         break;
      case '/':
         if( mod == 0 ) mod = 1;
         result /= mod;
         break;
      case '*':
         result *= mod;
         break;
      case '^':
         result = pow( result, mod );
         break;
      default:
         break;
   }

   return result;
}

