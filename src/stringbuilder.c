//
// Created by nickf on 27/04/2021.
//

#include "../include/stringbuilder.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ####################### *
 * String builder definition
 * ####################### */


#define sbcheck_realloc(ch_num) if(sbsize(builder) + ch_num >= builder->capacity) { \
                                    builder->buffer = realloc(builder->buffer, sbsize(builder) + ch_num + 1); \
                                    builder->capacity = sbsize(builder) + ch_num + 1; \
                                }
#define wsbcheck_realloc(ch_num) if(wbsize(builder) + ch_num >= builder->capacity) { \
                                    builder->buffer = realloc(builder->buffer, (wbsize(builder) + ch_num + 1) * sizeof(wchar_t)); \
                                    builder->capacity = wbsize(builder) + ch_num + 1; \
                                 } \


str_builder *sbof_size(int init_capacity) {
    str_builder *builder = (str_builder *) malloc(sizeof(str_builder));
    builder->buffer = calloc(init_capacity, sizeof(char));
    builder->capacity = init_capacity;
    return builder;
}

str_builder *sb_empty() {
    return sbof_size(DEFAULT_INI_CAPACITY);
}

str_builder *sbof_str(char *originalstr) {
    str_builder *builder = (str_builder *) malloc(sizeof(str_builder));

    size_t slen = strlen(originalstr);
    builder->buffer = calloc(slen + 1, sizeof(char));
    strcpy(builder->buffer, originalstr);
    builder->capacity = slen + 1;

    return builder;
}

str_builder *append_str(str_builder *builder, char *str) {
    size_t slen = strlen(str);
    sbcheck_realloc(slen);
    strcat(builder->buffer, str);
    return builder;
}

str_builder *append_char(str_builder *builder, char c) {
    size_t sblen = sbsize(builder);
    sbcheck_realloc(1);
    builder->buffer[sblen] = c;
    return builder;
}

str_builder *append_int(str_builder *builder, long long number) {
    int is_neg = number < 0;
    size_t chars_in_int = (size_t) ceil(log10((double) ((is_neg) ? -number : number))) + 2 + (is_neg ? 1 : 0);
    char str[chars_in_int];
    sprintf(str, "%lli", number);
    append_str(builder, str);
    return builder;
}

str_builder *append_uint(str_builder *builder, unsigned long long number) {
    size_t chars_in_int = (size_t) ceil(log10((double) number)) + 2;
    char str[chars_in_int];
    sprintf(str, "%llu", number);
    append_str(builder, str);
    return builder;
}


str_builder *append_double(str_builder *builder, double number) {
    char str[500]; //arbitrary size, will make it dynamic later on.
    sprintf(str, "%f", number);
    append_str(builder, str);
    return builder;
}

str_builder *concat_builder(str_builder *builder, str_builder *src) {
    sbcheck_realloc(sbsize(src));
    strcat(builder->buffer, src->buffer);
    return builder;
}

int index_of_char(str_builder *builder, char ch) {
    int index = 0;
    char c;
    while ((c = builder->buffer[index++]) != '\0') if (c == ch) return index;
    return -1;
}

str_pos index_of_str(str_builder *builder, const char *str) {
    str_pos pos;
    int index = 0, index_str = 0, found = 0;
    char c;

    while ((c = builder->buffer[index]) != '\0') {
        if (str[index_str] == '\0') {
            pos.end = index;
            return pos;
        }

        if (c == *str && !found) {
            found = 1;
            pos.start = index;
        }

        if (found && c != str[index_str++]) {
            found = 0;
            index_str = 0;
        }
        index++;
    }

    if (found && !str[index_str]) {
        pos.end = index;
        return pos;
    }

    return EMPTY_POS;
}

str_builder *delete_char(str_builder *builder, char ch) {
    char *buf = builder->buffer;
    while (*buf != '\0' && *buf != ch) buf++;
    while (*(buf + 1) != '\0') {
        *buf = *(buf + 1);
        buf++;
    }
    return builder;
}

str_builder *delete_sec(str_builder *builder, str_pos pos) {
    if (pos.start < 0 || pos.start >= sbsize(builder) ||
        pos.end < 0 || pos.end > sbsize(builder))
        return builder;

    int i = pos.start, l = pos.end - pos.start, size = sbsize(builder);

    while (i < size) {
        if (builder->buffer[i + l] && builder->buffer[i + l] != '\0') {
            builder->buffer[i] = builder->buffer[i + l];
            builder->buffer[i + l] = '\0';
        } else builder->buffer[i] = '\0';
        i++;
    }

    return builder;
}

str_builder *delete_str(str_builder *builder, char *str) {
    str_pos pos = index_of_str(builder, str);
    if (pos.start == -1 || pos.end == -1) return builder;

    delete_sec(builder, pos);

    return builder;
}

int sbsize(str_builder *builder) {
    return strlen(builder->buffer);
}

char *cstr(str_builder *builder) {
    char *str = calloc(sbsize(builder), sizeof(char));
    strcpy(str, builder->buffer);
    return str;
}

void free_str_builder(void *builder) {
    str_builder *ptr = (str_builder *) builder;
    if (ptr) {
        free(ptr->buffer);
        free(ptr);
    }
}

/* ####################### *
 * WideString builder definition
 * ####################### */

wstr_builder *wbof_size(int init_capacity) {
    wstr_builder *builder = (wstr_builder *) malloc(sizeof(wstr_builder));
    builder->buffer = calloc(init_capacity, sizeof(wchar_t));
    builder->capacity = init_capacity;
    return builder;
}

wstr_builder *wb_empty() {
    return wbof_size(DEFAULT_INI_CAPACITY);
}

wstr_builder *wbof_str(wchar_t *originalstr) {
    wstr_builder *builder = (wstr_builder *) malloc(sizeof(wstr_builder));

    size_t slen = wcslen(originalstr);
    builder->buffer = calloc(slen + 1, sizeof(wchar_t));
    wcscpy(builder->buffer, originalstr);
    builder->capacity = slen + 1;

    return builder;
}

wstr_builder *wappend_str(wstr_builder *builder, char *string) {
    size_t slen = strlen(string);
    wchar_t *wstr = calloc(slen, sizeof(wchar_t));
    mbstowcs(wstr, string, slen);
    wsbcheck_realloc(slen);

    wcscat(builder->buffer, wstr);
    free(wstr);
    return builder;
}

wstr_builder *wappend_wstr(wstr_builder *builder, wchar_t *wstring) {
    size_t slen = wcslen(wstring);
    wsbcheck_realloc(slen);
    wcscat(builder->buffer, wstring);
    return builder;
}

wstr_builder *wappend_char(wstr_builder *builder, char c) {
    wchar_t wchar = (wchar_t) c;
    int wslen = wbsize(builder);
    wsbcheck_realloc(1)
    builder->buffer[wslen] = wchar;
    return builder;
}

wstr_builder *wappend_wchar(wstr_builder *builder, wchar_t c) {
    int wslen = wbsize(builder);
    wsbcheck_realloc(1)
    builder->buffer[wslen] = c;
    return builder;
}

wstr_builder *wappend_int(wstr_builder *builder, long long number) {
    int wslen = wbsize(builder), is_neg = number < 0;
    size_t chars_in_int = (size_t) ceil(log10((double) ((is_neg) ? -number : number))) + 2 + (is_neg ? 1 : 0);
    wsbcheck_realloc(chars_in_int)
    swprintf(builder->buffer, wslen, L"%lli", number);
    return builder;
}

wstr_builder *wappend_uint(wstr_builder *builder, unsigned long long number) {
    int wslen = wbsize(builder), is_neg = number < 0;
    size_t chars_in_int = (size_t) ceil(log10((double) number)) + 2;
    wsbcheck_realloc(chars_in_int)
    swprintf(builder->buffer, wslen, L"%llu", number);
    return builder;
}

wstr_builder *wappend_double(wstr_builder *builder, double number) {
    wchar_t str[500]; // again, need to find a better way to count digits inside of double
    swprintf(str, 500, L"%f", number);
    wappend_wstr(builder, str);
    return builder;
}

wstr_builder * wconcat_builder(wstr_builder * builder, wstr_builder * src) {
    wsbcheck_realloc(wbsize(src));
    wcscat(builder->buffer, src->buffer);
    return builder;
}

int windex_of_char(wstr_builder * builder, wchar_t ch) {
    int index = 0;
    wchar_t c;
    while ((c = builder->buffer[index++]) != '\0') if (c == ch) return index;
    return -1;
}

str_pos windex_of_str(wstr_builder *builder, const wchar_t *str) {
    str_pos pos;
    int index = 0, index_str = 0, found = 0;
    wchar_t c;

    while ((c = builder->buffer[index]) != '\0') {
        if (str[index_str] == '\0') {
            pos.end = index;
            return pos;
        }

        if (c == *str && !found) {
            found = 1;
            pos.start = index;
        }

        if (found && c != str[index_str++]) {
            found = 0;
            index_str = 0;
        }
        index++;
    }

    if (found && !str[index_str]) {
        pos.end = index;
        return pos;
    }

    return EMPTY_POS;
}


wstr_builder *wdelete_char(wstr_builder *builder, wchar_t ch) {
    wchar_t *buf = builder->buffer;
    while (*buf != '\0' && *buf != ch) buf++;
    while (*(buf + 1) != '\0') {
        *buf = *(buf + 1);
        buf++;
    }
    return builder;
}

wstr_builder *wdelete_sec(wstr_builder *builder, str_pos pos) {
    if (pos.start < 0 || pos.start >= wbsize(builder) ||
        pos.end < 0 || pos.end > wbsize(builder))
        return builder;

    int i = pos.start, l = pos.end - pos.start, size = wbsize(builder);

    while (i < size) {
        if (builder->buffer[i + l] && builder->buffer[i + l] != '\0') {
            builder->buffer[i] = builder->buffer[i + l];
            builder->buffer[i + l] = '\0';
        } else builder->buffer[i] = '\0';
        i++;
    }

    return builder;
}

wstr_builder *wdelete_str(wstr_builder *builder, wchar_t *str) {
    str_pos pos = windex_of_str(builder, str);
    if (pos.start == -1 || pos.end == -1) return builder;

    wdelete_sec(builder, pos);

    return builder;
}

int wbsize(wstr_builder *builder) {
    return wcslen(builder->buffer);
}

wchar_t *cwstr(wstr_builder *builder) {
    wchar_t *str = calloc(wbsize(builder), sizeof(wchar_t));
    wcscpy(str, builder->buffer);
    return str;
}

void free_wstr_builder(void *builder) {
    wstr_builder *ptr = (wstr_builder *) builder;
    if (ptr) {
        free(ptr->buffer);
        free(ptr);
    }
}