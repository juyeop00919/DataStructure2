# 과제 02 - 배열과 포인터 기반 이진트리 구현 비교 분석

## 메모리 사용량 비교
|  | 일반이진트리 | 완전이진트리 | 편향이진트리 |
| --- | --- | --- | --- |
| 배열 | <img width="398" height="168" alt="배열일반이진트리" src="https://github.com/user-attachments/assets/952bfbd9-a871-4c54-bef1-2b7101044628" /> | <img width="353" height="163" alt="배열완전이진트리" src="https://github.com/user-attachments/assets/ccac1039-57a0-4da4-88aa-6d5f97ddccda" />| <img width="392" height="166" alt="배열편향이진트리" src="https://github.com/user-attachments/assets/6e743883-bc41-400d-8e25-4c93ea32a2c8" />   |
| 포인터 | <img width="415" height="167" alt="포인터일반이진트리" src="https://github.com/user-attachments/assets/08c8f3f1-6160-4130-b96c-8bf993c92b8e" /> | <img width="391" height="163" alt="포인터완전이진트리" src="https://github.com/user-attachments/assets/cdb95c52-5495-4db1-b1fe-b1946f3666d1" /> |  <img width="468" height="161" alt="포인터편향이진트리" src="https://github.com/user-attachments/assets/19b3cea6-a708-4571-86a4-a301b0cecc5d" />  |
| 입력 |  A(B(D,E),C(,F))| A(B(D,E),C(F)) | A(,B(,C(,D)))

- 완전 이진트리의 경우 노드가 위에서 아래로 왼쪽에서 오른쪽까지 꽉 차게되므로 배열 인덱스에 빈틈이 생기지 않아서 배열이 포인터에 비해 메모리 측면에서 효율적입니다.
  
- 편향 이진트리의 경우 우편향 트리를 배열에 저장하면 자식 노드의 인덱스가 증가하여 최대 인덱스를 사용하게 되지만 빈공간은 \0값으로 차게되어 포인터가 배열에 비해 메모리 측면에서 효율적입니다.

- 일반 이진트리의 경우 입력에 따라 다르지만 현재의 입력 예에서는 배열에선 낭비되는 공간이 1칸이고 포인터는 노드마다 좌우를 가르키는 포인터를 가지고 있기에 이 같은 경우는 배열이 우세합니다.

| |일반이진트리
|---|---|
|배열| <img width="433" height="166" alt="배열일반이진트리3" src="https://github.com/user-attachments/assets/efe73e35-90c2-4923-91f3-8c58c2eba3df" />|
|포인터| <img width="411" height="164" alt="포인터일반이진트리3" src="https://github.com/user-attachments/assets/0f8ee346-5262-4f3a-8d03-1d41a4f32a65" />|
|예| A(B(C(D,),),E(,F(,G(H,I))))

- 이와 같은 경우에선 배열은 9개의 문자를 저장하기 위해 31번 인덱스까지 사용하게 됩니다. 그러나 실제데이터는 9칸뿐이므로 22칸이 **\0** 으로 포인터가 메모리 측면에서 효율적입니다.

### 결론

일반적으로 **일반 이진트리**라는 카테고리 안에서 노드들이 **촘촘한 완전 이진트리 형태**에 가까울 수록 **배열**이 유리하고 **중간에 빈 노드가 많아 깊이만 깊어지는 불균형 형태**일 수록 메모리 측면에서 **포인터 연결구조**가 유리한 걸 알 수 있었습니다.








