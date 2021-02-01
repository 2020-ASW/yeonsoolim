# 11812 K진 트리

# 문제이해

![11812%20K%E1%84%8C%E1%85%B5%E1%86%AB%20%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%20ebbca1faac99462ea605bf67a4b984e8/Untitled.png](11812%20K%E1%84%8C%E1%85%B5%E1%86%AB%20%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%20ebbca1faac99462ea605bf67a4b984e8/Untitled.png)

**K진 트리에서 2 점 사이의 거리를 구하라.**

# Rule

## K진 Tree에서 x Node의 Parent : $( x + K - 2 ) / K$

### K == 1 일 때, 최대 높이 : 10 ^ 15

### K == 2 일 때, 최대 높이 : log(2)(10^15) = ln(10^15) / ln(2) = 49.8xxx

# Pre 1

### root 인 1에 갈 때까지 부모를 거슬러 올라간다.

```cpp
while (a > 1) {
	aCnt++;
	a = (a + K - 2)/K;
}
while(b > 1) {
	bCnt++;
	b = (b + K - 2)/K;
}-
```

# Pre 2

### root 1 보다 전에 만날 수도 있다.

→ map으로 이미 간 곳을 확인해 준다.

```cpp
map.insert({ a,aCnt });
while (a > 1) {
	aCnt++;
	a = (a + K - 2)/K;
	map.insert({a,aCnt});		
}
while(b > 1) {
	bCnt++;
	b = (b + K - 2)/K;
	if (map.find(b) != map.end()) {
		return map[b] + bCnt;
	}
}
```

# Solve

적어도 a는 모든 부모를 타고 올라가야 한다. → 쓸데없는 위로도 간다는 뜻.

LCA와 유사하게 한 칸씩 depth를 맞춰줘야 한다.

```cpp
int distance() {
	int aCnt = 0, bCnt = 0;
    ll a = x, b = y;
	while(a != b) {
		while (a > b) {
			aCnt++;
			a = (a + K - 2) / K;
		}
		while (a < b) {
			bCnt++;
			b = (b + K - 2) / K;
		}
	}
	return aCnt+bCnt;
}
```

# Error

- 자료형 Error

    N, x, y, a, b  ⇒  Node와 관련된 번호는 long long을 이용해주어야 한다.

![11812%20K%E1%84%8C%E1%85%B5%E1%86%AB%20%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%20ebbca1faac99462ea605bf67a4b984e8/Untitled%201.png](11812%20K%E1%84%8C%E1%85%B5%E1%86%AB%20%E1%84%90%E1%85%B3%E1%84%85%E1%85%B5%20ebbca1faac99462ea605bf67a4b984e8/Untitled%201.png)