#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;
unordered_map <string, int> token;
//bitset <100001> visit;
//vector <int> duplicate;
unordered_map <int, int> visit;
void setToken(vector<string> gems) {
    for (auto& gem : gems) {
        if (token.find(gem) != token.end()) continue;
        token.insert({ gem, token.size() });
    }
    //duplicate.resize(map.size()+1);
}
vector<int> twoPointer(vector<string> gems) {
    vector <int> answer;
    int left = 0, right = 0;
    // visit.set(map[gems[0]]);
    // duplicate[map[gems[0]]]++;
    visit[token[gems[0]]]++;
    int minimum = 2147483647;
    while (1) {
        if (visit.size() == token.size()) {
            if ((right - left) < minimum) {
                answer.clear();
                answer.push_back(left + 1);
                answer.push_back(right + 1);
                minimum = (right - left);
            }
            visit[token[gems[left]]]--;
            if (visit[token[gems[left]]] == 0)
                visit.erase(token[gems[left]]);
            left++;
        }
        else if (right == gems.size()) break;
        else {
            ++right; if (right >= gems.size())break;
            visit[token[gems[right]]]++;
            // if(visit.si(map[gems[right]]) == false){
            //     visit.set(map[gems[right]]);
            // }
        }
        if (gems.size() - left < token.size()) break;
    }

    return answer;
}
vector<int> solution(vector<string> gems) {
    setToken(gems);
    if (token.size() == 1) {
        vector <int> answer(2, 1);
        return answer;
    }
    return twoPointer(gems);
}