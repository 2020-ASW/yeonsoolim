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