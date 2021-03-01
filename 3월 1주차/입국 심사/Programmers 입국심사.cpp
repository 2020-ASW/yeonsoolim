#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define ll long long
using namespace std;
ll getMaxtime(int n, vector<int> &times){
    int cycle = n/times.size();
    return (ll)cycle*(*max_element(times.begin(), times.end()));
    //return (ll)n*(ll)(*max_element(times.begin(), times.end()));
}
bool check(ll mid, int n, vector<int> &times){
    // n명의 사람을 mid 분 만에 처리 가능한가.
    //int lb = lower_bound(times.begin(), times.end(), mid) - times.begin();
    ll ub = upper_bound(times.begin(), times.end(), mid) - times.begin();

    ll total = 0;
    for(ll i= 0; i < times.size(); i++){
        total += mid/(ll)times[i];
    }
    return total>=n;
}
ll binarySearch(int n, vector<int> &times){
    ll MAXTIME = getMaxtime(n, times);

    ll left = 1, right = MAXTIME, answer = 0;
    while(left <=right){
        ll mid = (right-left)/2 + left;

        if(check(mid, n, times)){
            right= mid-1;
            answer = mid;
        }else{
            left = mid+1;
        }
    }
    return answer;
}

long long solution(int n, vector<int> times) {

    //sort(times.begin(), times.end());
    ll answer = binarySearch(n, times);

    return answer;
}