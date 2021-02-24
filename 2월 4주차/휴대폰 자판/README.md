# 5670_휴대폰자판

#Trie #문자열 #입력

# Problem

1. 모듈이 단어의 첫 번째 글자를 추론하지는 않는다. 즉, 사전의 모든 단어가 같은 알파벳으로 시작하더라도 반드시 첫 글자는 사용자가 버튼을 눌러 입력해야 한다.
2. 길이가 1 이상인 문자열 cc...c이 지금까지 입력되었을 때, 사전 안의 모든 cc...c으로 시작하는 단어가 cc...cc로도 시작하는 글자 c가 존재한다면 모듈은 사용자의 버튼 입력 없이도 자동으로 c를 입력해 준다. 그렇지 않다면 사용자의 입력을 기다린다.

# Pre

유사 Trie 문제인 가사검색 [가사검색](https://www.notion.so/bbe07ce265404736ac98208422f6bfbc) 은 Trie 구조에서 얼마나 depth가 deep한 string을 꺼낼 수 있느냐

이 문제는 Trie 구조에서 같은 depth에 대해 얼마나 wide한 string을 알아낼 수 있느냐

## Trie 생성

- 입력의 끝을 알 수 없다.
- Trie.insert를 이용해서 Trie를 구성한다.
- typing() 을 이용하여 타이핑 수를 계산한다.

```cpp
while(cin >> N){
    Trie * root = new Trie;
    vector <string> keys;
    for(int i=0; i<N; i++){
        string key;
        cin >> key;
        keys.push_back(key);
        root->insert(key.c_str());
    }
    cout << fixed << setprecision(2) << typing(keys, root) << '\n';
    delete root;
}
```

## Typing 수 계산

- Trie.calc() 는 해당 Trie에서 유일한 next를 가질 때 : ( 자동으로 타이핑 할 수 있을 때 ) 를 체크 한 값.

    Trie 안의 멤버 hasSibling은 새로운 종류의 단어가 나올 때 마다 추가됨.
    → hasSibling이 1이라면 유일한 next를 가지므로 자동으로 타이핑을 할 수 있다는 뜻.

    Trie 가 isEnd 라면 한 단어의 Terminal이므로 멈춰서 고려해주어야 함.

```cpp
double typing(vector <string> &keys, Trie* root){
    int total = 0;
    for(auto &key : keys){
        total += ((int)key.size() - root->calc(key.c_str()));
    }
    return (double)total/keys.size();
}
```

# Code 2T

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
struct Trie{
    Trie* next[26];
    bool isEnd;
    int hasSibling;
    Trie(){
        fill(next, next+26, nullptr);
        isEnd = false;
        hasSibling = 0;
    }
    ~Trie(){
        for(int i=0; i<26; i++) delete next[i];
    }
    void insert(const char* key){
        if(*key == '\0'){
            isEnd = true;
            return;
        }
        int curr = *key - 'a';
        if(!next[curr]){
            next[curr] = new Trie;
            hasSibling++;
        }
        next[curr]->insert(key+1);
    }
    int calc(const char* key){
        if(*key == '\0'){
            return 0;
        }
        int curr = *key-'a';
        if(next[curr]->hasSibling == 1 && !(next[curr]->isEnd)){
            return 1+next[curr]->calc(key+1);
        }else{
            return next[curr]->calc(key+1);
        }
    }
};

double typing(vector <string> &keys, Trie* root){
    int total = 0;
    for(auto &key : keys){
        total += ((int)key.size() - root->calc(key.c_str()));
    }
    return (double)total/keys.size();
}

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N;
    while(cin >> N){
        Trie * root = new Trie;
        vector <string> keys;
        for(int i=0; i<N; i++){
            string key;
            cin >> key;
            keys.push_back(key);
            root->insert(key.c_str());
        }
        cout << fixed << setprecision(2) << typing(keys, root) << '\n';
        delete root;
    }

}
int main(){
    input();
}
```

![5670_%E1%84%92%E1%85%B2%E1%84%83%E1%85%A2%E1%84%91%E1%85%A9%E1%86%AB%E1%84%8C%E1%85%A1%E1%84%91%E1%85%A1%E1%86%AB%2043e4523c27bd42a5a469ce3c8604ead4/5670__.png](5670_%E1%84%92%E1%85%B2%E1%84%83%E1%85%A2%E1%84%91%E1%85%A9%E1%86%AB%E1%84%8C%E1%85%A1%E1%84%91%E1%85%A1%E1%86%AB%2043e4523c27bd42a5a469ce3c8604ead4/5670__.png)

# Code

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Trie {
	bool isEnd;
	int hasNext;
	Trie* next[26];

	Trie() {
		fill(next, next + 26, nullptr);
		isEnd = false;
		hasNext = 0;
	}

	~Trie() {
		for (int i = 0; i < 26; i++) if (next[i]) delete next[i];
	}

	void insert(const char* key) {
		if (*key == '\0') {
			isEnd = true;
			return;
		}
		int curr = *key - 'a';
		if (!next[curr]) {
			next[curr] = new Trie;
			hasNext++;
		}
		next[curr]->insert(key + 1);
	}

	int find(const char* key, int sum) {
		if (*key == '\0') {
			return sum;
		}
		int curr = *key - 'a';

		if (next[curr]->hasNext == 1 && !next[curr]->isEnd) {
			return next[curr]->find(key + 1, sum);
		}
		else {
			return next[curr]->find(key + 1, sum + 1);
		}
	}

};

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int testCase;
	string word;
	vector <string> words;
	while (cin>>testCase) {
		Trie* root = new Trie;
		words.clear();
		double answer = 0;
		for (int i = 0; i < testCase; i++) {
			cin >> word;
			words.push_back(word);
			root->insert(word.c_str());
		}
		for (auto& word : words) {
			answer += root->find(word.c_str(), 0);
		}
		cout << fixed << setprecision(2) << answer/testCase << '\n';
		delete root;
	}
}
int main() {
	input();
}
```

# Reference