//
// Created by nickf on 27/04/2021.
//

#ifndef TERMINALTEST_STRINGBUILDER_H
#define TERMINALTEST_STRINGBUILDER_H
#include <stdio.h>

#define DEFAULT_INI_CAPACITY 5
#define NULL_POS_INDEX -1
#define EMPTY_POS (str_pos) {NULL_POS_INDEX, NULL_POS_INDEX}

typedef struct {
    int start;
    int end;
} str_pos;

typedef struct {
    char * buffer;
    size_t capacity;
} str_builder;

str_builder * sbof_size(int);
str_builder * sb_empty();
str_builder * sbof_str(char *);

str_builder * append_str(str_builder *, char *);
str_builder * append_char(str_builder *, char);
str_builder * append_int(str_builder *, long long);
str_builder * append_uint(str_builder *, unsigned long long);
str_builder * append_double(str_builder *, double);

str_builder * concat_builder(str_builder *, str_builder *);

int index_of_char(str_builder *, char);
str_pos index_of_str(str_builder *, const char *);

str_builder * delete_str(str_builder *, char *);
str_builder * delete_sec(str_builder *, str_pos);
str_builder * delete_char(str_builder *, char);

char * cstr(str_builder *);
int sbsize(str_builder *);

void free_str_builder(void *);

typedef struct {
    wchar_t * buffer;
    size_t capacity;
} wstr_builder;

wstr_builder * wbof_size(int);
wstr_builder * wb_empty();
wstr_builder * wbof_str(wchar_t *);

wstr_builder * wappend_str(wstr_builder *, char *);
wstr_builder * wappend_wstr(wstr_builder *, wchar_t *);
wstr_builder * wappend_char(wstr_builder *, char);
wstr_builder * wappend_wchar(wstr_builder *, wchar_t);
wstr_builder * wappend_int(wstr_builder *, long long);
wstr_builder * wappend_uint(wstr_builder *, unsigned long long);
wstr_builder * wappend_double(wstr_builder *, double);

wstr_builder * wconcat_builder(wstr_builder *, wstr_builder *);

int windex_of_char(wstr_builder *, wchar_t);
str_pos windex_of_str(wstr_builder *, const wchar_t *);

wstr_builder * wdelete_str(wstr_builder *, wchar_t *);
wstr_builder * wdelete_sec(wstr_builder *, str_pos);
wstr_builder * wdelete_char(wstr_builder *, wchar_t);

wchar_t * cwstr(wstr_builder *);
int wbsize(wstr_builder *);

void free_wstr_builder(void *);


#endif //TERMINALTEST_STRINGBUILDER_H
