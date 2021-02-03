#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
vector <int> pre;    
vector <vector <ll> > dp;

ll multiply(vector<int> a, vector <int> b){
    return (ll)a[0]*b[1]*a[1];
}
void preExtraction(vector<vector<int>> &matrix){
    for(int i=0; i<matrix.size(); i+=2){
        pre.push_back(matrix[i][0]);
        pre.push_back(matrix[i][1]);
    }
    if(matrix.size() %2 == 0){
        pre.push_back(matrix[matrix.size()-1][1]);
    }
}
int solution(vector<vector<int>> matrix_sizes) {
    int answer = 0;
    preExtraction(matrix_sizes);
    
    dp.resize(pre.size()); for(auto &d : dp) d.resize(pre.size());
    for(int i=0; i<pre.size(); i++){
        for(int j=0; j<pre.size(); j++){
            dp[i][j] = 2147483647;
        }
    }
    //for(int i=0; i<pre.size(); i++) cout <<pre[i]<<' ';
    //cout<<'\n';
    for(int i=0; i<dp.size(); i++) dp[i][i] = 0;
    for(int pos = 1; pos<pre.size(); pos++){
        for(int left=0; left<pre.size()-pos-1; left++){
            int right = left + pos;
            for(int k=left; k<right; k++){
                // cout << left<<' '<<k<<' '<<right<<'\n';
                dp[left][right] = min(dp[left][right], dp[left][k] + dp[k+1][right]+(ll)pre[left]*pre[k+1]*pre[right+1]);
                //cout << dp[left][k]<<' '<<dp[k+1][right]<<' '<<' '<<pre[left]<<' '<<pre[k+1]<<' '<<pre[right+1]<<'\n';
                //cout << "left : "<<left <<" "<<"K : "<<k<<" right : "<<right<<' '<<"total : "<<dp[left][right]<<"\n\n";
            }
            
        }
    }
    
    return dp[0][matrix_sizes.size()-1];
}