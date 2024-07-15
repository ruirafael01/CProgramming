#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/hash_table.h"

static inline int char_code(char character)
{
    return (int)character;
}

int get_hash(char *value, unsigned int prime, struct hashtable *hashtable)
{
    long out_index = 0;
    const int length_of_string = strlen(value);

    for (int i = 0; i < length_of_string; i++)
    {
        out_index += (long)pow(prime, length_of_string - (i + 1)) * char_code(value[i]);

        out_index = out_index % hashtable->size;
    }

    return (int)out_index;
}

static void new_item(char *key, char *value, struct hashtable_item **out)
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

void hashtable_delete(struct hashtable *hashtable)
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
