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

    printArrayTree(tree, index * 2 + 1, depth + 1, sib); // 오른쪽

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("+---%c\n", tree->data[index]);

    printArrayTree(tree, index * 2, depth + 1, sib);     // 왼쪽
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

    printLinkedTree(node->right, depth + 1, sib);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("+---%c\n", node->data);

    printLinkedTree(node->left, depth + 1, sib);
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