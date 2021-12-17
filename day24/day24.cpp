#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <set>

using namespace std;

const regex INPUT_R("(\\d+)/(\\d+)");

typedef map<int, set<int>> Components;

int BestBridge(const Components& c, int start) {
    auto it = c.find(start);
    if (it == c.end()) {
        return 0;
    }
    int best = 0;
    for (auto next : it->second) {
        Components newc = c;
        newc[start].erase(next);
        if (next != start) {
            newc[next].erase(start);
        }
        best = max(best, start + next + BestBridge(newc, next));
    }

    return best;
}

struct LB {
    int length;
    int strength;
};

LB LongestBridge(const Components& c, int start) {
    auto it = c.find(start);
    if (it == c.end()) {
        return { 0,0 };
    }
    LB best({0,0});
    for (auto next : it->second) {
        Components newc = c;
        newc[start].erase(next);
        if (next != start) {
            newc[next].erase(start);
        }
        LB sub = LongestBridge(newc, next);
        sub.length++;
        sub.strength += (start + next);

        if (sub.length > best.length) {
            best = sub;
        }
        else if (sub.length == best.length) {
            if (sub.strength > best.strength) {
                best = sub;
            }
        }
    }

    return best;
}

int main()
{
    Components c;
    string s;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            int e1 = stoi(sm[1]);
            int e2 = stoi(sm[2]);
            c[e1].insert(e2);
            if (e1 != e2) c[e2].insert(e1);
        }
    }


    // RESULTS...

    cout << "Part 1: " << BestBridge(c, 0) << endl;
    cout << "Part 2: " << LongestBridge(c, 0).strength << endl;
}