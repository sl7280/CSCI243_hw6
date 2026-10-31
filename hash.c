/**
*@
*
*
*
*
*/

#include <stddef.h>
#include <stdlib.h>

typedef struct Node{
    Struct Node *next_node;
    int key;
    int value;
}Node;

typedef struct HashTable{
    //pointer to a list of nodes (buckets) that can use their next_node in case two are mapped to the same index
    Node *buckets[10];
    size_t size;

}HashTable;


/**
*Create a new, empty hashtable.
*@return the table, or NULL on allocation failure
*/
HashTable *ht_create(void){
    Hashtable *new_hashtable = calloc(1, sizeof(Hashtable));

    if(new_hashtable == NULL){
        return(NULL);
    }
    return new_hashtable;
}


/**
*Destroy a hashtable, freeing every key/value entry it ownes and the table itself safe to call on NULL
*@param self the table to destroy (may be NULL)
*/
void ht_destroy(HashTable *self){
    
    //iterate thru all buckets
    for(int i = 0; i<=10; i++){
        
        //free the nodes in the bucket
        Node *node_actual = self->buckets[i];
        Node *node_siguiente = node_actual->next_node;
        
        //keep clearing nodes girl
        while(node_siguiente != NULL){
            free(node_actual);
            node_actual = node_siguiente;
            node siguiente = node_siguiente->next_node;
        }
    }
    free(self);
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
    int location = hash(key);
    Node *node_actual = buckets[location];
    while(node_actual != NULL){
        if(node_actual->key == key){
            return(1);
        }
        node_actual = node_actual->next_node;
    }
    //you didnt find it
    return(0);
}


/**
*Remove key (and its value) from the table
*@param self the table
*@param key the key to remove
@return 1 if the key was present and removed, 0 if it was...
*/
int ht_remove(HashTable *self, int key){
    int location = hash(key);
    
    //if empty
    if(self->buckets[location] == NULL){
        return(0);
    }

    //set current node
    Node *node_actual = self->buckets[location];
    
    //if first node is key
    if(node_actual->key == key){
        if(node_actual->next_node != NULL){
            self->buckets[location] = node_actual->next_node;
        }
        free(node_actual);
        self->size -=1;
        return(0);
    }
    
    //if node is buried deeper
    while(node_actual != NULL){
        if(node_actual->key == key){
            
            //get the next node if exists
            if(node_actual->next_node != NULL){
                Node *node_siguiente = node_actual->next_node;
                
                //remove the current node
                free(node_actual);
                Node *cur_node = self->buckets[location];
                while(cur_node->next_node != Null){
                    cur_node = cur_node->next_node;
                }

                //connect the gap that was created by free()
                cur_node->next_node = node_siguiente;
                self->size-=1;
                return (0);
            }

            //if there is nothing after desired node
            free(node_actual);
            self->size-=1;
            return(0);
        }
    }
}


/**
*Report how many key/value pairs the table holds
*@param self the table
*@return the number of entries
*/
size_t ht_size(const HashTable *self){
    return(self->size);
}
