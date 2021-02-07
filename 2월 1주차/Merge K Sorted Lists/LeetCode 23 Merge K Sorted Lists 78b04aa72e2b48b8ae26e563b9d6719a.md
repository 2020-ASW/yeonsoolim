# LeetCode 23 Merge K Sorted Lists

# sort # Histogram

# 문제

Linked List 형태로 List의 쌍 여러개가 주어진다.

이를 오름차순으로 정렬하여 하나의 List로 반환해야 한다.

- 정의된 List 자료 구조

    ```cpp
    struct ListNode {
    	int val;
    	ListNode *next;
    	ListNode() : val(0), next(nullptr) {}
    	ListNode(int x) : val(x), next(nullptr) {}
    	ListNode(int x, ListNode *next) : val(x), next(next) {}
    }
    ```

# Pre

- 제약 조건
    1. **나올 수 있는 숫자의 범위가 -10,000  ~  10,000 까지다.**
    2. **2만 개에서는 Histogram보다 빠른게 없지 않을까**

# Solve

1. **모든 연결 리스트를 돌면서 Histogram을 만들어 준다.**
    1. **가장 앞에 노드를 따로 처리해준다.**
    2. **그 후, nextNode가 있다면 while안에서 처리 해준다.**
    3. **입력 Input에서 [], [[]] 과 같은 예외는 0으로 피할 수 있다.**

    ```cpp
    for(auto &list : lists){
        if(list == 0)continue;
        ListNode* curr = list;
        if(curr->val<0) 
    				minusHist[abs(curr->val)]++;
        else 
    				plusHist[curr->val]++;

        while(curr->next){
            curr = curr->next;
            if(curr->val<0) minusHist[abs(curr->val)]++;
            else plusHist[curr->val]++;
        }            
    }
    ```

2. **다시 +- 를 고려하면서 오름차순으로 새로운 LinkedList에 넣어 준다.**

    ```cpp
    ListNode* root = new ListNode();
    ListNode* answer = root;
    for(int i=10000; i>0; i--){
        if(minusHist[i]){
            for(int k=0; k<minusHist[i]; k++){
                ListNode* curr = new ListNode(-1*i);
                answer->next = curr;
                answer = answer->next;
            }
            
        }
    }
    for(int i=0; i<10001; i++){
        if(plusHist[i]){
            for(int k=0; k<plusHist[i]; k++){
                ListNode* curr= new ListNode(i);
                answer->next = curr;
                answer = answer->next;
            }
        }
    }
    ```

# Error

1. **answer 노드를 다음으로 옮겨가면서 새로운 Node를 이어주었는데, 
마지막에 answer를 return하면 마지막 Node만 가르키는 list가 return 된다.**

    ⇒ root를 계속 가르키고 있는 Node가 필요햐다.

2. 

    → return되는 root의 젤 처음 Node에는 0이 있다.

    ⇒ next를 return해서 버려준다.