#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum { NUM, VAR, OP } NodeType;

typedef struct Node {
    NodeType type;
    int val;
    char op;
    struct Node *left;
    struct Node *right;
} Node;

const char* str;

Node* make_num(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = NUM;
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

Node* make_var(char var) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = VAR;
    n->op = var;
    n->left = n->right = NULL;
    return n;
}

Node* make_op(char op, Node* l, Node* r) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = OP;
    n->op = op;
    n->left = l;
    n->right = r;
    return n;
}

Node* parse_expr();

Node* parse_factor() {
    while (*str == ' ') str++;
    if (*str == '(') {
        str++;
        Node* n = parse_expr();
        while (*str == ' ') str++;
        if (*str == ')') str++;
        return n;
    }
    if (isdigit(*str)) {
        int val = 0;
        while (isdigit(*str)) {
            val = val * 10 + (*str - '0');
            str++;
        }
        return make_num(val);
    }
    if (isalpha(*str)) {
        char v = *str;
        str++;
        return make_var(v);
    }
    return NULL;
}

Node* parse_power() {
    Node* left = parse_factor();
    while (*str == ' ') str++;
    if (*str == '^') {
        str++;
        Node* right = parse_power();
        left = make_op('^', left, right);
    }
    return left;
}

Node* parse_term() {
    Node* left = parse_power();
    while (*str == ' ') str++;
    while (*str == '*' || *str == '/') {
        char op = *str;
        str++;
        Node* right = parse_power();
        left = make_op(op, left, right);
        while (*str == ' ') str++;
    }
    return left;
}

Node* parse_expr() {
    Node* left = parse_term();
    while (*str == ' ') str++;
    while (*str == '+' || *str == '-') {
        char op = *str;
        str++;
        Node* right = parse_term();
        left = make_op(op, left, right);
        while (*str == ' ') str++;
    }
    return left;
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void simplify(Node* root) {
    if (!root) return;
    simplify(root->left);
    simplify(root->right);
    if (root->type == OP && root->op == '^') {
        if (root->left && root->left->type == NUM && root->right && root->right->type == NUM) {
            int res = (int)pow(root->left->val, root->right->val);
            free_tree(root->left);
            free_tree(root->right);
            root->type = NUM;
            root->val = res;
            root->left = root->right = NULL;
        }
    }
}

void print_tree(Node* root, int level) {
    if (!root) return;
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    if (root->type == NUM) printf("%d\n", root->val);
    else if (root->type == VAR) printf("%c\n", root->op);
    else printf("%c\n", root->op);
    print_tree(root->left, level + 1);
}

void print_expr(Node* root) {
    if (!root) return;
    if (root->type == OP) printf("(");
    print_expr(root->left);
    if (root->type == NUM) printf("%d", root->val);
    else if (root->type == VAR) printf("%c", root->op);
    else printf(" %c ", root->op);
    print_expr(root->right);
    if (root->type == OP) printf(")");
}

int main() {
    char buffer[256];
    printf("Введите выражение: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    str = buffer;
    
    Node* root = parse_expr();
    
    printf("\nИсходное дерево:\n");
    print_tree(root, 0);
    printf("\nИсходное выражение: ");
    print_expr(root);
    printf("\n");
    
    simplify(root);
    
    printf("\nУпрощенное дерево:\n");
    print_tree(root, 0);
    printf("\nУпрощенное выражение: ");
    print_expr(root);
    printf("\n");
    
    free_tree(root);
    return 0;
}