//#include <iostream>
//#include <string>
//#include <bitset>
//#include <algorithm>
//#include <cmath>
//#define ll long long
//using namespace std;
//int N;
//ll answer;
//string str;
//bitset <23> bit;
//void input() {
//	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	cin >> N >> str;
//}
//
//void print(bitset <23> bit) {
//	cout << "\n";
//	for (int i = 0; i < N; i++) {
//		if (bit.test(i)) cout << str[i];
//		else cout << "x";
//	}cout << "\n";
//}
//
//string intToStr(int x) {
//	string result = "";
//
//	while (x > 0) {
//		int end = x % 10;
//		result += '0' + end;
//		x /= 10;
//	}
//	reverse(result.begin(), result.end());
//	return result;
//}
//ll strToInt(string x) {
//	ll result = 0;
//	while (x.size()) {
//		result *= 10;
//		result += x[0]-'0';
//		x = x.substr(1, x.size());
//	}
//	return result;
//}
//void calc(bitset <23> bit) {
//	string equation = "";
//	for (int i = 0; i < N; ) {
//		if (bit.test(i)) {
//			int A = str[i] - '0';
//			int B = str[i + 2] - '0';
//			int C = 0;
//			switch (str[i + 1]) {
//			case '+':
//				C = A + B;
//				break;
//			case '-':
//				C = A - B;
//				break;
//			case '*':
//				C = A * B;
//				break;
//			}
//			if (C < 0) {
//				equation += "-";
//				C = abs(C);
//			}
//			equation += intToStr(C);
//			i += 3;
//		}
//		else {
//			equation += str[i++];
//		}
//	}
//	for (int i = 0; i < equation.size()-1; ) {
//		if (equation[i] == '-' && equation[i + 1] == '-') {
//			equation.erase(i + 1, 1);
//		}
//		else i++;
//	}
//	cout << equation << '\n';
//	ll tempAnswer = 0;
//	if (equation.size() == 1) {
//		answer = (answer > strToInt(equation) ? answer : strToInt(equation));
//	}
//	ll tempResult = 0;
//	ll temp = 0;
//	int cnt = 1;
//	string A="", B="", C="";
//	bool flag = true;
//	for (int i = 0; i < equation.size(); i++) {
//		if (equation[0] == '-') {
//			flag = false;
//			continue;
//		}
//		if (equation[i] != '*' && equation[i] != '+' && equation[i] != '-') {
//			if (!C.size()) A += equation[i];
//			else B += equation[i];
//		}
//		else {
//			if (B.size()) {
//				ll result = 0;
//				switch (C[0]) {
//				case '+':
//					if (flag) result = strToInt(A) + strToInt(B);
//					else result = strToInt(A) - strToInt(B);
//					break;
//				case '-':
//					if (flag) result = strToInt(A) - strToInt(B);
//					else result = strToInt(A) + strToInt(B);
//					break;
//				case '*':
//					result = strToInt(A) * strToInt(B);
//					break;
//				}
//				if(!flag)
//				A = intToStr(result);
//				B = "";
//				C = "";
//			}
//			C = equation[i];
//		}
//	}
//	ll result = 0;
//	switch (C[0]) {
//	case '+':
//		result = strToInt(A) + strToInt(B);
//		break;
//	case '-':
//		result = strToInt(A) - strToInt(B);
//		break;
//	case '*':
//		result = strToInt(A) * strToInt(B);
//		break;
//	}
//	if (!flag) result -= 2 * result;
//	cout << result << '\n';
//	if (answer < result) {
//		answer = result;
//	}
//}
//void search(int curr, bitset <23> bit) {
//
//	if (curr == N+1) {
//		print(bit);
//		calc(bit); cout << '\n';
//		return;
//	}
//	for (int i = curr; i < N+2; i+=2) {
//		if (bit.test(i)) continue;
//		bit.set(i); bit.set(i + 2);
//		search(i, bit);
//		bit.reset(i); bit.reset(i + 2);
//	}
//}
//
//int main() {
//	input();
//	search(0, bit);
//	cout << answer;
//}

#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;
int N;
ll answer = -2147483648;
string str;
bitset <23> bit;
void input() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> str;
}

void print(bitset <23> bit) {
	cout << "\n";
	for (int i = 0; i < N; i++) {
		if (bit.test(i)) cout << str[i];
		else cout << "x";
	}cout << "\n";
}

string intToStr(int x) {
	string result = "";

	while (x > 0) {
		int end = x % 10;
		result += '0' + end;
		x /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}
ll strToInt(string x) {
	ll result = 0;
	while (x.size()) {
		result *= 10;
		result += x[0] - '0';
		x = x.substr(1, x.size());
	}
	return result;
}
ll operateCalc(ll A, ll B, char C) {
	ll result = 0;
	switch (C) {
	case '+':
		result = A + B;
		break;
	case '-':
		result = A - B;
		break;
	case '*':
		result = A * B;
		break;
	}
	return result;
}

void gwalho(vector <string> &equation, bitset <23> bit) {
	for (int i = 0; i < N; ) {
		string C = "";
		if (bit.test(i)) {
			ll A = str[i] - '0';
			ll B = str[i + 2] - '0';
			
			C = to_string(operateCalc(A, B, str[i + 1]));
			i += 3;
		}
		else {
			C += str[i++];
		}
		equation.push_back(C);
	}
}
ll totalCalc(vector<string> &equation) {
	ll A = stoi(equation[0]);
	for (int i = 1; i < equation.size(); i += 2) {
		ll B = stoi(equation[i + 1]);
		string C = equation[i];
		A = operateCalc(A, B, C[0]);
	}
	return A;
}
void calc(bitset <23> bit) {
	vector <string> equation;
	gwalho(equation, bit);
	
	if (equation.size() == 1) answer = (answer < stoi(equation[0]) ? stoi(equation[0]) : answer);
	ll A = totalCalc(equation);
	answer = (answer < A ? A : answer);
}
void search(int curr, bitset <23> bit) {

	if (curr == N + 1) {
		calc(bit);
		return;
	}
	for (int i = curr; i < N + 2; i += 2) {
		if (bit.test(i)) continue;
		bit.set(i); bit.set(i + 2);
		search(i, bit);
		bit.reset(i); bit.reset(i + 2);
	}
}

int main() {
	input();
	search(0, bit);
	cout << answer;
}