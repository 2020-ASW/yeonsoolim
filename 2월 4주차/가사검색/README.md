# 가사검색

---

# **문제 설명**

**[본 문제는 정확성과 효율성 테스트 각각 점수가 있는 문제입니다.]**

친구들로부터 천재 프로그래머로 불리는 **프로도**는 음악을 하는 친구로부터 자신이 좋아하는 노래 가사에 사용된 단어들 중에 특정 키워드가 몇 개 포함되어 있는지 궁금하니 프로그램으로 개발해 달라는 제안을 받았습니다.그 제안 사항 중, 키워드는 와일드카드 문자중 하나인 '?'가 포함된 패턴 형태의 문자열을 뜻합니다. 와일드카드 문자인 '?'는 글자 하나를 의미하며, 어떤 문자에도 매치된다고 가정합니다. 예를 들어 `"fro??"`는 `"frodo"`, `"front"`, `"frost"` 등에 매치되지만 `"frame"`, `"frozen"`에는 매치되지 않습니다.

가사에 사용된 모든 단어들이 담긴 배열 `words`와 찾고자 하는 키워드가 담긴 배열 `queries`가 주어질 때, 각 키워드 별로 매치된 단어가 몇 개인지 **순서대로** 배열에 담아 반환하도록 `solution` 함수를 완성해 주세요.

### **가사 단어 제한사항**

- `words`의 길이(가사 단어의 개수)는 2 이상 100,000 이하입니다.
- 각 가사 단어의 길이는 1 이상 10,000 이하로 빈 문자열인 경우는 없습니다.
- 전체 가사 단어 길이의 합은 2 이상 1,000,000 이하입니다.
- 가사에 동일 단어가 여러 번 나올 경우 중복을 제거하고 `words`에는 하나로만 제공됩니다.
- 각 가사 단어는 오직 알파벳 소문자로만 구성되어 있으며, 특수문자나 숫자는 포함하지 않는 것으로 가정합니다.

### **검색 키워드 제한사항**

- `queries`의 길이(검색 키워드 개수)는 2 이상 100,000 이하입니다.
- 각 검색 키워드의 길이는 1 이상 10,000 이하로 빈 문자열인 경우는 없습니다.
- 전체 검색 키워드 길이의 합은 2 이상 1,000,000 이하입니다.
- 검색 키워드는 중복될 수도 있습니다.
- 각 검색 키워드는 오직 알파벳 소문자와 와일드카드 문자인 `'?'` 로만 구성되어 있으며, 특수문자나 숫자는 포함하지 않는 것으로 가정합니다.
- 검색 키워드는 와일드카드 문자인 `'?'`가 하나 이상 포함돼 있으며, `'?'`는 각 검색 키워드의 접두사 아니면 접미사 중 하나로만 주어집니다.
    - 예를 들어 `"??odo"`, `"fro??"`, `"?????"`는 가능한 키워드입니다.
    - 반면에 `"frodo"`(`'?'`가 없음), `"fr?do"`(`'?'`가 중간에 있음), `"?ro??"`(`'?'`가 양쪽에 있음)는 불가능한 키워드입니다.

### **입출력 예**

[Untitled](https://www.notion.so/f98d70eabf954077acb7d61f0ab1d932)

### **입출력 예에 대한 설명**

- `"fro??"`는 `"frodo"`, `"front"`, `"frost"`에 매치되므로 3입니다.
- `"????o"`는 `"frodo"`, `"kakao"`에 매치되므로 2입니다.
- `"fr???"`는 `"frodo"`, `"front"`, `"frost"`, `"frame"`에 매치되므로 4입니다.
- `"fro???"`는 `"frozen"`에 매치되므로 1입니다.
- `"pro?"`는 매치되는 가사 단어가 없으므로 0 입니다.

---

# 문제 풀이

## 1. lower_bound ~ upper_bound 까지 탐색하여 매칭.

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<string,int> psi;
vector <psi> valNlen;
int wordCnt[100000];

bool cmp(const psi &a, const psi &b){
    if(a.second == b.second){
        return a.first<b.first;
    }
    return a.second<b.second;
}
bool boundCmp(const psi &a, const psi &b){
    return a.second<b.second;
}
int matching(string query){
    int sum = 0;
    auto start = lower_bound(valNlen.begin(), valNlen.end(), psi(query,query.length()), boundCmp) - valNlen.begin();
    auto end = upper_bound(valNlen.begin(), valNlen.end(), psi(query,query.length()), boundCmp) - valNlen.begin();
    vector <psi>::iterator iter;
    for(iter = valNlen.begin()+start; iter!=valNlen.begin()+end; ++iter){
        if(query.length() != iter->first.length()) continue;
        bool matchFlag = true;
        for(int i=0; i<query.length(); i++){
            if(query[i] != iter->first[i] && query[i] != '?' && iter->first[i] != '?'){
                matchFlag = false;
                break;
            }
        }
        sum += (matchFlag?1:0);
    }
    return sum;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    for(auto &word : words){
        valNlen.push_back(psi(word, word.length()));        
        wordCnt[word.length()]++;
    } 
    sort(valNlen.begin(), valNlen.end(), cmp);
    for(auto &query : queries){
        if(query[0] == '?' && query[query.length()-1] == '?') answer.push_back(wordCnt[query.length()]);
        else answer.push_back(matching(query));
    }
    return answer;
}
```

### 특.케.

모두 ? 로 이루어진 입력에 주의해야함.

### 결과

```
정확성  테스트
테스트 1 〉통과 (0.05ms, 3.97MB)테스트 2 〉통과 (0.03ms, 3.96MB)테스트 3 〉통과 (0.03ms, 3.98MB)테스트 4 〉통과 (0.03ms, 3.94MB)테스트 5 〉통과 (0.03ms, 3.96MB)테스트 6 〉통과 (0.03ms, 3.93MB)테스트 7 〉통과 (0.27ms, 3.89MB)테스트 8 〉통과 (0.24ms, 3.84MB)테스트 9 〉통과 (0.32ms, 3.88MB)테스트 10 〉통과 (0.23ms, 3.93MB)테스트 11 〉통과 (0.20ms, 3.89MB)테스트 12 〉통과 (0.26ms, 3.94MB)테스트 13 〉통과 (2.21ms, 4.18MB)테스트 14 〉통과 (1.76ms, 3.97MB)테스트 15 〉통과 (1.97ms, 3.96MB)테스트 16 〉통과 (2.38ms, 4.02MB)테스트 17 〉통과 (1.72ms, 3.98MB)테스트 18 〉통과 (2.28ms, 4.16MB)효율성  테스트
테스트 1 〉실패 (시간 초과)테스트 2 〉실패 (시간 초과)테스트 3 〉통과 (37.39ms, 24.4MB)테스트 4 〉통과 (10.34ms, 9.84MB)테스트 5 〉통과 (10.19ms, 10MB)채점 결과
정확성: 25.0
효율성: 45.0
합계: 70.0 / 100.0
```

## 2. Trie

- 물음표 (?) 가 마지막 글자에 있다면 그 뒤는 모든 문자와 매칭할 수 있다.
→ 노드 별로 count를 새려놓는다.
→ 물음표로 시작되는 것은 reverse를 이용한다.
- 일반적인 Trie와 뒤집어진 Trie 를 함께 구성한다.

```cpp
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int ALPHABET = 26;
struct Trie {
    Trie* next[ALPHABET];
    bool isEnd;
    int count;
    Trie() {
        fill(next, next + ALPHABET, nullptr);
        isEnd = false;
        count = 0;
    }

    ~Trie() {
        for (int i = 0; i < ALPHABET; i++) if (next[i]) delete next[i];
    }

    void insert(const char* key) {
        count++;
        if (*key == '\0') {
            isEnd = true;
            return;
        }
        int curr = *key - 'a';
        if (!next[curr]) next[curr] = new Trie;
        next[curr]->insert(key + 1);
        return;
    }
    int find(const char* key) {
        if (*key == '?') {
            return count;
        }
        int curr = *key - 'a';
        if (next[curr] == NULL) return 0;
        return next[curr]->find(key + 1);
    }

};
Trie* root[10001];
Trie* reverseRoot[10001];
vector<int> findTrie(vector<string> queries) {
    vector<int> answer;
    for (string& query : queries) {
        int querySize = query.length();
        if (query[0] == '?') {
            reverse(query.begin(), query.end());
            if (reverseRoot[querySize] == NULL) answer.push_back(0);
            else answer.push_back(reverseRoot[querySize]->find(query.c_str()));
        }
        else {
            if (root[querySize] == NULL) answer.push_back(0);
            else answer.push_back(root[querySize]->find(query.c_str()));
        }

    }

    return answer;
}
void insertTrie(vector<string> words) {
    for (string& word : words) {
        int wordSize = word.length();
        if (!root[wordSize]) root[wordSize] = new Trie;
        if (!reverseRoot[wordSize]) reverseRoot[wordSize] = new Trie;

        root[wordSize]->insert(word.c_str());
        reverse(word.begin(), word.end());
        reverseRoot[wordSize]->insert(word.c_str());
    }

}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;

    insertTrie(words);

    return findTrie(queries);
}
```

### Error

1. queries에는 Trie에 없는 것이 들어올 수 있다.
→ NULL 참조를 잘 확인해주어야 한다.
2. ?가 나왔을때 바로 cnt를 반환하면 길이를 확인할 수 없다.
→ 길이별로 다른 Trie를 사용해야한다.