#pragma once
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    int height; 
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// BST
TreeNode* insertBST(TreeNode* node, int key, int* compCount, bool* inserted);
bool searchBST(TreeNode* root, int key, int* compCount);

// AVL 
TreeNode* insertAVL(TreeNode* node, int key, int* compCount, bool* inserted);
bool searchAVL(TreeNode* root, int key, int* compCount);

// 공통 
int getTreeHeight(TreeNode* node);
void freeTree(TreeNode* root);