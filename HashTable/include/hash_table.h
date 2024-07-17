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

char *hashtable_search(const struct hashtable *hashtable, const char *key);

void hashtable_insert(struct hashtable *hashtable, const char *key, const char *value);

void hashtable_delete(const struct hashtable *hashtable, const char *key);

struct hashtable *hashtable_new();

void hashtable_cleanup(struct hashtable *hashtable);

#endif