#include "tree.h"

//유효성 검사
int isValidTreeFormat(char* str) {
    int open_brackets = 0;
    char prev = '\0';
    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];
        if (ch == ' ' || ch == '\n') continue;
        if (!(ch >= 'A' && ch <= 'Z') && ch != '(' && ch != ')' && ch != ',') return 0;

        if (ch == '(') {
            if (!(prev >= 'A' && prev <= 'Z')) return 0;
            open_brackets++;
        }
        else if (ch == ')') {
            if (open_brackets == 0) return 0;
            if (prev == '(') return 0;
            open_brackets--;
        }
        else if (ch == ',') {
            if (open_brackets == 0) return 0;
            if (prev == ',') return 0;
        }
        prev = ch;
    }
    return open_brackets == 0;
}

//트리 깊이 계산
int calculateDepth(int index) {
    int depth = 0;
    while (index > 0) {
        depth++;
        index /= 2;
    }
    return depth;
}

// 배열
void initArrayTree(ArrayTree* tree) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree->data[i] = '\0';
    }
    tree->max_index = 0;
}

void buildArrayTree(ArrayTree* tree, char* str) {
    int idxStack[MAX_NODES];
    int stateStack[MAX_NODES];
    int top = -1;
    int last_idx = 1;

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];

        if (ch >= 'A' && ch <= 'Z') {
            int curr_idx;
            if (top == -1) {
                curr_idx = 1; // 루트 노드
            }
            else {
                int parent_idx = idxStack[top];
                int state = stateStack[top];
                curr_idx = (state == 0) ? (parent_idx * 2) : (parent_idx * 2 + 1);
            }

            tree->data[curr_idx] = ch;
            last_idx = curr_idx;
            if (curr_idx > tree->max_index) tree->max_index = curr_idx;

        }
        else if (ch == '(') {
            top++;
            idxStack[top] = last_idx;
            stateStack[top] = 0;
        }
        else if (ch == ',') {
            stateStack[top] = 1;
        }
        else if (ch == ')') {
            top--;
        }
    }
}
//배열 출력
void printArrayTree(ArrayTree* tree, int index, int depth, int* sib) {
    if (index > MAX_TREE_SIZE || tree->data[index] == '\0') return;

    // 현재 노드 출력
    if (depth == 0) {
        printf("%c\n", tree->data[index]); 
    }
    else {
        // 깊이에 따라 수직선(|) 또는 공백 출력
        for (int i = 0; i < depth - 1; i++) {
            if (sib[i]) printf("|   ");
            else printf("    ");
        }
        printf("+---%c\n", tree->data[index]);
    }

    int left_idx = index * 2;
    int right_idx = index * 2 + 1;
    int has_left = (left_idx <= MAX_TREE_SIZE && tree->data[left_idx] != '\0');
    int has_right = (right_idx <= MAX_TREE_SIZE && tree->data[right_idx] != '\0');

    // 왼쪽 자식이 있으면 먼저 탐색
    if (has_left) {
        sib[depth] = has_right ? 1 : 0;
        printArrayTree(tree, left_idx, depth + 1, sib);
    }
    // 오른쪽 자식이 있으면 탐색
    if (has_right) {
        sib[depth] = 0;
        printArrayTree(tree, right_idx, depth + 1, sib);
    }
}
//분석
void analyzeArrayTree(ArrayTree* tree) {
    int total_nodes = 0, leaf_nodes = 0, non_leaf = 0;
    int max_depth = 0;
    int max_degree = 0;

    for (int i = 1; i <= tree->max_index; i++) {
        if (tree->data[i] != '\0') {
            total_nodes++;
            int left_idx = i * 2;
            int right_idx = i * 2 + 1;
            int has_left = (left_idx <= MAX_TREE_SIZE && tree->data[left_idx] != '\0');
            int has_right = (right_idx <= MAX_TREE_SIZE && tree->data[right_idx] != '\0');

            int degree = has_left + has_right;
            if (degree > max_degree) max_degree = degree;

            if (degree == 0) leaf_nodes++;
            else non_leaf++;

            int depth = calculateDepth(i);
            if (depth > max_depth) max_depth = depth;
        }
    }

    printf("\n[ Array Tree info ]\n");
    printf("- Total Nodes : %d\n", total_nodes);
    printf("- Leaf Nodes: %d\n", leaf_nodes);
    printf("- Non Leaf Nodes : %d\n", non_leaf);
    printf("- Depth : %d\n", max_depth);
    printf("- Degree: %d\n", max_degree);

    int isComplete = (tree->max_index == total_nodes);
    int isPerfect = (total_nodes == ((1 << max_depth) - 1));
    int isSkewed = (total_nodes == max_depth);

    printf("- 완전 이진트리 여부 (Complete) : %s\n", isComplete ? "Yes" : "No");
    printf("- 포화 이진트리 여부 (Perfect): %s\n", isPerfect ? "Yes" : "No");
    printf("- 편향 이진트리 여부 (Skewed): %s\n", isSkewed ? "Yes" : "No");
}

//배열찾기
void printRelationsArray(ArrayTree* tree, char target) {
    int target_idx = -1;
    for (int i = 1; i <= tree->max_index; i++) {
        if (tree->data[i] == target) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) {
        printf("배열 트리: 노드 '%c'를 찾을 수 없습니다.\n", target);
        return;
    }

    printf("\n[ 배열 트리 - 노드 '%c' 관계 ]\n", target);

    // 부모 노드 (i / 2)
    if (target_idx == 1) printf("- 부모 노드: 없음 (루트 노드)\n");
    else printf("- 부모 노드: %c\n", tree->data[target_idx / 2]);

    // 자식 노드 (왼쪽 i*2, 오른쪽 i*2+1)
    int left = target_idx * 2;
    int right = target_idx * 2 + 1;
    if (left <= MAX_TREE_SIZE && tree->data[left] != '\0') printf("- 왼쪽 자식: %c\n", tree->data[left]);
    else printf("- 왼쪽 자식: 없음\n");
    if (right <= MAX_TREE_SIZE && tree->data[right] != '\0') printf("- 오른쪽 자식: %c\n", tree->data[right]);
    else printf("- 오른쪽 자식: 없음\n");

    // 형제 노드 (짝수면 +1, 홀수면 -1)
    if (target_idx == 1) {
        printf("- 형제 노드: 없음\n");
    }
    else {
        int sib = (target_idx % 2 == 0) ? (target_idx + 1) : (target_idx - 1);
        if (sib <= MAX_TREE_SIZE && tree->data[sib] != '\0') printf("- 형제 노드: %c\n", tree->data[sib]);
        else printf("- 형제 노드: 없음\n");
    }
}
//포인터
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); 
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildLinkedTree(char* str) {
    TreeNode* nodeStack[MAX_NODES];
    int stateStack[MAX_NODES];
    int top = -1;

    TreeNode* root = NULL;
    TreeNode* last_node = NULL;

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];

        if (ch >= 'A' && ch <= 'Z') {
            TreeNode* newNode = createNode(ch);
            if (root == NULL) {
                root = newNode;
            }
            else {
                TreeNode* parent = nodeStack[top];
                int state = stateStack[top];

                if (state == 0) parent->left = newNode;
                else parent->right = newNode;
            }
            last_node = newNode;

        }
        else if (ch == '(') {
            top++;
            nodeStack[top] = last_node;
            stateStack[top] = 0;
        }
        else if (ch == ',') {
            stateStack[top] = 1;
        }
        else if (ch == ')') {
            top--;
        }
    }
    return root;
}

void printLinkedTree(TreeNode* node, int depth, int* sib) {
    if (node == NULL) return;

    if (depth == 0) {
        printf("%c\n", node->data);
    }
    else {
        for (int i = 0; i < depth - 1; i++) {
            if (sib[i]) printf("|   ");
            else printf("    ");
        }
        printf("+---%c\n", node->data);
    }
    if (node->left != NULL) {
        sib[depth] = (node->right != NULL) ? 1 : 0;
        printLinkedTree(node->left, depth + 1, sib);
    }
    if (node->right != NULL) {
        sib[depth] = 0;
        printLinkedTree(node->right, depth + 1, sib);
    }
}

void analyzeLinkedTreeRecursive(TreeNode* node, int current_depth, int* total, int* leaf, int* non_leaf, int* max_depth, int* max_degree) {
    if (node == NULL) return;

    (*total)++;
    if (current_depth > *max_depth) *max_depth = current_depth;

    int degree = 0;
    if (node->left) degree++;
    if (node->right) degree++;

    if (degree > *max_degree) *max_degree = degree;

    if (degree == 0) (*leaf)++;
    else (*non_leaf)++;

    analyzeLinkedTreeRecursive(node->left, current_depth + 1, total, leaf, non_leaf, max_depth, max_degree);
    analyzeLinkedTreeRecursive(node->right, current_depth + 1, total, leaf, non_leaf, max_depth, max_degree);
}

int checkComplete(TreeNode* node, int index, int total_nodes) {
    if (node == NULL) return 1;
    if (index > total_nodes) return 0;
    return checkComplete(node->left, 2 * index, total_nodes) &&
        checkComplete(node->right, 2 * index + 1, total_nodes);
}

void analyzeLinkedTree(TreeNode* root) {
    int total_nodes = 0, leaf_nodes = 0, non_leaf = 0;
    int max_depth = 0, max_degree = 0;

    analyzeLinkedTreeRecursive(root, 1, &total_nodes, &leaf_nodes, &non_leaf, &max_depth, &max_degree);

    printf("\n[ Linked Tree Info ]\n");
    printf("- Total Nodes : %d\n", total_nodes);
    printf("- Leaf Nodes: %d\n", leaf_nodes);
    printf("- Non Leaf Nodes : %d\n", non_leaf);
    printf("- Depth : %d\n", max_depth);
    printf("- Degree: %d\n", max_degree);

    int isComplete = checkComplete(root, 1, total_nodes);
    int isPerfect = (total_nodes == ((1 << max_depth) - 1));
    int isSkewed = (total_nodes == max_depth);

    printf("- 완전 이진트리 여부 (Complete) : %s\n", isComplete ? "Yes" : "No");
    printf("- 포화 이진트리 여부 (Perfect): %s\n", isPerfect ? "Yes" : "No");
    printf("- 편향 이진트리 여부 (Skewed): %s\n", isSkewed ? "Yes" : "No");
}

TreeNode* findNode(TreeNode* current, char target) {
    if (current == NULL) return NULL;
    if (current->data == target) return current;
    TreeNode* leftSearch = findNode(current->left, target);
    if (leftSearch != NULL) return leftSearch;
    return findNode(current->right, target);
}

TreeNode* findParentLinked(TreeNode* current, char target) {
    if (current == NULL) return NULL;
    if ((current->left != NULL && current->left->data == target) ||
        (current->right != NULL && current->right->data == target)) {
        return current;
    }
    TreeNode* leftSearch = findParentLinked(current->left, target);
    if (leftSearch != NULL) return leftSearch;
    return findParentLinked(current->right, target);
}

void printRelationsLinked(TreeNode* root, char target) {
    TreeNode* targetNode = findNode(root, target);
    if (targetNode == NULL) {
        printf("포인터 트리: 노드 '%c'를 찾을 수 없습니다.\n", target);
        return;
    }

    printf("\n[ 포인터 트리 - 노드 '%c' 관계 ]\n", target);


    if (targetNode->left != NULL) printf("- 왼쪽 자식: %c\n", targetNode->left->data);
    else printf("- 왼쪽 자식: 없음\n");
    if (targetNode->right != NULL) printf("- 오른쪽 자식: %c\n", targetNode->right->data);
    else printf("- 오른쪽 자식: 없음\n");

    TreeNode* parentNode = findParentLinked(root, target);
    if (parentNode == NULL) {
        printf("- 부모 노드: 없음 (루트 노드)\n");
        printf("- 형제 노드: 없음\n");
    }
    else {
        printf("- 부모 노드: %c\n", parentNode->data);
        TreeNode* sibling = (parentNode->left == targetNode) ? parentNode->right : parentNode->left;
        if (sibling != NULL) printf("- 형제 노드: %c\n", sibling->data);
        else printf("- 형제 노드: 없음\n");
    }
}

//메모리 비교용
void compareMemoryUsage(ArrayTree* arrTree, TreeNode* linkedRoot) {
    int total_nodes = 0;
    for (int i = 1; i <= arrTree->max_index; i++) {
        if (arrTree->data[i] != '\0') {
            total_nodes++;
        }
    }

    // 배열 메모리 계산
    int array_memory = arrTree->max_index * sizeof(char);
    int wasted_space = arrTree->max_index - total_nodes;
    float waste_ratio = (arrTree->max_index > 0) ? ((float)wasted_space / arrTree->max_index * 100.0f) : 0.0f;

    // 포인터 메모리 계산
    int pointer_memory = total_nodes * sizeof(TreeNode);

    printf("\n\n============= 메모리 =============\n");

    printf("\n[ 1. 배열 트리 메모리 분석 ]\n");
    printf(">> 총 메모리 사용량: %d Byte\n", array_memory);
    printf(">> 실제 데이터 수: %d개 / 배열 차지 인덱스: %d칸\n", total_nodes, arrTree->max_index);

    printf("\n[ 2. 포인터 트리 메모리 분석 ]\n");
    printf(">> 총 메모리 사용량: %d Byte\n", pointer_memory);
    printf(">> 할당된 노드 수: %d개 (노드 1개당 크기: %zu Byte)\n", total_nodes, sizeof(TreeNode));

}