#include "list.h"

dllist *alloc_list()
{
   return calloc( 1, sizeof( dllist ) );
}

static dllnode *alloc_node()
{
   return calloc( 1, sizeof( dllnode ) );
}

void free_list( dllist *list )
{
   free( list );
}

static size_t find_in_list( void *content, dllist *list )
{
   size_t loc = 0;

   dllnode *ptr = list->head;
   if( !ptr )
      return 0;
   do
   {
      loc++;
      if( content == ptr->content )
         break;
   }while( ( ptr = ptr->next ) != NULL );

   if( ptr == NULL )
      return 0;
   return loc;
}

int list_append( void *content, dllist *list )
{
   dllnode *node;
   if( !list || !content )
      return 1;

   if( find_in_list( content, list ) )
      return 1;

   if( ( node = alloc_node() ) == NULL )
      return 1;

   node->content = content;

   if( list->head == NULL )
      list->head = node;

   if( list->tail )
      list->tail->next = node;
   node->prev = list->tail;
   list->tail = node;
   list->size++;

   return 0;
}

int list_prepend( void *content, dllist *list )
{
   dllnode *node;
   if( !list || !content )
      return 1;

   if( find_in_list( content, list ) )
      return 1;

   if( ( node = alloc_node() ) == NULL )
      return 1;

   node->content = content;

   if( list->tail == NULL )
      list->tail = node;

   if( list->head )
      list->head->prev = node;
   node->next = list->head;
   list->head = node;
   list->size++;

   return 0;
}

int list_attach_sorted( void *content, dllist *list, int(*comp)( const void*, const void*) )
{
   if( !content || !list || !comp )
      return 1;

   dllnode *pNode = list->head, *nNode = NULL;
   
   while( pNode )
   {
      if( pNode->content == content )
         return 1;
      if( (*comp)(pNode->content, content) > 0 )
         break;
      pNode = pNode->next;
   }

   if( ( nNode = alloc_node() ) == NULL )
      return 1;
   nNode->content = content;
   
   if( pNode )
   {
      if( list->head == pNode ) /*We're inserting at the very beginning of the list*/
      {
         nNode->next = list->head;

         if (list->head != NULL)
            list->head->prev = nNode;
         if (list->tail == NULL)
            list->tail = nNode;
         list->tail->next = NULL;

         list->head = nNode;
      }
      else/*Inserting somewhere in the middle of the list*/
      {
         nNode->prev = pNode->prev;
         pNode->prev = nNode;
         nNode->next = pNode;
         nNode->prev->next = nNode;
      }
   }
   else /*Appending to the end of the list.*/
   {
      nNode->prev = list->tail;
      if( list->tail )
      {
         list->tail->next = nNode;
      }
      list->tail = nNode;
      if( list->head == NULL )
      {
         list->head = nNode;
      }
   }

   list->size++;
   return 0;
}

void *next_in_list( dllist *list )
{
   if( !list )
      return NULL;
   if( list->iterator == NULL )
      return NULL;

   void *ret = list->iterator->content;
   list->iterator = list->iterator->next;
   return ret;
}

void *prev_in_list( dllist *list )
{
   if( !list )
      return NULL;
   if( list->iterator == NULL )
      return NULL;

   void *ret = list->iterator->content;
   list->iterator = list->iterator->prev;
   return ret;
}

void reset_list_iterator( dllist *list )
{
   if( !list )
      return;
   list->iterator = list->head;
   return;
}

void set_list_iterator( dllist *list, size_t loc )
{
   if( loc == LIST_HEAD )
      list->iterator = list->head;
   else if( loc == LIST_TAIL )
      list->iterator = list->tail;
   else
   {
      list->iterator = list->head;
      while( loc && next_in_list( list ) )
         loc--;
   }
}

void *list_remove( void *content, dllist *list )
{
   dllnode *node;
   if( !content || !list )
      return NULL;

   node = list->head;
   while( node )
   {
      if( content == node->content )
         break;
      node = node->next;
   }

   if( !node ) /* Content not in list */
      return NULL;

   if( list->head == node )
      list->head = node->next;
   if( list->tail == node )
      list->tail = node->prev;
   if( node->prev )
      node->prev->next = node->next;
   if( node->next )
      node->next->prev = node->prev;
   free( node );
   return content;
}
