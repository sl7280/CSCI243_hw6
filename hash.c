/**
*@file hash.c
*@brief implementing a hashtable from hash.h
*
*@author Stephanie Livingston <sl7280@rit.edu>
*@Course CSCI-243 hw 6
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define NUM_DE_CUBO 16

typedef struct Node{
    struct Node *next_node;
    int key;
    int value;
}Node;

typedef struct HashTable{
    //pointer to a list of nodes (buckets) that can use their next_node in case two are mapped to the same index
    Node *buckets[NUM_DE_CUBO];
    size_t size;

}HashTable;


/**
*Create a new, empty hashtable.
*@return the table, or NULL on allocation failure
*/
HashTable *ht_create(void){
    HashTable *new_hashtable = calloc(1, sizeof(HashTable));

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
    if(self == NULL){
        return;
    }
    //iterate through buckets
    for(int i = 0; i < NUM_DE_CUBO; i++){
        Node *cur_node = self->buckets[i];
        Node *to_del = cur_node;
        
        //iterate through nodes in bucket[i]
        if(cur_node != NULL){
            while(cur_node != NULL){
                to_del = cur_node;
                cur_node = cur_node->next_node;
                free(to_del);
            }
            
        }
    }
    free(self);
    return;
}


/**
*Insert key with the given value, or replace the value if the key is already present
*@param self the table
*@param key the key to insert or update
*@param value the value to associate with key
*/
void ht_put(HashTable *self, int key, int value){
    if(self == NULL){
        return;
    }
    unsigned int location = key % NUM_DE_CUBO;
    printf("dubugging location for negitives: %d", location);
    Node *node_at_location = self->buckets[location];
    
    //creaete the new node
    Node *new_bucket = malloc(sizeof(Node));

    //failsafe
    if(new_bucket == NULL){
        return;
    }

    new_bucket->key = key;
    new_bucket->value = value;
    new_bucket->next_node = NULL;
    
    //if no bucket
    if(node_at_location == NULL){
        self->buckets[location] = new_bucket;
        self->size += 1;
        //printf("put %d %d", key, value);
        return;
    }

    //there is at least one bucket already
    while(node_at_location != NULL){

        //key already exists; update value
        if(node_at_location->key == key){
            node_at_location->value = value;
          //  printf("put %d %d", key, value);
            free(new_bucket);
            return;
        }

        //add new buck to end
        if(node_at_location->next_node == NULL){
            node_at_location->next_node = new_bucket;
            self->size += 1;
            //printf("put %d %d", key, value);
            return;
        }
        node_at_location = node_at_location->next_node;
    }
    return;
}

/**
*get a constant value 
*@param self the table
*@param key the key
*@param found 1 if found 0 if not
*@return the value from the key
*/
int ht_get(const HashTable *self, int key, int *found){
    if(self == NULL){
        return(0);
    }

    unsigned int location = key % NUM_DE_CUBO;

    *found = 0;

    Node *bucket = self->buckets[location];
    while(bucket != NULL){
        if(bucket->key == key){
            *found = 1;
            return (bucket->value);
        }
        bucket = bucket->next_node;
    }
    return(0);
}


/**
*Look up key and return its value
*@param self the table
*@param key the key to look up
*@param found out-parameter: set to 1 if key was present, 0 otherwise
*@return the value associated with the key, or 0 if the key...
*/
int ht_contains(const HashTable *self, int key){

    if(self == NULL){
        //printf("contains %d -> no", key);
        return(0);
    }

    int location = key % NUM_DE_CUBO;
    Node *node_actual = self->buckets[location];
    while(node_actual != NULL){
        if(node_actual->key == key){
      //      printf("contains %d -> yes", key);
            return(1);
        }
        node_actual = node_actual->next_node;
    }
    //you didnt find it
    //printf("contains %d -> no", key);
    return(0);
}


/**
*Remove key (and its value) from the table
*@param self the table
*@param key the key to remove
*@return 1 if the key was present and removed, 0 if it wasnt.
*/
int ht_remove(HashTable *self, int key){
    if(self == NULL){
        return(0);
    }

    int location = key % NUM_DE_CUBO;
    
    //if empty
    if(self->buckets[location] == NULL){
        //printf("remove %d -> absent", key);
        return(0);
    }

    //set current node and prev node
    Node *node_actual = self->buckets[location];
    Node *node_anterior = NULL;

    while(node_actual != NULL){
        //if current node is key
        if(node_actual->key == key){
            //if there are nodes after, connect them to the previous one
            if(node_actual->next_node != NULL){
                //if its the first node with some after
                if(node_anterior == NULL){
                    self->buckets[location] = node_actual->next_node;
                    free(node_actual);
                    self->size-=1;
                    return(1);
                }
                //if it's in the middle with some after 
                else{
                    node_anterior->next_node = node_actual->next_node;
                    free(node_actual);
          //          printf("remove %d -> removed", key);
                    self->size -=1;
                    return(1);
                }
            }
            //it is the last node
            if(node_anterior != NULL){
                node_anterior->next_node = NULL;
                free(node_actual);
        //        printf("remove %d -> removed", key);
                self->size -=1;
                return(1);
            }
            //it is the only node
            free(node_actual);
      //      printf("remove %d -> removed", key);
            self->size -=1;
            return(1);

        }
        node_anterior = node_actual;
        node_actual = node_actual->next_node;
            
    }
    return(0);
}


/**
*Report how many key/value pairs the table holds
*@param self the table
*@return the number of entries
*/
size_t ht_size(const HashTable *self){
    if(self == NULL){
        return(0);
    }
    //printf("size -> %zu", self->size);
    return(self->size);
}
