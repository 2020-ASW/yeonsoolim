#include <string>
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;

void make8kindOfN(unordered_set <int> &items, int cnt, int N){
    string eleven = "1";
    for(int i=0; i<cnt; i++) eleven += "1";
    items.insert(N*stoi(eleven));
}
int solve(int N, int number){
    vector <unordered_set <int>> items(8);
    for(int i=0; i<8; i++){
        items[i].clear();
        make8kindOfN(items[i], i, N);
    }
    for(int i=1; i<8; i++){
        for(int j=0; j<i; j++){
            for(auto &left : items[j]){
                for(auto &right : items[i-j-1]){
                    items[i].insert(left*right);
                    items[i].insert(left+right);
                    items[i].insert(left-right);
                    if(right == 0) continue;
                    items[i].insert(left/right);
                }
            }
        }
        if(items[i].find(number) != items[i].end()){
            return i+1;
        }
    }
    return -1;
}
int solution(int N, int number) {
    if(N==number) return 1;
    else return solve(N, number);
}