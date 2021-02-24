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