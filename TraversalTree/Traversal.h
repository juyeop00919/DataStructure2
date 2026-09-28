#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* buildTree(const char* str); 
void preorder(TreeNode* tree);         // 전위 순회
void inorder(TreeNode* tree);          // 중위 순회
void postorder(TreeNode* tree);        // 후위 순회
void freeTree(TreeNode* tree);      
