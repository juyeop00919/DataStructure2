#include "Traversal.h"


typedef struct StackNode {
    TreeNode* treeNode;        // 데이터: 이진트리 노드의 주소
    struct StackNode* next;    // 포인터: 아래쪽(다음) 스택 노드를 가리킴
} StackNode;

typedef struct {
    StackNode* top;            // 스택의 맨 꼭대기를 가리키는 포인터
} Stack;


void initStack(Stack* s) {
    s->top = NULL;
}


int isEmpty(Stack* s) {
    return (s->top == NULL);
}


void push(Stack* s, TreeNode* node) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = node;
    newNode->next = s->top; 
    s->top = newNode;      
}

TreeNode* pop(Stack* s) {
    if (isEmpty(s)) return NULL;

    StackNode* temp = s->top;          
    TreeNode* popData = temp->treeNode;  

    s->top = temp->next;                
    free(temp);                         

    return popData;
}

TreeNode* peek(Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->top->treeNode;
}

// 입력
TreeNode* buildTree(const char* str) {
    Stack s;
    initStack(&s);
    TreeNode* root = NULL;
    TreeNode* last_created = NULL;
    int state = 0; // 0: 좌측 1: 우측 자식을 기다림

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c == ' ' || c == '\n') continue;

        // 알파벳인 경우 노드 생성
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
            node->data = c;
            node->left = NULL;
            node->right = NULL;

            if (root == NULL) {
                root = node; // 첫 노드는 루트
            }
            else {
                if (isEmpty(&s)) {
                    printf("오류: 잘못된 괄호 표기법입니다. (고립된 노드 발생)\n");
                    return NULL;
                }
                TreeNode* parent = peek(&s);
                if (state == 0) {
                    parent->left = node;
                }
                else {
                    parent->right = node;
                }
            }
            last_created = node;
        }
        else if (c == '(') {
            if (last_created == NULL) {
                printf("오류: 잘못된 괄호 표기법입니다. (부모 노드 없음)\n");
                return NULL;
            }
            push(&s, last_created);
            state = 0; // 다음은 왼쪽 자식
        }
        else if (c == ',') {
            state = 1; // 다음은 오른쪽 자식
        }
        else if (c == ')') {
            if (isEmpty(&s)) {
                printf("오류: 괄호의 짝이 맞지 않습니다. (닫는 괄호 초과)\n");
                return NULL;
            }
            pop(&s);
        }
        else {
            printf("오류: 허용되지 않은 문자 '%c'가 포함되어 있습니다.\n", c);
            return NULL;
        }
    }

    if (!isEmpty(&s)) {
        printf("오류: 괄호의 짝이 맞지 않습니다. (여는 괄호 초과)\n");
        return NULL;
    }

    return root;
}

// 전위 순회
void preorder(TreeNode* tree) {
    if (tree == NULL) return;

    Stack s;
    initStack(&s);
    push(&s, tree);

    while (!isEmpty(&s)) {
        TreeNode* curr = pop(&s);
        printf("%c ", curr->data);

        // 스택은 LIFO(후입선출)이므로 오른쪽 자식을 먼저 넣어야 왼쪽 자식이 먼저 꺼내짐
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
}

// 중위 순회
void inorder(TreeNode* tree) {
    Stack s;
    initStack(&s);
    TreeNode* curr = tree;

    while (curr != NULL || !isEmpty(&s)) {
        // 왼쪽 끝까지 이동하며 스택에 푸시
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }

        curr = pop(&s);
        printf("%c ", curr->data);

        // 오른쪽 서브트리로 이동
        curr = curr->right;
    }
}

//후위 순회
void postorder(TreeNode* tree) {
    if (tree == NULL) return;

    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    push(&s1, tree);

    // Root -> Right -> Left 순으로 s2에 담음
    while (!isEmpty(&s1)) {
        TreeNode* curr = pop(&s1);
        push(&s2, curr);

        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }

    // s2에서 꺼내면 Left -> Right -> Root 순서가 됨 (후위 순회)
    while (!isEmpty(&s2)) {
        TreeNode* curr = pop(&s2);
        printf("%c ", curr->data);
    }
}

void freeTree(TreeNode* tree) {
    if (tree == NULL) return;
    Stack s1, s2;
    initStack(&s1); initStack(&s2);

    push(&s1, tree);
    while (!isEmpty(&s1)) {
        TreeNode* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }

    while (!isEmpty(&s2)) {
        TreeNode* curr = pop(&s2);
        free(curr);
    }
}