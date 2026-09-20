# 과제 02 - 배열과 포인터 기반 이진트리 구현 비교 분석

## 메모리 사용량 비교
### 성능프로파일러로 비교
|  | 일반이진트리 | 완전이진트리 | 편향이진트리 |
| --- | --- | --- | --- |
| 배열 | <img width="398" height="168" alt="배열일반이진트리" src="https://github.com/user-attachments/assets/e38b575f-5b04-4dcf-b80c-4ae8456c340d" /> | <img width="353" height="163" alt="배열완전이진트리" src="https://github.com/user-attachments/assets/84bc830a-ca04-4e9c-807a-35f47b9ae823" />| <img width="392" height="166" alt="배열편향이진트리" src="https://github.com/user-attachments/assets/55b12a6c-49fb-4c36-8e1f-33b3c75f5aef" />   |
| 포인터 | <img width="415" height="167" alt="포인터일반이진트리" src="https://github.com/user-attachments/assets/38801986-0244-427b-b20e-8a729817c979" /> | <img width="391" height="163" alt="포인터완전이진트리" src="https://github.com/user-attachments/assets/77b76907-cc0e-4ae9-9edb-cc0ab2463cc9" />|  <img width="468" height="161" alt="포인터편향이진트리" src="https://github.com/user-attachments/assets/c07f4c05-9f6d-4eaf-bbed-64b08810475d" />  |
| 입력 | A(B(D,E),C(,F))| A(B(D,E),C(F)) | A(,B(,C(,D(,E(,F(,G(,H)))))))

- 완전 이진트리의 경우 노드가 위에서 아래로 왼쪽에서 오른쪽까지 꽉 차게되므로 배열 인덱스에 빈틈이 생기지 않아서 포인터에 비해 **배열이 메모리 측면에서 효율적**입니다.
  
- 편향 이진트리의 경우 우편향 트리를 배열에 저장하면 자식 노드의 인덱스가 증가하여 최대 인덱스를 사용하게 되지만 빈공간은 \0값으로 차게되어 배열에 비해 **포인터가 메모리 측면에서 효율적**입니다.

- 일반 이진트리의 경우 입력에 따라 다르지만 현재의 입력 예에서는 배열에선 낭비되는 공간이 1칸이고 포인터는 노드마다 좌우를 가르키는 포인터를 가지고 있기에 이 같은 경우는 **배열이 효율적**입니다.

| |일반이진트리
|---|---|
|배열| <img width="433" height="166" alt="배열일반이진트리3" src="https://github.com/user-attachments/assets/27dfd19e-b1b0-43be-b82f-be68555aa95f" />|
|포인터| <img width="433" height="166" alt="포인터일반이진트리3" src="https://github.com/user-attachments/assets/de8d7eb3-7112-4803-b7b7-313dc4bb675a" />|
|예| A(B,C(,D(,E(,F(,G(,H(,I)))))))

- 이와 같은 경우에선 배열은 9개의 문자를 저장하기 위해 255번 인덱스까지 사용하게 됩니다. 그러나 실제데이터는 9칸뿐이므로 246칸이 **\0** 으로 **포인터가 메모리 측면에서 효율적**입니다.
---
### 코드로 비교 
---
```c
// 배열 메모리 계산
int array_memory = arrTree->max_index * sizeof(char);
int wasted_space = arrTree->max_index - total_nodes;

// 포인터 메모리 계산
int pointer_memory = total_nodes * sizeof(TreeNode);
```
| 일반이진트리 1 | 일반이진트리 2 | 완전이진트리 | 편향이진트리 
|---|---|---|---|
|<img width="462" height="190" alt="일반이진트리 1" src="https://github.com/user-attachments/assets/a86d4ad9-c80b-4a20-85bd-bbb1c7261890" />|<img width="473" height="187" alt="일반이진트리2" src="https://github.com/user-attachments/assets/ddc992ef-c3a1-4160-889a-e643549ab392" />|<img width="460" height="176" alt="완전이진트리" src="https://github.com/user-attachments/assets/31721565-c1a4-4f92-a6a3-9529f0ea705f" />|<img width="455" height="180" alt="편향이진트리" src="https://github.com/user-attachments/assets/cc46efb6-6f2c-41e0-a6d1-6531cf1562c4" />|
|A(B(D,E),C(,F))|A(B,C(,D(,E(,F(,G(,H(,I)))))))|A(B(D,E),C(F))|A(,B(,C(,D(,E(,F(,G(,H)))))))

- 직접 코드를 통해 비교해보면서 이론상 편향 이진트리는 포인터 방식이 배열보다 메모리 효율이 좋다고 생각했으나 적은 깊이의 경우 오히려 포인터가 메모리를 더 낭비하는 모순적인 결과를 확인했습니다.
- 이미지
- 노드수가 적은 초반에는 배열의 지수적 낭비 ($2^N-1$) 보다 포인터의 고정 바이트가 더 무겁게 작용합니다.
- 수학적으로 트리의 깊이가 8에 도달하는 순간 포인터의 메모리 효율이 배열을 역전함을 알 수 있었습니다. 

## 자식 출력 프로그램 분석
### 배열
```c
printf("- 부모 노드: %c\n", tree->data[target_idx / 2]);

int left = target_idx * 2;
int right = target_idx * 2 + 1;

int sib = (target_idx % 2 == 0) ? (target_idx + 1) : (target_idx - 1);
```
- 배열은 메모리가 연속적으로 할당되어있고 트리 구조가 인덱스에 수학적으로 위치하여 트리가 아무리 커져도 반복문이나 순회없이 상수시간인 $O(1)$ 만에 모든 노드의 위치를 계산할 수 있습니다.

### 포인터 
```c
TreeNode* findParentLinked(TreeNode* current, char target) {
    if (current == NULL) return NULL;
    // 부모를 찾을 때까지 루트부터 왼쪽, 오른쪽을 재귀적으로 모두 뒤져야 함
    if ((current->left != NULL && current->left->data == target) ||
        (current->right != NULL && current->right->data == target)) {
        return current;
    }
    TreeNode* leftSearch = findParentLinked(current->left, target);
    if (leftSearch != NULL) return leftSearch;
    return findParentLinked(current->right, target);
}
```
- 현재 노드에서 위로 올라가는 역방향 포인터가 없기때문에 트리의 루트부터 시작하여 전체 노드를 재귀적으로 순회해야만 부모를 찾을 수 있습니다. 형제 노드 역시 부모를  먼저 찾아야 하므로 최악의 경우 모든 트리를 방문하는 $O(N)$ 의 시간복잡도가 발생합니다.


## 결론

일반적으로 **일반 이진트리**라는 카테고리 안에서 노드들이 **촘촘한 완전 이진트리 형태**에 가까울 수록 **배열**이 유리하고 **중간에 빈 노드가 많아 깊이만 깊어지는 불균형 형태**일 수록 메모리 측면에서 **포인터 연결구조**가 유리한 걸 알 수 있었습니다.

자식 출력 프로그램을 분석한 결과 포인터방식보다 배열이 시간복잡도에서 효율적인걸 알 수 있었습니다.






