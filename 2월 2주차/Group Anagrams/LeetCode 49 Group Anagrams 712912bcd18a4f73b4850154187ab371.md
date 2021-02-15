# LeetCode 49 Group Anagrams

# Problem

**Given an array of strings strs, group the anagrams together. You can return the answer in any order.**

- Anagram을 만족하는 것들을 순서 상관없이 반환하라.

# Pre

- 문제 중 아래 문장 때문에 오직 1번만 쓰는 줄 알았다.

    ⇒ 비트마스크를 이용하여 한 번씩 체크해주고, 비트마스크를 string으로 바꿔서 해시테이블을 구성한다.

    **X → 여러 번 중복되는 알파벳도 있다.**

> An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, **typically using all the original letters exactly once.**

```cpp
void makeBitsetKey(string str){
	  bitset <26> bitCheck;
	  for(auto &alphabet : str){
	      bitCheck.set(alphabet-'a');
	  }
	  if(map.find(bitCheck.to_string()) == map.end()){
	      answer.resize(answer.size()+1);
	      answer[kindOfAnagrams].push_back(str);
	      map.insert({bitCheck.to_string(), kindOfAnagrams++});
	  }else{
	      answer[map[bitCheck.to_string()]].push_back(str);
}
```

# Solve

- Anagram에 해당하는 문자열은 알파벳의 종류와 갯수가 같을 것이다.
- 알파벳 구성이 같다면 같은 기준으로 정렬했을 때 같은 결과값을 가질 것이다.
- 
- 정렬을 위해 문자열 하나 하나 정렬해준다.
- 정렬된 문자열끼리 모으기 위해서는 각자의 Index가 필요하다.

    ```cpp
    vector<pair<string,int>> sortAndIndex(vector <string>& strs){
        vector <pair<string,int> > stringID;
        for(int i=0; i<strs.size(); i++){
            vector <char> temp;
            string newStr;
            for(auto &alphabet : strs[i]){
                temp.push_back(alphabet);
            }
            sort(temp.begin(), temp.end());
            for(auto &alphabet : temp){
                newStr+=alphabet;
            }
            stringID.push_back({newStr, i});
        }
        return stringID;
    }
        
    ```

- 모아진 문자열들끼리 모아서 vector를 구성하여 반환한다.

    ```cpp
    vector<vector<string>> makeAnagrams(vector<string>& strs, vector <pair<string,int> > &stringID){
        unordered_map <string, vector<string>> map;
        vector<vector<string>> answers;
        for(auto &pairs : stringID){
            string str = pairs.first;
            int idx = pairs.second;            
            map[str].push_back(strs[idx]);
        }        
        
        for(auto &pairs : map){
            answers.push_back(pairs.second);
        }
        return answers;
    }
    ```

# Code

```cpp
class Solution {
public:

    vector<vector<string>> makeAnagrams(vector<string>& strs, vector <pair<string,int> > &stringID){
        unordered_map <string, vector<string>> map;
        vector<vector<string>> answers;
        for(auto &pairs : stringID){
            string str = pairs.first;
            int idx = pairs.second;            
            map[str].push_back(strs[idx]);
        }        
        
        for(auto &pairs : map){
            answers.push_back(pairs.second);
        }
        return answers;
    }
    
    vector<pair<string,int>> sortAndIndex(vector <string>& strs){
        vector <pair<string,int> > stringID;
        for(int i=0; i<strs.size(); i++){
            vector <char> temp;
            string newStr;
            for(auto &alphabet : strs[i]){
                temp.push_back(alphabet);
            }
            sort(temp.begin(), temp.end());
            for(auto &alphabet : temp){
                newStr+=alphabet;
            }
            stringID.push_back({newStr, i});
        }
        return stringID;
    }
    
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector <pair<string,int> > stringID = sortAndIndex(strs);
        return makeAnagrams(strs, stringID);
    }
};
```