#include <iostream>
#include <unordered_map>

class Solution {
public:
    int answer = 0;
    unordered_map <int, int> map;

    void swapMap(vector<int>& row, int left, int right) {
        int temp = map[row[left]];
        map[row[left]] = map[row[right]];
        map[row[right]] = temp;
    }

    void swap(vector<int>& row, int left, int right) {
        int temp = row[left];
        row[left] = row[right];
        row[right] = temp;
    }

    void setMap(vector<int>& row) {
        for (int i = 0; i < row.size(); i++) {
            map[row[i]] = i;
        }
    }

    int minSwapsCouples(vector<int>& row) {

        setMap(row);

        for (int i = 0; i < row.size() - 1; i += 2) {
            int nextIdx;
            if (row[i] % 2 == 0) {
                if (row[i + 1] == row[i] + 1) continue;
                nextIdx = map[row[i] + 1];
            }
            else {
                if (row[i + 1] == row[i] - 1) continue;
                nextIdx = map[row[i] - 1];
            }
            swap(row, i + 1, nextIdx);
            swapMap(row, i + 1, nextIdx);
            answer += 1;
        }

        return answer;
    }
};