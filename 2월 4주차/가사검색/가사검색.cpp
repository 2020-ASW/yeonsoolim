//#include <string>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//typedef pair<string, int> psi;
//vector <psi> valNlen;
//int wordCnt[100000];
//
//bool cmp(const psi& a, const psi& b) {
//    if (a.second == b.second) {
//        return a.first < b.first;
//    }
//    return a.second < b.second;
//}
//bool boundCmp(const psi& a, const psi& b) {
//    return a.second < b.second;
//}
//int matching(string query) {
//    int sum = 0;
//    auto start = lower_bound(valNlen.begin(), valNlen.end(), psi(query, query.length()), boundCmp) - valNlen.begin();
//    auto end = upper_bound(valNlen.begin(), valNlen.end(), psi(query, query.length()), boundCmp) - valNlen.begin();
//    vector <psi>::iterator iter;
//    for (iter = valNlen.begin() + start; iter != valNlen.begin() + end; ++iter) {
//        if (query.length() != iter->first.length()) continue;
//        bool matchFlag = true;
//        for (int i = 0; i < query.length(); i++) {
//            if (query[i] != iter->first[i] && query[i] != '?' && iter->first[i] != '?') {
//                matchFlag = false;
//                break;
//            }
//        }
//        sum += (matchFlag ? 1 : 0);
//    }
//    return sum;
//}
//
//vector<int> solution(vector<string> words, vector<string> queries) {
//    vector<int> answer;
//    for (auto& word : words) {
//        valNlen.push_back(psi(word, word.length()));
//        wordCnt[word.length()]++;
//    }
//    sort(valNlen.begin(), valNlen.end(), cmp);
//    for (auto& query : queries) {
//        if (query[0] == '?' && query[query.length() - 1] == '?') answer.push_back(wordCnt[query.length()]);
//        else answer.push_back(matching(query));
//    }
//    return answer;
//}
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