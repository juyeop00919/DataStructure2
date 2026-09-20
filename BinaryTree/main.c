#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"
#include <windows.h> 


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
    TreeNode* linkedTreeRoot = buildLinkedTree(input);
    //int temp[MAX_NODES] = { 0 };
    printf("\n[ Linked Tree ]\n");
    printLinkedTree(linkedTreeRoot, 0, temp);
    analyzeLinkedTree(linkedTreeRoot);


    //Sleep(30000);
    //메모리
    //compareMemoryUsage(&arrTree, linkedTreeRoot);

    printf("\n\n=============== [ Find Node ] ===============\n");
    char target;
    printf("탐색할 노드의 알파벳을 입력하세요 (예: C): ");
    scanf(" %c", &target);

    printRelationsArray(&arrTree, target); //배열에서 찾기
    printRelationsLinked(linkedTreeRoot, target); //포인터에서 찾기



    return 0;
}
//dd