#include <stdio.h>

#include "../include/hash_table.h"

int main(int argc, char *argv[])
{
    struct hashtable *hashtable = hashtable_new();

    printf("Index generated %d\n", get_hash("cat", 151, hashtable));

    printf("Created hashtable!\n");

    hashtable_delete(hashtable);

    printf("Deleted hashtable!\n");
}