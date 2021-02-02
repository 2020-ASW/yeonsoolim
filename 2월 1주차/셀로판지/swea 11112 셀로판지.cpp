#include<iostream>
#include <cmath>

using namespace std;
struct Coord {
    int x;
    int y;
};

bool checkRectInner(int p, int q, int r, Coord point) {
    return ((pow((point.x - p), 2) + pow((point.y - q), 2) - pow(r, 2)) <= 0);
}
bool checkCircleInner(int a, int b, int c, int d, Coord point) {
    return (a <= point.x && point.x <= c && b <= point.y && point.y <= d);
}
int main(int argc, char** argv)
{
    int test_case;
    int T, p, q, r, a, b, c, d;
    bool RED, BLUE;
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        RED = BLUE = false; a = b = c = d = 0; p = q = r = 0;
        cin >> p >> q >> r;
        cin >> a >> b >> c >> d;
        Coord leftTop = { a, d };
        Coord leftBottom = { a, b };
        Coord rightTop = { c, d };
        Coord rightBottom = { c, b };
        //Coord left = {a, (d-b)/2+b};
        //Coord right = {c, (d-b)/2+b};
        //Coord top = {(c-a)/2+a, d};
        //Coord bottom = {(c-a)/2+a, b};
        //Coord left =  {(double)(2*p - sqrt(-4*pow(q,2) + 4*pow(r,2)) ) / 2 , 0};
        //Coord right =  {(double)(2*p + sqrt(-4*pow(q,2) + 4*pow(r,2)) ) / 2 , 0};
        //Coord top =  {0, (double)(2*q + sqrt(-4*pow(p,2) + 4*pow(r,2)) ) / 2};
        //Coord bottom =  {0, (double)(2*q - sqrt(-4*pow(p,2) + 4*pow(r,2)) ) / 2};
        Coord left = { p - r , q };
        Coord right = { p + r , q };
        Coord top = { p, q + r };
        Coord bottom = { p, q - r };
        if (!checkRectInner(p, q, r, leftTop)) BLUE = true;
        if (!checkRectInner(p, q, r, leftBottom)) BLUE = true;
        if (!checkRectInner(p, q, r, rightTop)) BLUE = true;
        if (!checkRectInner(p, q, r, rightBottom)) BLUE = true;

        if (!checkCircleInner(a, b, c, d, left)) RED = true;
        if (!checkCircleInner(a, b, c, d, right)) RED = true;
        if (!checkCircleInner(a, b, c, d, top)) RED = true;
        if (!checkCircleInner(a, b, c, d, bottom)) RED = true;

        cout << "#" << test_case << ' ' << (RED ? "Y" : "N") << (BLUE ? "Y" : "N") << '\n';
    }
    return 0;
}