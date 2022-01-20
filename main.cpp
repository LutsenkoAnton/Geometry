#include "geometry.hpp"
#include <iostream>

using namespace std;

signed main() {
    Point a(2, -1, 1);
    Point b(-2, 1, 0);
    Point c(1, -4, -1);
    Point d(4, -5, 1);
    Point s(2, -3, -1);
    // cerr << e + Vector(b, c) << endl;
    auto p1 = Plane(s, a, d);
    auto p2 = Plane(s, b, c);
    cout << angle(p1, p2) << endl;
    return 0;
}