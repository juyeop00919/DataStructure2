#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

int main() {
    char input[MAX_TREE_SIZE];
    printf("Input Tree ( ex: A(B(E,F),C,D(G)) ) : ");
    scanf("%s", input);

    if (!isValidTreeFormat(input)) {
        printf("\nInvalid Tree\n");
        return 1;
    }

    //배열
     
    printf("\n\n=============== [ Array Tree ] ===============\n");
    ArrayTree arrTree;
    initArrayTree(&arrTree);
    buildArrayTree(&arrTree, input);

    int temp[MAX_NODES] = { 0 };
    printf("\n[ Array Tree ]\n");
    printArrayTree(&arrTree, 1, 0, temp);
    analyzeArrayTree(&arrTree);
    
        //포인터
        printf("\n\n=============== [ Linked Tree ] ===============\n");
        int temp[MAX_NODES] = { 0 };
        TreeNode* linkedTreeRoot = buildLinkedTree(input);

        printf("\n[ Linked Tree ]\n");
        printLinkedTree(linkedTreeRoot, 0, temp);
        analyzeLinkedTree(linkedTreeRoot);

        printf("\n=========================================================\n");

        
    
    return 0;
}