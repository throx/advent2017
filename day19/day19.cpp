#include <iostream>
#include <string>
#include <map>
#include <set>
#include "../shared/Point.h"

using namespace std;

int main()
{
    map<Point2, char> m;

    string s;
    int y = 0;
    Point2 pos;
    while (getline(cin, s)) {
        for (int x = 0; x < s.length(); ++x) {
            if (s[x] != ' ') {
                m[{x, y}] = s[x];
                if (y == 0) {
                    pos = { x, y };
                }
            }
        }
        ++y;
    }

    set<Point2> been;
    string letters;
    int step = 1;

    while (true) {
        cout << step << ": " << pos << " = " << m[pos] << endl;

        // Check for a letter
        if (isalpha(m[pos])) {
            letters.push_back(m[pos]);
        }

        Point2 next;
        pos.DoSquareNeighbours([&](auto n) {
            if (m.find(n) == m.end()) return;

            // Same row, check '-'
            if (m[pos] != '|' && n[1] == pos[1]) {
                if (m[n] != '|') {
                    if (been.find(n) != been.end()) return;
                    next = n;
                    return;
                }

                // It's a '|' - check one more.
                Point2 jump = n + n - pos;
                if (been.find(jump) != been.end()) return;
                if (m.find(jump) == m.end()) return;
                if (m[jump] == '|') return;
                next = jump;
                return;
            }

            // Must be same column
            if (m[pos] == '-') return;
            if (m[n] != '-') {
                if (been.find(n) != been.end()) return;
                next = n;
                return;
            }

            // It's a '-' - check one more.
            Point2 jump = n + n - pos;
            if (been.find(jump) != been.end()) return;
            if (m.find(jump) == m.end()) return;
            if (m[jump] == '-') return;
            next = jump;
            return;
            });

        if (next == Point2()) {
            break;
        }

        been.insert(pos);
        step += Dist(pos, next);
        pos = next;
    }


    cout << "Part 1: " << letters << endl;
    cout << "Part 2: " << step << endl;
}