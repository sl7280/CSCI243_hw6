/**
*@
*
*
*
*
*/

/**
*Create a new, empty hashtable.
*@return the table, or NULL on allocation failure
*/
HashTable *ht_create(void){

}

/**
*Destroy a hashtable, freeing every key/value entry it ownes and the table itself safe to call on NULL
*@param self the table to destroy (may be NULL)
*/
void ht_destroy(HashTable *self){

}

/**
*Insert key with the given value, or replace the value if the key is already present
*@param self the table
*@param key the key to insert or update
*@param value the value to associate with key
*/
void ht_put(HashTable *self, int key, int value){

}

/**
*Look up key and return its value
*@param self the table
*@param key the key to look up
*@param found out-parameter: set to 1 if key was present, 0 otherwise
*@return the value associated with the key, or 0 if the key...
*/
int ht_contains(const HashTable *self, int key){

}

/**
*Remove key (and its value) from the table
*@param self the table
*@param key the key to remove
@return 1 if the key was present and removed, 0 if it was...
*/
int ht_remove(HashTable *self, int key){

}

/**
*Report how many key/value pairs the table holds
*@param self the table
*@return the number of entries
*/
size_t ht_size(const HashTable *self){

}
