#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <String.h>

//출력 함수
void printTree(char* input) {
	int print_depth = 0;
	int sib[100] = { 0 };
	int len = (int)strlen(input);

	printf("\n-----------Tree Structure-----------\n");

	for (int i = 0; i < len; i++) {
		char ch = input[i];

		if (ch >= 'A' && ch <= 'Z') {
			if (print_depth == 0) {
				printf("%c\n", ch);
			}
			else {
				for (int d = 0; d < print_depth - 1; d++) {
					if (sib[d]) printf("|   ");
					else printf("    ");
				}
				printf("+---%c\n", ch);
			}
		}
		else if (ch == '(' || ch == ',') {
			int temp_p = 0;
			int re_comma = 0;
			for (int j = i + 1; j < len; j++) {
				if (input[j] == '(') temp_p++;
				else if (input[j] == ')') {
					if (temp_p == 0) break;
					temp_p--;
				}
				else if (input[j] == ',' && temp_p == 0) {
					re_comma = 1;
					break;
				}
			}

			if (ch == '(') {
				sib[print_depth] = re_comma;
				print_depth++;
			}
			else {
				sib[print_depth - 1] = re_comma;
			}
		}
		else if (ch == ')') {
			print_depth--;
		}
	}
}

//정상적인 입력인지 판단 함수
int isValidTreeFormat(char* str) {
	ArrayStack* StrStack = createArrayStack(100);
	char prev = '\0';
	int length = strlen(str);

	for (int i = 0; i < length; i++) {
		char ch = str[i];
		if (ch == ' ' || ch == '\n') continue;

		//이상한 문자 감지
		if (!(ch >= 'A' && ch <= 'Z') && ch != '(' && ch != ')' && ch != ',') {
			return 0;
		}

		// (검사
		if (ch == '(') {
			//괄호 앞은 무조건 노드가 있어야함
			if (!(prev >= 'A' && prev <= 'Z')) return 0;
			pushArrayStack(StrStack, '(');
		}
		// )검사
		else if (ch == ')') {
			// 닫을게 없을 때
			if (emptyArrayStack(StrStack)) return 0;
			// 앞에(,가 나오면 안됨
			if (prev == '(' || prev == ',') return 0;
			popArrayStack(StrStack);
		}
		// ,검사
		else if (ch == ',') {
			// (, 뒤에 나오는 경우 
			if (emptyArrayStack(StrStack)) return 0;
			if (prev == '(' || prev == ',') return 0;
		}
		// 알파벳 검사
		else if (ch >= 'A' && ch <= 'Z') {
			// 연속으로 나오는 경우
			if (prev >= 'A' && prev <= 'Z') return 0;
			// ) 뒤에 바로 나오는 경우
			if (prev == ')') return 0;
		}

		prev = ch;
	}

	//여는 괄호가 다 안끝난 경우
	if (!emptyArrayStack(StrStack)) {
		return 0;
	}

	return 1; //굿
}

/*
* IN
* `A(B(E,F),C,D(G))
  OUT
A
+---B
|   +---E
|   +---F
+---C
+---D
	+---G

* 전체 노드의 수 -> 문자의 갯수 세기
* 단말 노드의 수 -> 자식이 없는 노드의 수
* 비단말 노드의 수 - > 자식이 있는 노드의 수
* 트리의 높이 -> 루트 노드에서 가장 깊은 단말 노드까지의 거리
* 트리의 차수-> 자식의 수 중 최댓값
  * 모든 노드의 차수 중 최댓값을 구합니다.
  * 노드의 차수를 계산하기 위해 스택을 사용합니다.
* 노드 `C`의 부모 노드
  * 노드 스택을 사용합니다.
* 노드 `C`의 자식 노드
  * 카운터 스택을 사용합니다.
* 트리를 왼쪽으로 눕힌 형태로 계층적으로 출력합니다.
  * 문자 `+`, `-`와 들여쓰기를 사용합니다.
*/

int main() {
	//char input[100] = "A(B(E,F),C,D(G)) ";
	printf("ex> A(B(E,F),C,D(G)) / Input >>");
	char input[100];
	scanf("%s", input);
	if (!isValidTreeFormat(input)) {
		printf("Error. Not Valid Style \n");
		return 1; // 프로그램 종료
	}

	int total_node = 0; //전체 노드의 수
	int last_node = 0; //임시 마지막 노드
	int leaf_node = 0; //단말 노드의 수
	int non_leaf_node = 0; //비단말 노드의 수
	int current_depth = 0; //현재 깊이
	int max_depth = 0; //최고 높이 
	int max_degree = 0;//트리의 차수 

	ArrayStack* node_stack = createArrayStack(100);
	//부모노드 보관 (노드 스택)
	ArrayStack* counter_stack = createArrayStack(100);
	//자식수 카운트(카운터 스택)

	char target = 'C'; //찾을 노드
	char parent_of_C = ' '; //부모노드
	char children_of_C[50] = ""; //자식노드

	for (int i = 0; i < strlen(input); i++)
	{
		switch (input[i])
		{
		case '(':
			non_leaf_node++;
			pushArrayStack(node_stack, last_node);
			pushArrayStack(counter_stack, 1);
			current_depth++;
			if (current_depth > max_depth) {
				max_depth = current_depth;
			}
			break;
		case ')': {
			if (!emptyArrayStack(node_stack)) {
				popArrayStack(node_stack);
			}
			if (!emptyArrayStack(counter_stack)) {
				int child_cnt = popArrayStack(counter_stack);
				if (child_cnt > max_degree) {
					max_degree = child_cnt;
				}
			}
			current_depth--;
			break;
		}
		case ',': {
			if (!emptyArrayStack(counter_stack)) {
				int count = popArrayStack(counter_stack);
				pushArrayStack(counter_stack, count + 1);
			}
			break;
		}
		default:
			if (input[i] >= 'A' && input[i] <= 'Z') {
				total_node++;
				last_node = input[i];
			}
			if (last_node == target) {
				if (!emptyArrayStack(node_stack)) {
					parent_of_C = (char)peekArrayStack(node_stack);
				}
			}

			if (!emptyArrayStack(node_stack) && (char)peekArrayStack(node_stack) == target) {
				int idx = strlen(children_of_C);
				children_of_C[idx] = last_node;
				children_of_C[idx + 1] = '\0';
			}
			break;
		}
	}
	leaf_node = total_node - non_leaf_node;
	destroyArrayStack(node_stack);
	destroyArrayStack(counter_stack);
	//printArrayStack(node_stack);

	printf("Total Node: %d\n", total_node);
	printf("Leaf Node: %d\n", leaf_node);
	printf("Non-Leaf Node: %d\n", non_leaf_node);
	printf("Tree Height: %d\n", max_depth);
	printf("Tree Degree: %d\n", max_degree);
	// 부모 노드 출력
	if (parent_of_C != ' ') {
		printf("Parent of '%c': %c\n", target, parent_of_C);
	}
	else {
		printf("Parent of '%c': None\n", target);
	}

	// 자식 노드 출력
	printf("Children of '%c': ", target);
	if (strlen(children_of_C) > 0) {
		for (int i = 0; i < (int)strlen(children_of_C); i++) {
			printf("%c ", children_of_C[i]);
		}
		printf("\n");
	}
	else {
		printf("None\n");
	}
	printTree(input);


}
//dd