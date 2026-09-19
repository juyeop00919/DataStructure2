#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_SIZE 256
#define MAX_NODES 100

//배열
typedef struct {
	char data[MAX_TREE_SIZE];
	int max_index;
}ArrayTree;

//포인터
typedef struct TreeNode{
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

extern int isValidTreeFormat(char* str);

//배열
extern void createArrayTree(ArrayTree* tree);
extern void buildArrayTree(ArrayTree* tree,char* str);
extern void printArrayTree(ArrayTree* tree, int index, int depth, int* sib);
extern void analyzeArrayTree(ArrayTree* tree);
extern void printRelationsArray(ArrayTree* tree, char target);

//포인터
extern TreeNode* createNode(char data);
extern TreeNode* buildLinkedTree(char* str);
extern void printLinkedTree(TreeNode* node, int depth, int* sib);
extern void analyzeLinkedTree(TreeNode* root);
extern void printRelationsLinked(TreeNode* root, char target);