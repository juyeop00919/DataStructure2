#include "MenuTree.h"

int main() {
    BTree* tree = create_btree(100);
    char line[256];
	printf("입력 예 : \nI(NSERT) / A\nI(NSERT) /A L B\nD(ELETE) /A/L\nU(PDATE) /A/L C\nR(EAD) /A\nP(RINT)\nEXIT입력시 종료\n");
    while (1) {
        //print_btree(tree);
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;

        //개행 문자 제거
        line[strcspn(line, "\r\n")] = 0; //끝에 붙은 엔터키를 NULL로 변경
        if (strlen(line) == 0) continue;

        //명령어
        char* cmd = strtok(line, " \t"); //빈칸을 기준으로 잘라서 CMD에 저장
        if (!cmd) continue;

        if (strcmp(cmd, "EXIT") == 0) { // EXIT 입력시 종료
            break;
        }
        else if (strcmp(cmd, "INSERT") == 0 || strcmp(cmd, "I") == 0) {
            char* arg1 = strtok(NULL, " \t"); //다음 빈칸을 기준으로 잘라서 ARG1에 저장
            char* arg2 = strtok(NULL, " \t"); 
            char* arg3 = strtok(NULL, " \t");
            char* extra = strtok(NULL, " \t");

            if (extra != NULL) {
                printf("Error: 명령에 필요한 인자의 개수가 초과되었습니다.\n");
                continue;
            }

			// Insert / A (루트 노드 생성)
            if (arg1 != NULL && strcmp(arg1, "/") == 0 && arg2 != NULL && arg3 == NULL) {
                if (validate_insert_root(tree)) {
                    tree = insert_root(tree, arg2[0]);
                }
            }
            // Insert /A L B (자식 노드 생성)
            else if (arg1 != NULL && arg2 != NULL && arg3 != NULL) {
                if (validate_insert_child(tree, arg1, arg2[0], arg3[0])) {
                    tree = insert_child(tree, arg1, arg2[0], arg3[0]);
                }
            }
            else {
                printf("Error: Insert 명령의 인자 개수나 형식이 맞지 않습니다.\n");
            }
        }
        else if (strcmp(cmd, "DELETE") == 0 || strcmp(cmd, "D") == 0) {
            char* arg1 = strtok(NULL, " \t");
            char* extra = strtok(NULL, " \t");

            if (extra != NULL || arg1 == NULL) {
                printf("Error: Delete 명령의 인자 개수가 맞지 않습니다.\n");
                continue;
            }
            if (validate_delete(tree, arg1)) {
                tree = delete_node(tree, arg1);
            }
        }
        else if (strcmp(cmd, "UPDATE") == 0 || strcmp(cmd, "U") == 0) {
            char* arg1 = strtok(NULL, " \t");
            char* arg2 = strtok(NULL, " \t");
            char* extra = strtok(NULL, " \t");

            if (extra != NULL || arg1 == NULL || arg2 == NULL) {
                printf("Error: Update 명령의 인자 개수가 맞지 않습니다.\n");
                continue;
            }
            if (validate_update(tree, arg1, arg2[0])) {
                tree = update_value(tree, arg1, arg2[0]);
            }
        }
        else if (strcmp(cmd, "READ") == 0 || strcmp(cmd, "R") == 0) {
            char* arg1 = strtok(NULL, " \t");
            char* extra = strtok(NULL, " \t");

            if (extra != NULL || arg1 == NULL) {
                printf("Error: Read 명령의 인자 개수가 맞지 않습니다.\n");
                continue;
            }
            if (validate_read(tree, arg1)) {
                read_child(tree, arg1);
            }
        }
        else if (strcmp(cmd, "PRINT") == 0 || strcmp(cmd, "P") == 0) {
            char* extra = strtok(NULL, " \t");
            if (extra != NULL) {
                printf("Error: Print 명령은 인자를 받지 않습니다.\n");
                continue;
            }
            print_btree(tree);
        }
        else {
            printf("Error: 잘못된 명령어를 입력하였습니다.\n");
        }
    }

    destroy_btree(tree);
    return 0;
}