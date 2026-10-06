#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

// BST 함수
TreeNode* insertBST(TreeNode* node, int key, int* compCount, bool* inserted) {
    if (node == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = key;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        *inserted = true;
        return newNode;
    }

    (*compCount)++; 
    if (key < node->data) {
        node->left = insertBST(node->left, key, compCount, inserted);
    }
    else if (key > node->data) {
        node->right = insertBST(node->right, key, compCount, inserted);
    }
    else {
        *inserted = false; 
    }
    return node;
}

bool searchBST(TreeNode* root, int key, int* compCount) {
    *compCount = 0;
    TreeNode* current = root;

    while (current != NULL) {
        (*compCount)++;
        if (key == current->data) {
            return true;
        }
        else if (key < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}


// AVL 트리 함수
int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getAVLHeightValue(TreeNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return getAVLHeightValue(node->left) - getAVLHeightValue(node->right);
}


TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;


    y->height = getMax(getAVLHeightValue(y->left), getAVLHeightValue(y->right)) + 1;
    x->height = getMax(getAVLHeightValue(x->left), getAVLHeightValue(x->right)) + 1;

    return x;
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = getMax(getAVLHeightValue(x->left), getAVLHeightValue(x->right)) + 1;
    y->height = getMax(getAVLHeightValue(y->left), getAVLHeightValue(y->right)) + 1;

    return y;
}


TreeNode* insertAVL(TreeNode* node, int key, int* compCount) {
    if (node == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = key;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    (*compCount)++;
    if (key < node->data) {
        node->left = insertAVL(node->left, key, compCount);
    }
    else if (key > node->data) {
        node->right = insertAVL(node->right, key, compCount);
    }
    else {
        return node; 
    }

    node->height = 1 + getMax(getAVLHeightValue(node->left), getAVLHeightValue(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool searchAVL(TreeNode* root, int key, int* compCount) {
    return searchBST(root, key, compCount);
}

// 공통 유틸리티
int getTreeHeight(TreeNode* node) {
    if (node == NULL) return 0;
    int leftH = getTreeHeight(node->left);
    int rightH = getTreeHeight(node->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}