#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

// Define a generic list structure
typedef struct {
    void **items;
    size_t size;
    size_t capacity;
} List;

// Initialize the list
void list_init(List *list, size_t capacity) {
    list->items = (void **)malloc(capacity * sizeof(void *));
    list->size = 0;
    list->capacity = capacity;
}

// Add an item to the list
void list_add(List *list, void *item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->items = (void **)realloc(list->items, list->capacity * sizeof(void *));
    }
    list->items[list->size++] = item;
}

// Get an item from the list
void *list_get(List *list, size_t index) {
    if (index >= list->size) return NULL;
    return list->items[index];
}

// Remove an item from the list
void list_remove(List *list, size_t index) {
    if (index >= list->size) return;
    free(list->items[index]);
    for (size_t i = index; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    list->size--;
}

// Free the list memory
void list_free(List *list) {
    free(list->items);
    list->size = 0;
    list->capacity = 0;
    list->items = NULL;
}

#endif // LIST_H

