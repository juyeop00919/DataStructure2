#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 이진트리
typedef struct BTree {
    TreeNode* root;
    int max_size;
    int current_size;
} BTree;

// ADT
extern BTree* create_btree(int size);
extern BTree* insert_root(BTree* tree, char value);
extern BTree* insert_child(BTree* tree, const char* parent, char child, char value);
extern BTree* delete_node(BTree* tree, const char* leaf);
extern BTree* update_value(BTree* tree, const char* node, char value);
extern void read_child(BTree* tree, const char* parent);
extern void print_btree(BTree* tree);
extern void destroy_btree(BTree* tree);

// 오류 탐지 및 기타함수
extern TreeNode* find_node(BTree* tree, const char* path);
extern int validate_insert_root(BTree* tree);
extern int validate_insert_child(BTree* tree, const char* parent_path, char child_dir, char value);
extern int validate_delete(BTree* tree, const char* leaf_path);
extern int validate_update(BTree* tree, const char* path, char value);
extern int validate_read(BTree* tree, const char* path);
