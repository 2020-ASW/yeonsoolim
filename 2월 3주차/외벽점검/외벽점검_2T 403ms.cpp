#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

int calcDistance(bool CCW, int &N, vector<int> &weaks, int curr){
    int nextDistance = 0;
    if(!CCW){
        if(weaks[curr+1] < weaks[curr])  // 12 -> 
            nextDistance = weaks[curr+1]+N - weaks[curr];
        else
            nextDistance = weaks[curr+1] -weaks[curr];
    }else{
        if(weaks[curr+1] > weaks[curr])  //  <- 12 
            nextDistance = N - weaks[curr+1] + weaks[curr];
        else
            nextDistance = abs(weaks[curr] - weaks[curr+1]);
    }

    return nextDistance;
}

bool check(bool CCW, int &N, vector<int> &weaks, vector<int> &friends){
    bool success = false;
    int nextDistance = 0;

    int curr = 0;
    int completed = 0;
    int _friend = 0;
    int friendIdx = 0;

    while(1){
        if(_friend <= 0) _friend = friends[friendIdx];
        nextDistance = calcDistance(CCW,N, weaks, curr);

        if(_friend < nextDistance){
            completed += 1;
            curr += 1;
            _friend = 0;
            friendIdx+=1;
        }else if(_friend == nextDistance){
            completed += 2;
            curr += 2;
            _friend = 0;
            friendIdx+=1;
        }else if(_friend > nextDistance){
            completed += 1;
            curr += 1;
            _friend = _friend-nextDistance;
            friendIdx = friendIdx;
        }
        if(completed >= weaks.size()){
            return true;
        }
        if(friendIdx >= friends.size() || curr >= weaks.size()){
            return false;
        }
    }
    if(completed >= weaks.size()) return true;
    else return false;
}

bool assignFriends(bool CCW, int &N, int &numFriends, bitset <8> bits, vector<int> friends, vector<int> &weaks, vector<int> &dist){
    if(bits.count() == numFriends){
        // vector<int> friends;
        // for(int i=0; i<8; i++)
        //     if(bits.test(i)) 
        //         friends.push_back(dist[i]);

        return check(CCW, N, weaks, friends);
    }

    for(int i=0; i<dist.size(); i++){
        if(bits.test(i)) continue;
        bool result = false;
        bits.set(i);
        friends[bits.count()-1] = dist[i];
        result = assignFriends(CCW, N, numFriends, bits, friends, weaks, dist);
        bits.reset(i);
        if(result) return true;
    }
    return false;
}


int solution(int n, vector<int> weak, vector<int> dist) {
    reverse(dist.begin(), dist.end());
    for(int numFriends = 1; numFriends<=dist.size(); numFriends++){
        if(numFriends >= weak.size()) return numFriends;
        //weak의 배열 조작
        for(int pos = 0; pos<weak.size(); pos++){
            vector<int> newWeak;
            bitset <8> bits;
            vector <int> friends(numFriends,0);
            bool result = false;

            // CW
            for(int i=pos; i<weak.size()+pos; i++)
                newWeak.push_back(weak[i%weak.size()]);
            result = assignFriends(false, n, numFriends, bits, friends, newWeak, dist);
            if(result) return numFriends;

            // CCW
            reverse(newWeak.begin(), newWeak.end());
            result = assignFriends(true, n, numFriends, bits, friends, newWeak, dist);
            if(result) return numFriends;
        }
    }

    return -1;
}