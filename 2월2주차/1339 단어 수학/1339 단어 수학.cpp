#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
int N;
vector <string> targets;
vector <int> numbers;
bool cmp(const int &a, const int &b){
    return a>b;
}
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; targets.resize(N); numbers.resize(26);
    for(int i=0; i<N; i++){
        cin >> targets[i];
    }
}
void calc(string target){
    int exp = target.size()-1;
    for(auto &alphabet : target){
        numbers[alphabet-'A'] += pow(10, exp);
        exp -= 1;
    }
}
void histPrint(){
    for(int i=0; i<26; i++){
        cout << i<<" : "<<numbers[i]<<'\n';
    }
}
void weightCalc(){
    for(auto &target : targets){
        calc(target);
    }
}
void assignWeight(){
    int answer = 0, cnt = 9;
    sort(numbers.begin(), numbers.end(), cmp);

    for(int number : numbers){
        if(number == 0) break;
        answer += number*(cnt--);
    }
    cout << answer;
}
int main(){
    input();
    weightCalc();
    assignWeight();
}