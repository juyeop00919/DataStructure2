#pragma once
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* insertNode(TreeNode* root, int key, int* compCount);
bool bstSearch(TreeNode* root, int key, int* compCount);
void freeTree(TreeNode* root);


void printInorder(TreeNode* root);

void printTree(TreeNode* root, int space);