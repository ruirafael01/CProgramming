#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_NUMBER_OF_ITEMS 53

struct hashtable_item
{
    char *key;
    char *value;
};

struct hashtable
{
    unsigned int size;
    unsigned int count;
    struct hashtable_item **items;
};

int get_hash(char *value, unsigned int prime, struct hashtable *hashtable);

struct hashtable *hashtable_new();

void hashtable_delete(struct hashtable *hashtable);

#endif