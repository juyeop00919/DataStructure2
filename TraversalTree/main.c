#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Traversal.h"

int main() {
    // 10개 이상의 노드를 가지는 복잡한 이진트리 (총 13개 노드)
    // 구조 설명:
    //         A
    //       /   \
    //      B     C
    //     / \   / \
    //    D   E F   G
    //   / \ /   \ / \
    //  H  I J   K L  M
    // (일부 자식은 생략된 비대칭 구조 포함)
	char* treeString = (char*)malloc(100 * sizeof(char));
    printf("트리를 입력하세요 : ");
    scanf(" %[^\n]", treeString);

    printf("==========================================\n");
    printf("      반복적 이진트리 순회 프로그램\n");
    printf("==========================================\n\n");

    printf("[1] 입력된 이진트리의 구조 (괄호 표기법)\n");
    printf("입력 문자열: %s\n\n", treeString);

    // 트리 생성
    TreeNode* root = buildTree(treeString);
    if (root == NULL) {
        printf("트리 생성에 실패하여 프로그램을 종료합니다.\n");
        return 1;
    }

    // 결과 출력
    printf("[2] 전위 순회 결과 (Preorder)\n");
    printf("결과: ");
    preorder(root);
    printf("\n\n");

    printf("[3] 중위 순회 결과 (Inorder)\n");
    printf("결과: ");
    inorder(root);
    printf("\n\n");

    printf("[4] 후위 순회 결과 (Postorder)\n");
    printf("결과: ");
    postorder(root);
    printf("\n\n");

    printf("==========================================\n");

    // 동적 할당 메모리 해제
    freeTree(root);
    free(treeString);

    return 0;
}