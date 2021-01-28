#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define ±âµÕ 0
#define º¸ 1

using namespace std;

int base[101][101][2];
int SIZE;

void print() {
    for (int i = SIZE; i >= 0; i--) {
        for (int j = 0; j <= SIZE; j++) {
            int sum = 0;
            sum += base[i][j][0];
            sum += base[i][j][1];
            cout << sum << ' ';
        }cout << '\n';
    }cout << '\n';
}

vector <vector<int> > makeAnswer() {
    vector <vector<int> > answer;
    for (int x = 0; x <= SIZE; x++) {
        for (int y = 0; y <= SIZE; y++) {
            if (base[y][x][0] == 1) {
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(0);
                answer.push_back(temp);
            }
            if (base[y][x][1] == 1) {
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(1);
                answer.push_back(temp);
            }
        }
    }
    if (answer.size() == 0) {
        vector<int> temp;
        answer.push_back(temp);
    }
    else {
        for (auto& a : answer) {
            cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';
        }
    }
    return answer;
}

bool check(int x, int y, int item) {
    if (item == 0) { // ±âµÕ
        if (y == 0) return true;  //¹Ù´Ú À§
        if (y - 1 >= 0 && base[y - 1][x][0] == 1) return true; // ±âµÕ À§
        if (x - 1 >= 0 && base[y][x - 1][1] == 1) return true; // º¸ ÇÑÂÊ ³¡
        if (base[y][x][1] == 1) return true;
        return false;
    }
    if (item == 1) { // º¸

        if (y - 1 >= 0 && base[y - 1][x][0] == 1) return true; // ¿ÞÂÊ ±âµÕ
        if (y - 1 >= 0 && x + 1 <= SIZE && base[y - 1][x + 1][0] == 1) return true; // ¿À¸¥ÂÊ ±âµÕ
        if (x - 1 >= 0 && x + 1 <= SIZE && base[y][x - 1][1] == 1 && base[y][x + 1][1] == 1) return true; //¾çÂÊ º¸
        return false;
    }
}
void install(int x, int y, int item) {
    if (check(x, y, item)) {
        base[y][x][item] = 1;
    }
}
void uninstall(int x, int y, int item) {
    base[y][x][item] = 0;
    if (item == 0) { //±âµÕ »èÁ¦ 3°¡Áö
        if (base[y + 1][x][0] && !check(x, y + 1, 0)) {
            base[y][x][item] = 1;
            return;
        }
        if (base[y + 1][x - 1][1] && !check(x - 1, y + 1, 1)) {
            base[y][x][item] = 1;
            return;
        }
        if (base[y + 1][x][1] && !check(x, y + 1, 1)) {
            base[y][x][item] = 1;
            return;
        }
    }
    else { //º¸ »èÁ¦
        if (base[y][x - 1][1] && !check(x - 1, y, 1)) {
            base[y][x][item] = 1;
            return;
        }
        if (base[y][x + 1][1] && !check(x + 1, y, 1)) {
            base[y][x][item] = 1;
            return;
        }
        if (base[y][x][0] && !check(x, y, 0)) {
            base[y][x][item] = 1;
            return;
        }
        if (base[y][x + 1][0] && !check(x + 1, y, 0)) {
            base[y][x][item] = 1;
            return;
        }
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    SIZE = n;
    vector<vector<int>> answer;
    cout << base[0][1];
    for (auto pair4 : build_frame) {
        int x = pair4[0];
        int y = pair4[1];
        int item = pair4[2];
        int mission = pair4[3];
        if (mission == 1) install(x, y, item);
        else uninstall(x, y, item);
    }
    print();

    return makeAnswer();
}