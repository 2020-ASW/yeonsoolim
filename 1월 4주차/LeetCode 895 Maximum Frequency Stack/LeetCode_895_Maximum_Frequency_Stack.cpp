#include <iostream>
#include <unordered_map>
#include <stack>

class FreqStack {
public:
    int global;
    unordered_map <int, int> elemCountMap;
    unordered_map <int, stack<int> > countStackMap;
    FreqStack() {

    }

    void push(int x) {
        int xCnt = ++elemCountMap[x];
        global = (global < xCnt ? xCnt : global);
        countStackMap[xCnt].push(x);
    }

    int pop() {
        int element = countStackMap[global].top(); countStackMap[global].pop();
        if (countStackMap[global].size() == 0) global--;
        elemCountMap[element]--;
        return element;
    }
};