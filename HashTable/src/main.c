#include <stdio.h>

#include "../include/hash_table.h"

#define HASHTABLE_KEY "Rui"
#define HASHTABLE_VALUE "Test with Hash Table"

int main(int argc, char *argv[])
{
    struct hashtable *hashtable = hashtable_new();

    hashtable_insert(hashtable, HASHTABLE_KEY, HASHTABLE_VALUE);

    printf("Inserted new item\n");

    char *value = hashtable_search(hashtable, HASHTABLE_KEY);

    if (value == NULL)
    {
        printf("Value not found\n");
    }
    else
    {
        printf("Value found %s\n", value);
    }

    hashtable_delete(hashtable, HASHTABLE_KEY);

    printf("Key was deleted!\n");
    
    value = hashtable_search(hashtable, HASHTABLE_KEY);

    if (value == NULL)
    {
        printf("Value not found\n");
    }
    else
    {
        printf("Value found %s\n", value);
    }

    hashtable_cleanup(hashtable);

    printf("Deleted hashtable!\n");
}