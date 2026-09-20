#define _CRT_SECURE_NO_WARNINGS
#include "MenuTree.h"

// 특정 경로의 노드 찾기
TreeNode* find_node(BTree* tree, const char* path) {
    if (!tree || !tree->root || !path || path[0] != '/') return NULL;

    char path_copy[256];
    strcpy(path_copy, path); //복사

    char* token = strtok(path_copy, "/"); 
    if (!token || tree->root->data != token[0]) return NULL;  //루트의 이름을 확인하고 없으면 종료

    TreeNode* curr = tree->root;
    token = strtok(NULL, "/");

    while (token != NULL) {
        char target = token[0];
        if (curr->left && curr->left->data == target) { 
            curr = curr->left;
        }
        else if (curr->right && curr->right->data == target) {
            curr = curr->right;
        }
        else {
            return NULL; 
        }
        token = strtok(NULL, "/");
    }
    return curr;
}

//오류탐지

int validate_insert_root(BTree* tree) {
    if (tree->root != NULL) {
        printf("Error: 트리가 비어있지 않아 루트를 생성할 수 없습니다.\n");
        return 0;
    }
    return 1;
}

int validate_insert_child(BTree* tree, const char* parent_path, char child_dir, char value) {
    TreeNode* parent = find_node(tree, parent_path);
    if (!parent) {
        printf("Error: 부모 노드가 존재하지 않습니다.\n");
        return 0;
    }
    if (child_dir != 'L' && child_dir != 'R') {
        printf("Error: 자식 위치는 L 또는 R이어야 합니다.\n");
        return 0;
    }

    //부모가 완전히 비어있는지가 아니라, 지정한 위치가 비어있는지 검사
    if (child_dir == 'L' && parent->left != NULL) {
        printf("Error: 왼쪽 자식 위치에 이미 노드가 존재하여 끼워넣을 수 없습니다.\n");
        return 0;
    }
    if (child_dir == 'R' && parent->right != NULL) {
        printf("Error: 오른쪽 자식 위치에 이미 노드가 존재하여 끼워넣을 수 없습니다.\n");
        return 0;
    }

    //같은 데이터일 경우 에러
    if (child_dir == 'L' && parent->right != NULL && parent->right->data == value) {
        printf("Error: Insert 오류 - 오른쪽 자식과 동일한 데이터를 가질 수 없습니다.\n");
        return 0;
    }
    if (child_dir == 'R' && parent->left != NULL && parent->left->data == value) {
        printf("Error: Insert 오류 - 왼쪽 자식과 동일한 데이터를 가질 수 없습니다.\n");
        return 0;
    }

    return 1;
}

int validate_delete(BTree* tree, const char* leaf_path) {
    TreeNode* node = find_node(tree, leaf_path);
    if (!node) {
        printf("Error: 삭제할 노드가 존재하지 않습니다.\n");
        return 0;
    }
    if (node->left != NULL || node->right != NULL) {
        printf("Error: 삭제 대상이 단말 노드가 아닙니다.\n");
        return 0;
    }
    return 1;
}

int validate_update(BTree* tree, const char* path, char value) {
    if (!tree || !tree->root) {
        printf("Error: 트리가 비어 있습니다.\n");
        return 0;
    }

    char path_copy[256];
    strcpy(path_copy, path);
    char* token = strtok(path_copy, "/");
    if (!token || tree->root->data != token[0]) {
        printf("Error: 대상 노드가 존재하지 않습니다.\n");
        return 0;
    }

    TreeNode* parent = NULL;
    TreeNode* curr = tree->root;
    token = strtok(NULL, "/");

    while (token != NULL) {
        parent = curr;
        char target = token[0];
        if (curr->left && curr->left->data == target) curr = curr->left;
        else if (curr->right && curr->right->data == target) curr = curr->right;
        else {
            printf("Error: 대상 노드가 존재하지 않습니다.\n");
            return 0;
        }
        token = strtok(NULL, "/");
    }

    // 형제 노드와의 중복 검사
    if (parent != NULL) {
        if (parent->left == curr && parent->right != NULL && parent->right->data == value) {
            printf("Error: 변경하려는 데이터가 오른쪽 자식의 데이터와 중복됩니다.\n");
            return 0;
        }
        if (parent->right == curr && parent->left != NULL && parent->left->data == value) {
            printf("Error: 변경하려는 데이터가 왼쪽 자식의 데이터와 중복됩니다.\n");
            return 0;
        }
    }
    return 1;
}

int validate_read(BTree* tree, const char* path) {
    if (!find_node(tree, path)) {
        printf("Error: 확인할 노드가 존재하지 않습니다.\n");
        return 0;
    }
    return 1;
}

//ADT

BTree* create_btree(int size) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = NULL;
    tree->max_size = size;
    tree->current_size = 0;
    return tree;
}

BTree* insert_root(BTree* tree, char value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    tree->root = node;
    tree->current_size++;
    return tree;
}

BTree* insert_child(BTree* tree, const char* parent_path, char child_dir, char value) {
    TreeNode* parent = find_node(tree, parent_path); 
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if (child_dir == 'L') parent->left = new_node;
    else parent->right = new_node;

    tree->current_size++;
    return tree;
}

BTree* delete_node(BTree* tree, const char* leaf_path) {
    char path_copy[256];
    strcpy(path_copy, leaf_path);
    char* token = strtok(path_copy, "/");

    TreeNode* parent = NULL;
    TreeNode* curr = tree->root;
    token = strtok(NULL, "/");

    while (token != NULL) {
        parent = curr;
        char target = token[0];
        if (curr->left && curr->left->data == target) curr = curr->left;
        else curr = curr->right;
        token = strtok(NULL, "/");
    }

    if (parent == NULL) { 
        free(tree->root);
        tree->root = NULL;
    }
    else {
        if (parent->left == curr) parent->left = NULL;
        else parent->right = NULL;
        free(curr);
    }
    tree->current_size--;
    return tree;
}

BTree* update_value(BTree* tree, const char* path, char value) {
    TreeNode* node = find_node(tree, path);
    if (node) node->data = value;
    return tree;
}

void read_child(BTree* tree, const char* path) {
    TreeNode* node = find_node(tree, path);
    if (!node->left && !node->right) {
        printf("단말 노드입니다. (자식 없음)\n");
    }
    else if (node->left && node->right) {
        printf("%c(L), %c(R)\n", node->left->data, node->right->data);
    }
    else if (node->left) {
        printf("%c(L)\n", node->left->data);
    }
    else {
        printf("%c(R)\n", node->right->data);
    }
}

// 트리 공백 출력
void print_helper(TreeNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth - 1; i++) {
        printf("    "); 
    }
    if (depth > 0) printf("+---");
    printf("%c\n", node->data);

    print_helper(node->left, depth + 1);
    print_helper(node->right, depth + 1);
}

void print_btree(BTree* tree) {
    if (!tree || !tree->root) {
        printf("트리가 비어 있습니다.\n");
        return;
    }
    print_helper(tree->root, 0);
}

// 메모리 해제
void destroy_node(TreeNode* node) {
    if (!node) return;
    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
}

void destroy_btree(BTree* tree) {
    if (tree) {
        destroy_node(tree->root);
        free(tree);
    }
}