#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int N;
vector <int> potion;
void input(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; potion.resize(N);
    for(int i=0; i<N; i++){
        cin >> potion[i];
    }
}
void search(){
    int answer = 2147483647;
    int ansL, ansM, ansR;
    for(int left = 0; left<N-2; left++){
        int mid = left+1, right= N-1;

        while(mid < right){
            int sum = potion[left] + potion[mid] + potion[right];
            if( abs(sum) < answer){
                answer = abs(sum);
                ansL = potion[left];
                ansR = potion[right];
                ansM = potion[mid];
            }

            if(sum < 0){
                mid++;
            }else if(sum == 0){
                cout << ansL <<' '<<ansM<<' '<<ansR;
                exit(0);
            }else{
                right--;
            }
        }
    }
    cout << ansL <<' '<<ansM<<' '<<ansR;
}
int main(){
    input();
    sort(potion.begin(), potion.end());
    search();
}