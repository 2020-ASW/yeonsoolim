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