#define _CRT_SECURE_NO_WARNINGS #Это чтобы визуал студио не жаловался
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float data;
    struct Node* son;
    struct Node* brother;
} Node;

float deepestValue = 0;
int maxFoundDepth = -1;

Node* createNode(float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = value;
        newNode->son = NULL;
        newNode->brother = NULL;
    }
    return newNode;
}

Node* findNode(Node* root, float value) {
    if (!root) return NULL;
    if (root->data == value) return root;
    Node* res = findNode(root->son, value);
    if (res) return res;
    return findNode(root->brother, value);
}

void addNode(Node* parent, float value) {
    if (!parent) return;
    Node* newNode = createNode(value);
    if (!parent->son) {
        parent->son = newNode;
    }
    else {
        Node* temp = parent->son;
        while (temp->brother) temp = temp->brother;
        temp->brother = newNode;
    }
}

void clearSubtree(Node* target) {
    if (!target) return;
    clearSubtree(target->son);
    clearSubtree(target->brother);
    free(target);
}

Node* deleteNode(Node* root, float value) {
    if (!root) return NULL;

    if (root->data == value) {
        Node* nextRoot = root->brother;
        clearSubtree(root->son);
        free(root);
        return nextRoot;
    }

    if (root->son && root->son->data == value) {
        Node* toDelete = root->son;
        root->son = toDelete->brother;
        clearSubtree(toDelete->son);
        free(toDelete);
        return root;
    }

    Node* curr = root->son;
    while (curr && curr->brother) {
        if (curr->brother->data == value) {
            Node* toDelete = curr->brother;
            curr->brother = toDelete->brother;
            clearSubtree(toDelete->son);
            free(toDelete);
            return root;
        }
        curr = curr->brother;
    }

    deleteNode(root->son, value);
    deleteNode(root->brother, value);
    return root;
}

void printTree(Node* root, int depth) {
    if (!root) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%.2f\n", root->data);
    printTree(root->son, depth + 1);
    printTree(root->brother, depth);
}

void solveVariant5(Node* root, int depth) {
    if (!root) return;
    if (root->son != NULL) {
        if (depth > maxFoundDepth) {
            maxFoundDepth = depth;
            deepestValue = root->data;
        }
    }
    solveVariant5(root->son, depth + 1);
    solveVariant5(root->brother, depth);
}

int main() {
    Node* root = NULL;
    int choice;
    float val, pVal;

    while (1) {
        printf("\n--- МЕНЮ(Вариант 5)---\n");
        printf("1.Добавить узел\n2.Показать дерево\n3.Расчет значения нетерминальной вершины дерева с максимальной глубиной(Задание варианта)\n4.Удалить узел\n5.Выход\n");
        printf("Выбор:");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printf("Значение:"); scanf("%f", &val);
            if (!root) root = createNode(val);
            else {
                printf("Отец:"); scanf("%f", &pVal);
                addNode(findNode(root, pVal), val);
            }
        }
        else if (choice == 2) {
            printTree(root, 0);
        }
        else if (choice == 3) {
            maxFoundDepth = -1;
            solveVariant5(root, 0);
            if (maxFoundDepth != -1) printf("Результат:%.2f (глубина %d)\n", deepestValue, maxFoundDepth);
            else printf("Нетерминальных узлов нет.\n");
        }
        else if (choice == 4) {
            printf("Что удалить:"); scanf("%f", &val);
            root = deleteNode(root, val);
            printf("Готово.\n");
        }
        else if (choice == 5) {
            clearSubtree(root);
            break;
        }
    }
    return 0;
}