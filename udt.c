#include <stdio.h>
#include "udt.h"

void udt_create(udt *u) {
    u->front = 0;
    u->rear = -1;
    u->size = 0;
}

bool udt_is_empty(const udt *u) {
    return u->size == 0;
}

size_t udt_size(const udt *u) {
    return u->size;
}

void udt_push_back(udt *u, data_type d) {
    if (u->size >= MAX_SIZE) {
        printf("Ошибка: дек переполнен\n");
        return;
    }
    u->rear = (u->rear + 1) % MAX_SIZE;
    u->data[u->rear] = d;
    if (u->size == 0) {
        u->front = u->rear;
    }
    u->size++;
}

void udt_push_front(udt *u, data_type d) {
    if (u->size >= MAX_SIZE) {
        printf("Ошибка: дек переполнен\n");
        return;
    }
    u->front = (u->front - 1 + MAX_SIZE) % MAX_SIZE;
    u->data[u->front] = d;
    if (u->size == 0) {
        u->rear = u->front;
    }
    u->size++;
}

data_type udt_pop_front(udt *u) {
    if (u->size == 0) {
        data_type empty = {0, 0.0};
        return empty;
    }
    data_type d = u->data[u->front];
    u->front = (u->front + 1) % MAX_SIZE;
    u->size--;
    return d;
}

data_type udt_pop_back(udt *u) {
    if (u->size == 0) {
        data_type empty = {0, 0.0};
        return empty;
    }
    data_type d = u->data[u->rear];
    u->rear = (u->rear - 1 + MAX_SIZE) % MAX_SIZE;
    u->size--;
    return d;
}

void udt_insert(udt *u, data_type d) {
    udt_push_back(u, d);
}

void udt_erase(udt *u, key_type k) {
    size_t s = u->size;
    for (size_t i = 0; i < s; i++) {
        data_type d = udt_pop_front(u);
        if (d.key != k) {
            udt_push_back(u, d);
        }
    }
}

void udt_print(const udt *u) {
    if (u->size == 0) {
        printf("Дек пуст\n");
        return;
    }
    int idx = u->front;
    for (size_t i = 0; i < u->size; i++) {
        printf("[%d: %.2f] ", u->data[idx].key, u->data[idx].value);
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}