#ifndef _UDT_H_
#define _UDT_H_

#include <stdbool.h>
#include <stddef.h>

typedef int key_type;
typedef double value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

#define MAX_SIZE 100

typedef struct {
    data_type data[MAX_SIZE];
    int front;
    int rear;
    size_t size;
} udt;

void udt_create(udt *u);
bool udt_is_empty(const udt *u);
void udt_push_front(udt *u, data_type d);
void udt_push_back(udt *u, data_type d);
data_type udt_pop_front(udt *u);
data_type udt_pop_back(udt *u);
void udt_print(const udt *u);
size_t udt_size(const udt *u);
void udt_insert(udt *u, data_type d);
void udt_erase(udt *u, key_type k);

#endif