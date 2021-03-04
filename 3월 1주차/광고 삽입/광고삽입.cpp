#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#define ll long long

using namespace std;
int maxPlayTimeS, advRange;
vector <ll> prefixSum;
vector <int> histograms;
vector <string> stringSplit(string str, char delim){
    vector <string> answer;
    stringstream ss(str);
    string temp;
    while(getline(ss, temp, delim)){
        answer.push_back(temp);
    }
    return answer;
}
int strToInt(string time){
    // xx:yy:zz
    vector <string> _hms;
    _hms = stringSplit(time, ':');
    int h = stoi(_hms[0]);
    int m = stoi(_hms[1]);
    int s = stoi(_hms[2]);
    return h*3600+m*60+s;
}
string intToStr(int time){
    int _h, _m, _s;
    string answer, h, m, s;
    _h = time/3600;
    time %= 3600;
    _m = time/60;
    time %=60;
    _s = time;
    h = to_string(_h);
    m = to_string(_m);
    s = to_string(_s);
    if(h.size()==1) answer += "0";
    answer += h+":";
    if(m.size()==1) answer+= "0";
    answer += m+":";
    if(s.size()==1) answer+="0";
    answer += s;
    return answer;
}
void init(string play_time, string adv_time, vector<string> logs){
    maxPlayTimeS = strToInt(play_time);
    advRange = strToInt(adv_time);

    histograms.resize(maxPlayTimeS+1);
    prefixSum.resize(maxPlayTimeS+1);
}

void logAnalasis(vector<string> logs){
    for(auto &log : logs){
        string startTime, endTime;
        vector <string> splited = stringSplit(log, '-');
        startTime = splited[0];
        endTime = splited[1];
        int logS = strToInt(startTime);
        int logE = strToInt(endTime);
        for(int i=logS+1; i<=logE; i++){
            histograms[i]++;
        }
    }
}
void setPrefixSum(){
    prefixSum[0] = histograms[0];
    for(int i=1; i<=maxPlayTimeS; i++){
        prefixSum[i] = prefixSum[i-1]+(ll)histograms[i];
    }
}
string searchFixRange(){
    ll answerSum = prefixSum[advRange];
    int answerIdx = 0;
    for(int left=1; left<=maxPlayTimeS - advRange; left++){
        int right = left+advRange;
        ll sum = prefixSum[right]-prefixSum[left];
        if(answerSum < sum){
            answerSum = sum;
            answerIdx = left;
        }
    }
    return intToStr(answerIdx);
}
string solution(string play_time, string adv_time, vector<string> logs) {
    if(play_time == adv_time) return "00:00:00";
    init(play_time, adv_time, logs);
    logAnalasis(logs);
    setPrefixSum();
    return searchFixRange();

}