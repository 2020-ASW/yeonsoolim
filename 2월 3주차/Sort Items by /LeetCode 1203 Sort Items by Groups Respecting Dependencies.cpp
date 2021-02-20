class Solution {
private:
    int N;
    int M;
    int extendM;
    vector <unordered_set<int> > groupInfo;
    vector <unordered_set<int> > itemInfo;
    vector <int> indegree;
public:

    void init(int &n, int &m, vector<int>& group, vector<vector<int>>& beforeItems){
        this->N = n;
        this->M = m;
        this->extendM = m;
        itemInfo.resize(n);
        groupInfo.resize(m);
        for(int item=0; item<n; item++){
            if(group[item] == -1){
                groupInfo.resize(extendM+1);
                group[item] = extendM++;
            }
        }

        for(int item=0; item<n; item++){
            for(auto &before : beforeItems[item]){
                itemInfo[before].insert(item);
                if(group[item] != group[before]){

                    groupInfo[group[before]].insert(group[item]);
                }
            }
        }
    }

    void tpSort(vector <int> &sorted, vector <unordered_set<int> > &info){
        indegree.clear();
        indegree.resize(info.size());

        for(auto &i : info){
            for(auto iter=i.begin(); iter!=i.end(); ++iter){
                indegree[*iter]++;
            }
        }

        queue <int> q;
        for(int i=0; i<info.size(); i++){
            if(indegree[i] == 0) q.push(i);
        }

        while(!q.empty()){
            int curr = q.front(); q.pop();
            sorted.push_back(curr);
            for(auto &next : info[curr]){
                indegree[next] -= 1;
                if(indegree[next] == 0) q.push(next);
            }
        }
    }


    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        init(n, m, group, beforeItems);

        vector <int> sortedItem;
        vector <int> sortedGroup;
        vector<int> answer;

        tpSort(sortedItem, itemInfo);
        if(sortedItem.size() != N) return answer;
        tpSort(sortedGroup, groupInfo);
        if(sortedGroup.size() != extendM) return answer;


        vector <vector<int> > v(sortedGroup.size());

        for(auto &item: sortedItem){
            v[group[item]].push_back(item);
        }

        for(auto &group : sortedGroup){
            for(auto iter= v[group].begin(); iter!=v[group].end(); ++iter){
                answer.push_back(*iter);
            }
        }

        return answer;
    }
};