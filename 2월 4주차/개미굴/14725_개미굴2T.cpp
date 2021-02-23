#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct Trie{
    Trie* next[1001]{};
    unordered_map <string, int> dictionary;
    bool isEnd;
    Trie(){
        fill(next, next+1001, nullptr);
        dictionary.clear();
        isEnd = false;
    }
    ~Trie(){
        for(auto & i : next) delete i;
    }

    void insert(vector <string> &keys, int idx){
        if(keys[idx] == " "){
            isEnd = true;
            return;
        }

        string currStr = keys[idx];

        if(dictionary.find(currStr) == dictionary.end()){
            dictionary.insert({currStr, dictionary.size()});
            next[dictionary.find(currStr)->second] = new Trie;
        }
        next[dictionary.find(currStr)->second]->insert(keys, idx+1);
    }
    void preorder(int depth){
        vector <string> words;
        for(auto &key : dictionary) words.push_back(key.first);
        sort(words.begin(), words.end());
        for(auto &word : words){
            for(int _=0; _<depth*2; _++) cout << "-";
            cout << word<<'\n';
            next[dictionary.find(word)->second]->preorder(depth+1);
        }
    }
};
Trie* root = new Trie;
vector <vector<string> > orders;
int N, temp;
string query;

void input(){
    ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> temp; orders.resize(N);
        for(int j=0; j<temp; j++){
            cin >> query;
            orders[i].push_back(query);
        }
        orders[i].push_back(" ");
        root->insert(orders[i], 0);
    }
}

int main(){
    input();
    root->preorder(0);
}