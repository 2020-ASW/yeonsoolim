# LeetCode Longest Repeating Character Replacement

# Problem

Given a string `s` that consists of only uppercase English letters, you can perform at most `k` operations on that string.

In one operation, you can choose **any** character of the string and change it to any other uppercase English character.

Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.

```
Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
```

# Solve

![LeetCode%20Longest%20Repeating%20Character%20Replacement%20ab415197c77a4c89a3efe1a2f9f9dcce/Untitled.png](LeetCode%20Longest%20Repeating%20Character%20Replacement%20ab415197c77a4c89a3efe1a2f9f9dcce/Untitled.png)

1. left, right 포인터를 이용하여 한 문자열씩 보면서 진행.
2. 치환 가능할 때는 치환 하는게 이득.

```cpp
int getMaxHist(vector<int>hist){
    int mx = 0;
    int mxIdx = 0;
    for(int i=0; i<hist.size(); i++){
        if(mx<hist[i]){
            mx = hist[i];
            mxIdx = i;
        }
    }
    return mxIdx;
}

int left = 0, right = 0, answer = 0;
        
while(right<s.size()){

    hist[s[right] - 'A']++;
    int histChar = getMaxHist(hist);
    int histCnt = hist[histChar];
    
    if(right-left+1-histCnt > k){
        hist[s[left]-'A']--;
        left++;
    }
    answer = max(answer, right-left+1);
    right++;

}
```

# Code

```cpp
class Solution {
public:
    int getMaxHist(vector<int>hist){
        int mx = 0;
        int mxIdx = 0;
        for(int i=0; i<hist.size(); i++){
            if(mx<hist[i]){
                mx = hist[i];
                mxIdx = i;
            }
        }
        return mxIdx;
    }
    
    int characterReplacement(string s, int k) {
        vector <int> hist(26,0);
        
        int left = 0, right = 0, answer = 0;
        
        while(right<s.size()){
   
            cout << "left : "<<left<<" "<<"right : "<<right<<'\n';
            hist[s[right] - 'A']++;
            int histChar = getMaxHist(hist);
            int histCnt = hist[histChar];
            
            if(right-left+1-histCnt > k){
                hist[s[left]-'A']--;
                left++;
            }
            answer = max(answer, right-left+1);
            right++;

        }
        return answer;
        
    }
};
```