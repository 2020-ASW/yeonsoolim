# SWEA 11112 셀로판지

#원의 방정식  # 방정식  # 범위

# 문제

![SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled.png](SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled.png)

# 경우의 수

![SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%201.png](SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%201.png)

![SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%202.png](SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%202.png)

1. **사각형 : 4꼭짓점이 가장 원 밖으로 나가기 쉬울 것이다.**

    **꼭짓점의 좌표**

    ```cpp
    Coord leftTop = {a, d};
    Coord leftBottom = {a, b};
    Coord rightTop = {c, d};
    Coord rightBottom = {c, b};
    ```

**2. 원 : x == p,  y == q 일 때 가장 네모 밖으로 나가기 쉬울 것이다.**

**4 방향의 좌표**

```cpp
Coord left =  { p-r , q};
Coord right =  { p+r , q};
Coord top =  {p, q+r };
Coord bottom =  {p, q-r };
```

**3. 범위를 벗어난다면 각 색깔의 영역이 존재.**

```cpp
if(!checkRectInner(p,q,r,leftTop)) BLUE=true;
if(!checkRectInner(p,q,r,leftBottom)) BLUE=true;
if(!checkRectInner(p,q,r,rightTop)) BLUE=true;
if(!checkRectInner(p,q,r,rightBottom)) BLUE=true;

if(!checkCircleInner(a,b,c,d,left)) RED = true;
if(!checkCircleInner(a,b,c,d,right)) RED = true;            
if(!checkCircleInner(a,b,c,d,top)) RED = true;
if(!checkCircleInner(a,b,c,d,bottom)) RED = true;
```

# Error

x == p,  y == q 가 아니라  각각 0으로 생각했다.

# Code

```cpp
#include<iostream>
#include <cmath>

using namespace std;
struct Coord{
    int x;
    int y;
};

bool checkRectInner(int p, int q, int r, Coord point){
 	return ((pow( (point.x - p), 2) + pow( (point.y - q), 2) - pow(r,2) ) <= 0);
}
bool checkCircleInner(int a, int b, int c, int d, Coord point){
 	return (a <= point.x && point.x <= c && b <= point.y && point.y <= d);
}
int main(int argc, char** argv)
{
	int test_case;
    int T, p, q, r, a, b, c, d;
	bool RED, BLUE;
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case){
		RED = BLUE = false; a = b = c = d = 0; p = q = r = 0;
        cin >> p >> q >> r;
        cin >> a >> b >> c >> d;
		Coord leftTop = {a, d};
        Coord leftBottom = {a, b};
        Coord rightTop = {c, d};
        Coord rightBottom = {c, b};
        //Coord left = {a, (d-b)/2+b};
        //Coord right = {c, (d-b)/2+b};
        //Coord top = {(c-a)/2+a, d};
        //Coord bottom = {(c-a)/2+a, b};
        //Coord left =  {(double)(2*p - sqrt(-4*pow(q,2) + 4*pow(r,2)) ) / 2 , 0};
        //Coord right =  {(double)(2*p + sqrt(-4*pow(q,2) + 4*pow(r,2)) ) / 2 , 0};
        //Coord top =  {0, (double)(2*q + sqrt(-4*pow(p,2) + 4*pow(r,2)) ) / 2};
        //Coord bottom =  {0, (double)(2*q - sqrt(-4*pow(p,2) + 4*pow(r,2)) ) / 2};
        Coord left =  { p-r , q};
        Coord right =  { p+r , q};
        Coord top =  {p, q+r };
        Coord bottom =  {p, q-r };
        if(!checkRectInner(p,q,r,leftTop)) BLUE=true;
        if(!checkRectInner(p,q,r,leftBottom)) BLUE=true;
        if(!checkRectInner(p,q,r,rightTop)) BLUE=true;
        if(!checkRectInner(p,q,r,rightBottom)) BLUE=true;
        
        if(!checkCircleInner(a,b,c,d,left)) RED = true;
        if(!checkCircleInner(a,b,c,d,right)) RED = true;            
        if(!checkCircleInner(a,b,c,d,top)) RED = true;
        if(!checkCircleInner(a,b,c,d,bottom)) RED = true;
            
		cout << "#"<<test_case<<' '<<(RED ? "Y" : "N")<<(BLUE ? "Y" : "N")<<'\n';
	}
	return 0;
}
```

![SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%203.png](SWEA%2011112%20%E1%84%89%E1%85%A6%E1%86%AF%E1%84%85%E1%85%A9%E1%84%91%E1%85%A1%E1%86%AB%E1%84%8C%E1%85%B5%202963acdd867f4848b68eeb437c871142/Untitled%203.png)