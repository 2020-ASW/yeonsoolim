# 기둥과 보 설치

---

# **문제 설명**

빙하가 깨지면서 스노우타운에 떠내려 온 **죠르디**는 인생 2막을 위해 주택 건축사업에 뛰어들기로 결심하였습니다. 죠르디는 **기둥과 보**를 이용하여 벽면 구조물을 자동으로 세우는 로봇을 개발할 계획인데, 그에 앞서 로봇의 동작을 시뮬레이션 할 수 있는 프로그램을 만들고 있습니다.프로그램은 **2차원 가상 벽면**에 기둥과 보를 이용한 구조물을 설치할 수 있는데, 기둥과 보는 **길이가 1인 선분**으로 표현되며 다음과 같은 규칙을 가지고 있습니다.

- 기둥은 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위에 있어야 합니다.
- 보는 한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.

단, 바닥은 벽면의 맨 아래 지면을 말합니다.

2차원 벽면은 **`n x n`** 크기 정사각 격자 형태이며, 각 격자는 **`1 x 1`** 크기입니다. 맨 처음 벽면은 비어있는 상태입니다. 기둥과 보는 격자선의 교차점에 걸치지 않고, 격자 칸의 각 변에 정확히 일치하도록 설치할 수 있습니다. 다음은 기둥과 보를 설치해 구조물을 만든 예시입니다.

![%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled.png](%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled.png)

예를 들어, 위 그림은 다음 순서에 따라 구조물을 만들었습니다.

1. (1, 0)에서 위쪽으로 기둥을 하나 설치 후, (1, 1)에서 오른쪽으로 보를 하나 만듭니다.
2. (2, 1)에서 위쪽으로 기둥을 하나 설치 후, (2, 2)에서 오른쪽으로 보를 하나 만듭니다.
3. (5, 0)에서 위쪽으로 기둥을 하나 설치 후, (5, 1)에서 위쪽으로 기둥을 하나 더 설치합니다.
4. (4, 2)에서 오른쪽으로 보를 설치 후, (3, 2)에서 오른쪽으로 보를 설치합니다.

만약 (4, 2)에서 오른쪽으로 보를 먼저 설치하지 않고, (3, 2)에서 오른쪽으로 보를 설치하려 한다면 2번 규칙에 맞지 않으므로 설치가 되지 않습니다. 기둥과 보를 삭제하는 기능도 있는데 기둥과 보를 삭제한 후에 남은 기둥과 보들 또한 위 규칙을 만족해야 합니다. 만약, 작업을 수행한 결과가 조건을 만족하지 않는다면 해당 작업은 무시됩니다.

벽면의 크기 n, 기둥과 보를 설치하거나 삭제하는 작업이 순서대로 담긴 2차원 배열 build_frame이 매개변수로 주어질 때, 모든 명령어를 수행한 후 구조물의 상태를 return 하도록 solution 함수를 완성해주세요.

### **제한사항**

- n은 5 이상 100 이하인 자연수입니다.
- build_frame의 세로(행) 길이는 1 이상 1,000 이하입니다.
- build_frame의 가로(열) 길이는 4입니다.
- build_frame의 원소는 [x, y, a, b]형태입니다.
    - x, y는 기둥, 보를 설치 또는 삭제할 교차점의 좌표이며, [가로 좌표, 세로 좌표] 형태입니다.
    - a는 설치 또는 삭제할 구조물의 종류를 나타내며, 0은 기둥, 1은 보를 나타냅니다.
    - b는 구조물을 설치할 지, 혹은 삭제할 지를 나타내며 0은 삭제, 1은 설치를 나타냅니다.
    - 벽면을 벗어나게 기둥, 보를 설치하는 경우는 없습니다.
    - 바닥에 보를 설치 하는 경우는 없습니다.
- 구조물은 교차점 좌표를 기준으로 보는 오른쪽, 기둥은 위쪽 방향으로 설치 또는 삭제합니다.
- 구조물이 겹치도록 설치하는 경우와, 없는 구조물을 삭제하는 경우는 입력으로 주어지지 않습니다.
- 최종 구조물의 상태는 아래 규칙에 맞춰 return 해주세요.
    - return 하는 배열은 가로(열) 길이가 3인 2차원 배열로, 각 구조물의 좌표를 담고있어야 합니다.
    - return 하는 배열의 원소는 [x, y, a] 형식입니다.
    - x, y는 기둥, 보의 교차점 좌표이며, [가로 좌표, 세로 좌표] 형태입니다.
    - 기둥, 보는 교차점 좌표를 기준으로 오른쪽, 또는 위쪽 방향으로 설치되어 있음을 나타냅니다.
    - a는 구조물의 종류를 나타내며, 0은 기둥, 1은 보를 나타냅니다.
    - return 하는 배열은 x좌표 기준으로 오름차순 정렬하며, x좌표가 같을 경우 y좌표 기준으로 오름차순 정렬해주세요.
    - x, y좌표가 모두 같은 경우 기둥이 보보다 앞에 오면 됩니다.

### **입출력 예**

[Untitled](https://www.notion.so/af7ac33568824d728068c50b110bfd33)

### **입출력 예에 대한 설명**

**입출력 예 #1**

문제의 예시와 같습니다.

**입출력 예 #2**

여덟 번째 작업을 수행 후 아래와 같은 구조물 만들어집니다.

![%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%201.png](%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%201.png)

아홉 번째 작업의 경우, (1, 1)에서 오른쪽에 있는 보를 삭제하면 (2, 1)에서 오른쪽에 있는 보는 조건을 만족하지 않으므로 무시됩니다.

열 번째 작업의 경우, (2, 2)에서 위쪽 방향으로 기둥을 세울 경우 조건을 만족하지 않으므로 무시됩니다.

---

# 문제 풀이

조건만 확인하면 된다.

1. 기둥
    1. 기둥 위
    2. 바닥 위
    3. 보의 한 쪽 끝  ( 왼쪽 or 오른쪽 )
2. 보
    1. 기둥 연결 ( 왼쪽 or 오른쪽 )
    2. 양쪽 보의 사이

```java
bool check(int x, int y, int item){
    if(item == 0){ // 기둥
        if(y == 0) return true;  //바닥 위
        if(y-1 >= 0 && base[y-1][x][0] == 1) return true; // 기둥 위
        if(x-1 >= 0 && base[y][x-1][1] == 1) return true; // 보 한쪽 끝
        if(base[y][x][1] == 1) return true;
        return false;
    }
    if(item == 1){ // 보
        
        if(y-1 >= 0 && base[y-1][x][0] == 1) return true; // 왼쪽 기둥
        if(y-1 >= 0 && x+1 <= SIZE && base[y-1][x+1][0] == 1) return true; // 오른쪽 기둥
        if(x-1 >= 0 && x+1 <= SIZE && base[y][x-1][1] == 1 && base[y][x+1][1] == 1) return true; //양쪽 보
        return false;
    }
}
```

- x-1, x+1, y-1, y+1 에서 배열 범위를 초과할 수 있으므로, && 연산의 성질을 이용하여 먼저 범위 검사를 해준다.  (사실 카카오의 테스트케이스에서 초과하는 것을 주지 않는다고 했다.)
- 기둥을 설치할 수 있는 조건 4가지
- 보를 설치할 수 있는 경우 3가지

### 설치 시

이 조건을 확인 하고 삭제

![%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%202.png](%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%202.png)

### 삭제 시

**일단 지우고**, 연관 된 것들이 지워진 것이 없는 상태로 설치 될 수 있는지를 확인한다.

![%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%203.png](%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%203.png)

```java
void uninstall(int x, int y, int item){
	base[y][x][item] = 0;  // 일단 지운다.
	if(item == 0){  // 기둥을 삭제할 수 있는 경우 3가지
		...
		...
		...
	}
	else{           // 보를 삭제할 수 있는 경우 4가지
		...
		...
		...
		...
	}
```

## 에러

1. 같은 좌표에 기둥 + 보가 존재할 수 있는데, 이를 고려하지 못했다.
2차원 → 3차원  ( x좌표, y좌표,  0 or 1 )
2. 3차원 배열에서  2차원 까지만 bool체크를 하면 주소값이 나오므로 무조건 true다.

```java
if(base[y][x-1][1] && !check(x-1, y, 1)){
    base[y][x][item] = 1;    
    return;  
}    //이건 맞다.

if(base[y][x-1] && !check(x-1, y, 1)){
    base[y][x][item] = 1;    
    return;  
}    // 이건 틀렸다.
```

# 코드 C++

```java
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define 기둥 0
#define 보 1

using namespace std;

int base[101][101][2];
int SIZE;

void print(){
    for(int i=SIZE; i>=0; i--){
        for(int j=0; j<=SIZE; j++){
            int sum = 0;
            sum+=base[i][j][0];
            sum+=base[i][j][1];
            cout << sum <<' ';
        }cout <<'\n';
    }cout <<'\n';
}

vector <vector<int> > makeAnswer(){
    vector <vector<int> > answer;
    for(int x=0; x<=SIZE; x++){
        for(int y=0; y<=SIZE; y++){
            if(base[y][x][0] == 1){
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(0);
                answer.push_back(temp);
            }
            if(base[y][x][1] == 1){
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(1);
                answer.push_back(temp);
            }
        }
    }
    if(answer.size() == 0){
        vector<int> temp;
        answer.push_back(temp);
    }else{
        for(auto &a: answer){
            cout << a[0]<<' '<<a[1]<<' '<<a[2]<<'\n';
        }
    }
    return answer;
}

bool check(int x, int y, int item){
    if(item == 0){ // 기둥
        if(y == 0) return true;  //바닥 위
        if(y-1 >= 0 && base[y-1][x][0] == 1) return true; // 기둥 위
        if(x-1 >= 0 && base[y][x-1][1] == 1) return true; // 보 한쪽 끝
        if(base[y][x][1] == 1) return true;
        return false;
    }
    if(item == 1){ // 보
        
        if(y-1 >= 0 && base[y-1][x][0] == 1) return true; // 왼쪽 기둥
        if(y-1 >= 0 && x+1 <= SIZE && base[y-1][x+1][0] == 1) return true; // 오른쪽 기둥
        if(x-1 >= 0 && x+1 <= SIZE && base[y][x-1][1] == 1 && base[y][x+1][1] == 1) return true; //양쪽 보
        return false;
    }
}
void install(int x, int y, int item){
    if(check(x,y,item)){
        base[y][x][item]=1; 
    }
}
void uninstall(int x, int y, int item){
    base[y][x][item] = 0;
    if(item == 0){ //기둥 삭제 3가지
        if(base[y+1][x][0] && !check(x, y+1, 0)){
            base[y][x][item] = 1;    
            return;  
        } 
        if(base[y+1][x-1][1] && !check(x-1, y+1, 1)){
            base[y][x][item] = 1;    
            return;  
        } 
        if(base[y+1][x][1] && !check(x, y+1, 1)){
            base[y][x][item] = 1;    
            return;  
        }  
    }
    else{ //보 삭제
        if(base[y][x-1][1] && !check(x-1, y, 1)){
            base[y][x][item] = 1;    
            return;  
        }
        if(base[y][x+1][1] && !check(x+1, y, 1)){
            base[y][x][item] = 1;
            return;  
        }
        if(base[y][x][0] && !check(x, y, 0)){
            base[y][x][item] = 1;
            return;  
        }
        if(base[y][x+1][0] && !check(x+1, y, 0)){
            base[y][x][item] = 1;
            return;  
        }
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    SIZE = n;
    vector<vector<int>> answer;
    cout<< base[0][1];
    for(auto pair4 : build_frame){
        int x = pair4[0];
        int y = pair4[1];
        int item = pair4[2];
        int mission = pair4[3];
        if(mission == 1) install(x, y, item);
        else uninstall(x, y, item);    
    }
    print();

    return makeAnswer();
}
```

# Code (JS)

```cpp
var N;
var bo, gi;
const init = (n, build_frame) => {
    N = n;
    bo = new Array(n+1);
    gi = new Array(n+1);
    for(let i=0; i<=n; i++) {
        bo[i] = new Array(n+1);
        gi[i] = new Array(n+1);
        for(let j=0; j<=n; j++){
            bo[i][j] = false;
            gi[i][j] = false;
        }
    }
}

const giCheck = (x, y) => { // :int :int
    if(y === 0) return true;
    if(bo[y][x-1] || bo[y][x]) return true;
    if(gi[y-1][x] ) return true;
    return false;
}
const boCheck = (x, y) => {
    if(gi[y-1][x] || gi[y-1][x+1]) return true;
    if(bo[y][x-1] && bo[y][x+1]) return true;
    return false;
}
const end = () => {
    let answer = [];
    for(let i=0; i<=N; i++){
        for(let j=0; j<=N; j++){
            if(gi[j][i]){
                answer.push([i,j,0]);
            }
            if(bo[j][i]){
                answer.push([i,j,1]);
            }
        }
    }
    return answer;
}
const giRemove = (x, y) => {
    gi[y][x] = false;
    if(bo[y+1][x-1] && !boCheck(x-1,y+1)){
        gi[y][x] = true; return false;
    }
    if(bo[y+1][x] && !boCheck(x, y+1)){
        gi[y][x] = true; return false;
    }
    if(gi[y+1][x] && !giCheck(x,y+1)){
        gi[y][x] = true; return false;
    }
    return true;
}
const boRemove = (x,y) => {
    bo[y][x] = false;
    if(gi[y][x] && !giCheck(x,y)){
        bo[y][x] = true; return false;
    }
    if(gi[y][x+1] && !giCheck(x+1,y)){
        bo[y][x] = true; return false;
    }
    if(bo[y][x-1] && !boCheck(x-1,y)){
        bo[y][x] = true; return false;
    }
    if(bo[y][x+1] && !boCheck(x+1,y)){
        bo[y][x] = true; return false;
    }
    return true;
}
function solution(n, build_frame) { //build_frame => [][]
    init(n, build_frame);
    
    for(let cmd of build_frame){
        let giOrBo = cmd[2];
        let installOrRemove = cmd[3]; 
        let res;
        switch(cmd[2]){
            case 0:
                res = giCheck(cmd[0], cmd[1]);
                if(res && installOrRemove)
                    gi[cmd[1]][cmd[0]] = true;
                else if(res)
                    giRemove(cmd[0],cmd[1]);
                break;
            case 1:
                res = boCheck(cmd[0], cmd[1]);
                if(res && installOrRemove) 
                    bo[cmd[1]][cmd[0]] = true;
                else if(res)
                    boRemove(cmd[0],cmd[1]);
                break;
        }   
    }
    
    let answer = end();
    if(answer.length === 0) return [[]]
    //console.log(answer);
    return answer;
}
```

![%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%204.png](%E1%84%80%E1%85%B5%E1%84%83%E1%85%AE%E1%86%BC%E1%84%80%E1%85%AA%20%E1%84%87%E1%85%A9%20%E1%84%89%E1%85%A5%E1%86%AF%E1%84%8E%E1%85%B5%20f102e41c99aa4f1d8a4c9c7b7a35625f/Untitled%204.png)