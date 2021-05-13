//
// Created by nickf on 23/04/2021.
//

#ifndef TERMINALTEST_DATASTACK_H
#define TERMINALTEST_DATASTACK_H

#include <stdlib.h>

#define DEFAULT_INIT_SIZE 5
#define peek_first(type, list) (type *) impl_peek_first(list)
#define peek_last(type, list) (type *) impl_peek_last(list)
#define pop_first(type, list) (type *) impl_pop_first(list)
#define pop_last(type, list) (type *) impl_pop_last(list)
#define remove_at(list, index) impl_remove_at(list, index, &free)
#define obt(type, list, index) (type *) impl_obt(list, index)

#define str_alloc(str) impl_str_allocate(str)
#define int_alloc(num) impl_int_allocate(num)
#define float_alloc(num) impl_float_allocate(num)
#define wstr_alloc(str) impl_wstr_alloc(str)

#define generic_alloc(data, size_t) impl_generic_alloc(data, size_t)

typedef struct {
    void * data;
    size_t size;
} data_stack_element;

typedef struct {
    data_stack_element ** data;
    int capacity;
    int size;
} data_stack;

extern data_stack * of_size(int);
extern data_stack * empty();

extern void * impl_peek_first(const data_stack *);
extern void * impl_peek_last(const data_stack *);

extern void * impl_pop_first(data_stack *);
extern void * impl_pop_last(data_stack *);

extern void offer(data_stack *, data_stack_element *);
extern void impl_remove_at(data_stack *, int, void (*)(void*));
extern void * impl_obt(data_stack *, int);

extern int is_empty(const data_stack *);
extern data_stack_element * impl_str_allocate(char *);
extern data_stack_element * impl_int_allocate(int);
extern data_stack_element * impl_float_allocate(float);
extern data_stack_element * impl_wstr_alloc(wchar_t *);

/**
 *
 * @param void* assuming a malloc'd pointer
 * @return
 */
extern data_stack_element * impl_generic_alloc(void *, size_t);

#endif //TERMINALTEST_DATASTACK_H
