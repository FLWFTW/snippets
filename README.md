# Snippets

## list
A generic doubly-linked list.
-`dllist *alloc_list()` Allocates a new linked list
-`int list_append( void *content, dllist *list )` appends an item to the linked list. Returns 0 on success, 1 on failure (Either the item is already in the list, or it couldn't allocate memory to create a new node in the list)
-`int list_prepend( void *content, dllist *list)` Same as above, only it attaches it to the head of the list.
-`int list_attach_sorted( void *content, dllist *list, int(*comp)(const void*, const void*) )` Inserts content into the list sorted by the provided sorting function.
-`void *next_in_list( dllist *list )` Returns the next item in a list, using an internal iterator managed by the list.
-`void *prev_in_list( dllist *list )` Returns the previous item in a list, using an internal iterator managed by the list.
-`void reset_list_iterator( dllist *list )` Points the list's internal iterator to the head of the list.
-`void set_list_iterator( dllist *list, size_t loc )` Points the list's internal iterator to the nth item in the list specified by loc. If given LIST_HEAD or LIST_TAIL as an argument, will point the iterator to the head or tail.
-`void list_remove( void *content, dllist *list )` Removes the item 'content' from the list specified.

## hash
A generic hash table
-`hash_table *new_hash_table()` Creates a new hash table.
-`void free_hash_table( hash_table *table )` Frees an allocated hash table.
-`bool hash_add( void *content, char *key, hash_table *table )` Adds content to hash table with the specified key.
-`void *hash_get( char *key, hash_table *table )` Returns the content with the specified key from the hash table.
-`void hash_del( char *key, hash_table *table )` Deletes the item specified by key from the hash table. Note: This does not free any memory allocated to the specific item.
-`void hash_mod( void *content, char *key, hash_table *table )` Modifies the specified item in the hash table.

## Dictionary
A generic dictionary.
-`dictionary *alloc_dictionary()` Creates a new dictionary.
-`void free_dictionary( dictionary *d )` Frees the specified dictionary.
-`int dictionary_add( void *content, char *key, dictionary *d )` Adds an item to the specified dictionary.
-`void *dictionary_get( char *key, dictionary *d )` Gets the specified item from the dictionary.
-`void dictionary_foreach( int (*func)( const void * ), dictionary *d )` Runs the specified function on each entry in the dictionary.
-`void *dictionary_remove( char *key, dictionary *d )` Removes the specified item from the dictionary. Returns a pointer to the removed item.
