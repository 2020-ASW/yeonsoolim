#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
struct Trie{
    Trie* next[27];
    bool isEnd;
    int hasNext;

    Trie(){
        fill(next, next+27, nullptr);
        isEnd = false;
        hasNext = 0;
    }

    ~Trie(){
        for(int i=0; i<27; i++) delete next[i];
    }

    void insert(const char* key){
        hasNext++;
        if(*key == '\0'){
            isEnd = true;
            return;
        }
        int curr = *key - 'a';

        if(!next[curr]){
            next[curr] = new Trie;
        }
        next[curr]->insert(key+1);
    }
    int search(const char* key){
        if(*key == '?'){
            return hasNext;
        }else{
            int currIdx = *key-'a';
            if(!next[currIdx]) return 0;
            else return next[currIdx]->search(key+1);
        }
    }
};

Trie* sequenceTrie[10001];
Trie* reverseTrie[10001];

void setTrie(vector<string> &words){
    for(auto &word : words){
        if(!sequenceTrie[word.size()]) sequenceTrie[word.size()] = new Trie;
        if(!reverseTrie[word.size()]) reverseTrie[word.size()] = new Trie;

        sequenceTrie[word.size()]->insert(word.c_str());
        reverse(word.begin(), word.end());
        reverseTrie[word.size()]->insert(word.c_str());
    }
}

vector<int> searchQuery(vector<string> queries){
    vector<int> answer;
    for(auto &query : queries){
        int result = 0;
        if(query[0] == '?'){
            reverse(query.begin(), query.end());
            if(!reverseTrie[query.size()]) result = 0;
            else result = reverseTrie[query.size()]->search(query.c_str());
        }else{
            if(!sequenceTrie[query.size()]) result = 0;
            else result = sequenceTrie[query.size()]->search(query.c_str());
        }
        answer.push_back(result);
    }
    return answer;
}

vector<int> solution(vector<string> words, vector<string> queries) {

    setTrie(words);

    return searchQuery(queries);
}