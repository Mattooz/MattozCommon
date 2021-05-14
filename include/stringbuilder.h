//
// Created by nickf on 27/04/2021.
//

#ifndef TERMINALTEST_STRINGBUILDER_H
#define TERMINALTEST_STRINGBUILDER_H
#include <stdio.h>
#include <wchar.h>

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

extern str_builder * sbof_size(int);
extern str_builder * sb_empty();
extern str_builder * sbof_str(char *);

extern str_builder * append_str(str_builder *, char *);
extern str_builder * append_char(str_builder *, char);
extern str_builder * append_int(str_builder *, long long);
extern str_builder * append_uint(str_builder *, unsigned long long);
extern str_builder * append_double(str_builder *, double);

extern str_builder * concat_builder(str_builder *, str_builder *);

extern int index_of_char(str_builder *, char);
extern str_pos index_of_str(str_builder *, const char *);

extern str_builder * delete_str(str_builder *, char *);
extern str_builder * delete_sec(str_builder *, str_pos);
extern str_builder * delete_char(str_builder *, char);

extern void sbeditatpos(str_builder *, str_pos, char *);
extern void sbeditatind(str_builder *, size_t, char *);

extern char * cstr(str_builder *);
extern int sbsize(str_builder *);

extern void free_str_builder(void *);

typedef struct {
    wchar_t * buffer;
    size_t capacity;
} wstr_builder;

extern wstr_builder * wbof_size(int);
extern wstr_builder * wb_empty();
extern wstr_builder * wbof_str(wchar_t *);

extern wstr_builder * wappend_str(wstr_builder *, char *);
extern wstr_builder * wappend_wstr(wstr_builder *, wchar_t *);
extern wstr_builder * wappend_char(wstr_builder *, char);
extern wstr_builder * wappend_wchar(wstr_builder *, wchar_t);
extern wstr_builder * wappend_int(wstr_builder *, long long);
extern wstr_builder * wappend_uint(wstr_builder *, unsigned long long);
extern wstr_builder * wappend_double(wstr_builder *, double);

extern wstr_builder * wconcat_builder(wstr_builder *, wstr_builder *);

extern int windex_of_char(wstr_builder *, wchar_t);
extern str_pos windex_of_str(wstr_builder *, const wchar_t *);

extern wstr_builder * wdelete_str(wstr_builder *, wchar_t *);
extern wstr_builder * wdelete_sec(wstr_builder *, str_pos);
extern wstr_builder * wdelete_char(wstr_builder *, wchar_t);

extern void wbeditatpos(wstr_builder *, str_pos, wchar_t *);
extern void wbeditatind(wstr_builder *, size_t, wchar_t *);

extern wchar_t * cwstr(wstr_builder *);
extern int wbsize(wstr_builder *);

extern void free_wstr_builder(void *);


#endif //TERMINALTEST_STRINGBUILDER_H
