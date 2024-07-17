#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/hash_table.h"

#define FIRST_PRIME 151
#define SECOND_PRIME 160

static inline int char_code(char character)
{
    return (int)character;
}

static struct hashtable_item HASHTABLE_DELETED_ITEM = {NULL, NULL};

static int hash(const char *value, const unsigned int prime, const int num_buckets)
{
    long out_index = 0;
    const int length_of_string = strlen(value);

    for (int i = 0; i < length_of_string; i++)
    {
        out_index += (long)pow(prime, length_of_string - (i + 1)) * char_code(value[i]);

        out_index = out_index % num_buckets;
    }

    return (int)out_index;
}

static int get_hash(const char *value, const unsigned int num_buckets, const int attempt)
{
    const int first_hash = hash(value, FIRST_PRIME, num_buckets);
    const int second_hash = hash(value, SECOND_PRIME, num_buckets);

    return (first_hash + (attempt * (second_hash + 1))) % num_buckets;
}

static void new_item(const char *key, const char *value, struct hashtable_item **out)
{
    *out = (struct hashtable_item *)malloc(sizeof(struct hashtable_item));

    (**out).key = strdup(key);
    (**out).value = strdup(value);
}

static void delete_item(struct hashtable_item *item)
{
    if (item == NULL)
    {
        return;
    }

    if (item->key != NULL)
    {
        free(item->key);
    }

    if (item->value != NULL)
    {
        free(item->value);
    }

    free(item);
}

struct hashtable *hashtable_new()
{
    struct hashtable *out = malloc(sizeof(struct hashtable));
    out->count = 0;
    out->size = MAX_NUMBER_OF_ITEMS;
    out->items = calloc(MAX_NUMBER_OF_ITEMS, sizeof(struct hashtable_item));

    return out;
}

void hashtable_cleanup(struct hashtable *hashtable)
{
    if (hashtable == NULL)
    {
        return;
    }

    for (int i = 0; i < hashtable->size; i++)
    {
        if (hashtable->items[i] != NULL)
        {
            delete_item(hashtable->items[i]);
        }
    }

    free(hashtable->items);
    free(hashtable);
}

void hashtable_insert(struct hashtable *hashtable, const char *key, const char *value)
{
    struct hashtable_item *item = NULL;

    new_item(key, value, &item);

    unsigned int index = get_hash(key, hashtable->size, 0);

    struct hashtable_item *current_item = hashtable->items[index];

    unsigned int attempt = 1;

    while (current_item != NULL)
    {
        index = get_hash(key, hashtable->size, attempt);
        current_item = hashtable->items[index];
        attempt++;
    }

    hashtable->items[index] = item;
    hashtable->count++;
}

char *hashtable_search(const struct hashtable *hashtable, const char *key)
{
    unsigned int index = get_hash(key, hashtable->size, 0);
    struct hashtable_item *current_item = hashtable->items[index];

    unsigned int attempt = 1;

    while (current_item != NULL)
    {
        if (current_item != &HASHTABLE_DELETED_ITEM && strcmp(current_item->key, key) == 0)
        {
            return current_item->value;
        }

        index = get_hash(key, hashtable->size, attempt);
        current_item = hashtable->items[index];
        attempt++;
    }

    return NULL;
}

void hashtable_delete(const struct hashtable *hashtable, const char *key)
{
    unsigned int index = get_hash(key, hashtable->size, 0);
    struct hashtable_item *current_item = hashtable->items[index];

    unsigned int attempt = 0;

    while (current_item != NULL)
    {
        if (current_item != &HASHTABLE_DELETED_ITEM)
        {
            if (strcmp(current_item->key, key) == 0)
            {
                delete_item(current_item);
                hashtable->items[index] = &HASHTABLE_DELETED_ITEM;
            }
        }

        index = get_hash(key, hashtable->size, attempt);
        current_item = hashtable->items[index];
        attempt++;
    }
}