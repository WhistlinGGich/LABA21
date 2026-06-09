#include <stdio.h>
#include <stdbool.h>
#include "udt.h"

data_type find_and_remove_max(udt *u, size_t current_size) {
    data_type max_item;
    bool first = true;

    for (size_t i = 0; i < current_size; i++) {
        data_type item = udt_pop_front(u);
        if (first || item.key > max_item.key) {
            max_item = item;
            first = false;
        }
        udt_push_back(u, item);
    }

    bool removed = false;
    for (size_t i = 0; i < current_size; i++) {
        data_type item = udt_pop_front(u);
        if (!removed && item.key == max_item.key) {
            removed = true;
        } else {
            udt_push_back(u, item);
        }
    }
    return max_item;
}

void sort_deque_recursive(udt *u, size_t current_size) {
    if (current_size <= 1) return;
    data_type max_item = find_and_remove_max(u, current_size);
    sort_deque_recursive(u, current_size - 1);
    udt_push_back(u, max_item);
}

int main() {
    udt my_deque;
    udt_create(&my_deque);
    int choice;

    while (1) {
        printf("\n--- МЕНЮ ---\n");
        printf("1.Добавить в начало\n");
        printf("2.Добавить в конец\n");
        printf("3.Удалить с начала (pop_front)\n");
        printf("4.Удалить с конца (pop_back)\n");
        printf("5.Вывести дек\n");
        printf("6.Сортировка линейным выбором (Рекурсия)\n");
        printf("7.Выйти\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) break;

        if (choice == 7) break;

        data_type d;
        switch (choice) {
            case 1:
                printf("Введите ключ и значение: ");
                scanf("%d %lf", &d.key, &d.value);
                udt_push_front(&my_deque, d);
                break;
            case 2:
                printf("Введите ключ и значение: ");
                scanf("%d %lf", &d.key, &d.value);
                udt_push_back(&my_deque, d);
                break;
            case 3:
                if (!udt_is_empty(&my_deque)) {
                    d = udt_pop_front(&my_deque);
                    printf("Удален элемент: [%d: %.2f]\n", d.key, d.value);
                } else {
                    printf("Дек пуст\n");
                }
                break;
            case 4:
                if (!udt_is_empty(&my_deque)) {
                    d = udt_pop_back(&my_deque);
                    printf("Удален элемент: [%d: %.2f]\n", d.key, d.value);
                } else {
                    printf("Дек пуст\n");
                }
                break;
            case 5:
                udt_print(&my_deque);
                break;
            case 6:
                sort_deque_recursive(&my_deque, udt_size(&my_deque));
                printf("Дек отсортирован по возрастанию ключей\n");
                udt_print(&my_deque);
                break;
            default:
                printf("Неверный пункт меню\n");
        }
    }
    return 0;
}