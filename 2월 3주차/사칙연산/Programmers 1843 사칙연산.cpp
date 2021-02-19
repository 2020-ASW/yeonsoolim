//#include <vector>
//#include <string>
//#include <algorithm>
//#include <iostream>
//using namespace std;
//
//int dp[101][101][2];
//void init(vector<string>& arr) {
//    for (int i = 0; i < 101; i++) {
//        for (int j = 0; j < 101; j++) {
//            dp[i][j][1] = -100000;
//            dp[i][j][0] = 100000;
//        }
//    }
//    for (int i = 0; i < arr.size() / 2 + 1; i++) dp[i][i][0] = dp[i][i][1] = stoi(arr[i * 2]);
//}
//void DP(vector<string>& arr) {
//    for (int pos = 1; pos < arr.size() / 2 + 1; pos++) {  //����
//        for (int left = 0; left < arr.size() / 2 + 1 - pos; left++) {
//            int right = left + pos;
//            for (int k = left; k < right; k++) {
//                if (arr[k * 2 + 1] == "+") {
//                    // + �϶�  �ִ� : �ִ� + �ִ�  �ּ� : �ּ� + �ּ�
//                    dp[left][right][1] = max(dp[left][k][1] + dp[k + 1][right][1], dp[left][right][1]);
//                    dp[left][right][0] = min(dp[left][k][0] + dp[k + 1][right][0], dp[left][right][0]);
//
//                }
//                else {
//                    // - �϶�  �ִ� : �ִ� - �ּ�  �ּ� : �ּ� - �ִ�
//                    dp[left][right][1] = max(dp[left][k][1] - dp[k + 1][right][0], dp[left][right][1]);
//                    dp[left][right][0] = min(dp[left][k][0] - dp[k + 1][right][1], dp[left][right][0]);
//
//                }
//            }
//        }
//    }
//}
//int solution(vector<string> arr)
//{
//
//    init(arr);
//    DP(arr);
//
//    return dp[0][arr.size() / 2][1];
//}

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#define MAXNUM 102
using namespace std;

int minDP[MAXNUM][MAXNUM];
int maxDP[MAXNUM][MAXNUM];
int numSize, opSize;
void init(vector<string> &arr){
    numSize = (int)arr.size()/2 +1;
    opSize = arr.size() - numSize;

    for(int i=1; i<MAXNUM; i++){
        for(int j=1; j<MAXNUM; j++){
            minDP[i][j] = 10000;
            maxDP[i][j] = -10000;
        }
    }
}

void setDP(vector<string> &arr){
    for(int cnt=1, i=0; i<arr.size(); i+=2,cnt++){
        minDP[cnt][cnt] = stoi(arr[i]);
        maxDP[cnt][cnt] = stoi(arr[i]);
    }
}

void search(vector<string> &arr){

    for(int pos = 1; pos<numSize; pos++){
        for(int left= 1; left<numSize-pos+1; left++){
            int right = left + pos;
            for(int k=left; k<right; k++){
                if(arr[(k-1)*2+1] == "+"){
                    minDP[left][right] = min(minDP[left][right], minDP[left][k] + minDP[k+1][right]);
                    maxDP[left][right] = max(maxDP[left][right], maxDP[left][k] + maxDP[k+1][right]);
                }else{
                    minDP[left][right] = min(minDP[left][right], minDP[left][k] - maxDP[k+1][right]);
                    maxDP[left][right] = max(maxDP[left][right], maxDP[left][k] - minDP[k+1][right]);
                }
            }

        }
    }

}

int solution(vector<string> arr)
{
    init(arr);

    setDP(arr);

    search(arr);

    return maxDP[1][numSize];
}