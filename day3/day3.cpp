#include <iostream>
#include <string>
#include <map>
#include "../shared/Point.h"

using namespace std;
using namespace P2;

const int INPUT = 277678;

const Point2 DIR[] = { E, N, W, S };

int main()
{
    int n = 1;
    int d = 0;
    Point2 loc;
    map<Point2, int> points;

    while (true) {
        points[loc] = n;
        if (n == INPUT) break;

        loc += DIR[d];
        Point2 next = DIR[(d + 1) % 4];
        if (points.find(loc + next) == points.end()) {
            d = (d + 1) % 4;
        }
        ++n;
    }
    cout << "Part 1: " << Dist(loc, Point2()) << endl;

    points.clear();
    d = 0;
    loc = Point2();
    int sum = 0;

    while (true) {
        if (loc == Point2()) {
            points[loc] = 1;
        }
        else {
            sum = 0;
            loc.DoNeighbours([&](const Point2& p)
                {
                    if (points.find(p) != points.end()) {
                        sum += points[p];
                    }
                });
            points[loc] = sum;
            if (sum > INPUT) break;
        }

        loc += DIR[d];
        Point2 next = DIR[(d + 1) % 4];
        if (points.find(loc + next) == points.end()) {
            d = (d + 1) % 4;
        }
    }

    cout << "Part 2: " << sum << endl;
}