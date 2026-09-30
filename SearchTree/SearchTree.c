#include <stdio.h>
#include <stdlib.h>
#include "SearchTree.h"

TreeNode* insertNode(TreeNode* root, int key, int* compCount) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;

   
    if (root == NULL) {
        return newNode;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;


    while (current != NULL) {
        parent = current;
        (*compCount)++; 

        if (key < current->data) {
            current = current->left;
        }
        else if (key > current->data) {
            current = current->right;
        }
        else {
            free(newNode);
            return root;
        }
    }

    
    if (key < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return root;
}

bool bstSearch(TreeNode* root, int key, int* compCount) {
    *compCount = 0; 
    TreeNode* current = root;

    while (current != NULL) {
        (*compCount)++; 

        if (key == current->data) {
            return true; // 탐색 성공
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

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}



void printInorder(TreeNode* root) {
    if (root != NULL) {
        printInorder(root->left);   
        printf("%d ", root->data);  
        printInorder(root->right);  
    }
}

void printTree(TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    printTree(root->left, space);
}