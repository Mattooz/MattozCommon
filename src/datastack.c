//
// Created by nickf on 23/04/2021.
//

#include "../include/datastack.h"
#include <string.h>
#define MALLOC_DATA_ELEMENT malloc(sizeof(data_stack_element *))

data_stack *of_size(int initial_size) {
    data_stack *result = (data_stack *) malloc(sizeof(data_stack));
    result->size = 0;
    result->capacity = initial_size;
    result->data = malloc(initial_size * sizeof(data_stack_element *));

    for (int i = 0; i < initial_size; i++) result->data[i] = NULL;

    return result;
}

data_stack *empty() {
    return of_size(DEFAULT_INIT_SIZE);
}

void *impl_peek_first(const data_stack *list) {
    if (is_empty(list)) return NULL;

    return list->data[0]->data;
}

void *impl_peek_last(const data_stack *list) {
    if (is_empty(list)) return NULL;

    return list->data[list->size - 1]->data;
}

void *impl_pop_first(data_stack *list) {
    if (is_empty(list)) return NULL;
    void *result = malloc(list->data[0]->size);

    memcpy(result, list->data[0]->data, list->data[0]->size);
    remove_at(list, 0);

    return result;
}

void *impl_pop_last(data_stack *list) {
    if (is_empty(list)) return NULL;
    void *result = malloc(list->data[list->size - 1]->size);
    memcpy(result, list->data[list->size - 1]->data, list->data[list->size - 1]->size);
    remove_at(list, list->size - 1);

    return result;
}

void offer(data_stack *list, data_stack_element * element) {
    if (list->size == list->capacity)
        list->data = realloc(list->data, (list->capacity += DEFAULT_INIT_SIZE) * sizeof(void *));
    list->data[list->size++] = element;
}

void impl_remove_at(data_stack *list, int at, void (*free_func)(void *)) {
    if (is_empty(list) || at < 0 || at >= list->size) return;

    free_func(list->data[at]->data);
    free(list->data[at]);
    for (int i = 0; i < list->capacity; i++) {
        if (i >= at) {
            if (i < list->size) {
                if (i < (list->size - 1))
                    list->data[i] = list->data[(i + 1)];
                else
                    list->data[i] = NULL;
            } else {
                list->data[i] = NULL;
            }
        }
    }

    list->size--;
}

void *impl_obt(data_stack *list, int at) {
    if (is_empty(list) || at < 0 || at >= list->size) return NULL;
    return list->data[at]->data;
}

int is_empty(const data_stack *list) {
    return list->size == 0;
}

data_stack_element *impl_str_allocate(char *string) {
    data_stack_element * element = MALLOC_DATA_ELEMENT;
    void *copy = malloc(strlen(string) + 1);
    strcpy((char *) copy, string);
    element->data = copy;
    element->size = strlen(string) + 1;
    return element;
}

data_stack_element *impl_int_allocate(int num) {
    data_stack_element * element = MALLOC_DATA_ELEMENT;
    void *copy = malloc(sizeof(int));
    *((int *) copy) = num;
    element->data = copy;
    element->size = sizeof(int);
    return element;
}

data_stack_element *impl_float_allocate(float num) {
    data_stack_element * element = MALLOC_DATA_ELEMENT;
    void *copy = malloc(sizeof(float));
    *((float *) copy) = num;
    element->data = copy;
    element->size = sizeof(float);
    return element;
}

data_stack_element *impl_wstr_alloc(wchar_t * wstring) {
    data_stack_element * element = MALLOC_DATA_ELEMENT;
    void *copy = malloc(wcslen(wstring) + 1);
    wcscpy((wchar_t *) copy, wstring);
    element->data = copy;
    element->size = wcslen(wstring) + 1;
    return element;
}

data_stack_element * impl_generic_alloc(void * data, size_t size) {
    data_stack_element * element = MALLOC_DATA_ELEMENT;
    element->data = data;
    element->size = size;
    return element;
}