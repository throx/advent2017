#include <iostream>
#include <string>
#include "../shared/Split.h"

using namespace std;

string Dance(const vector<string>& s, string d)
{
    int l = d.length();

    for (auto& m : s) {
        switch (m[0]) {
        case 's':
            {
                int n = stoi(m.substr(1));
                rotate(d.begin(), d.begin() + (l - n), d.end());
                break;
            }

        case 'x':
            {
                int d1, d2;
                if (m[2] == '/') {
                    d1 = m[1] - '0';
                    d2 = stoi(m.substr(3));
                }
                else {
                    d1 = 10 + m[2] - '0';
                    d2 = stoi(m.substr(4));
                }
                swap(d[d1], d[d2]);
                break;
            }

        case 'p':
            {
                auto p1 = d.find(m[1]);
                auto p2 = d.find(m[3]);
                swap(d[p1], d[p2]);
                break;
            }
        }
    }

    return d;
}

// Parse the dance into a formula
// 'P' is irrelevant in an even number of moves, because
// the partners just swap back again.
// 'R' can be aggregated to a net rotation
// 'X' can be all added up and applied at the start (modulo rotation),
//     with opposing swaps reversing.

int main()
{
    string s;
    getline(cin, s);
    string d;
    if (s.length() < 80) {
        d = "abcde";
    }
    else {
        d = "abcdefghijklmnop";
    }

    // RESULTS...
    auto m = Split(s);
    cout << "Part 1: " << Dance(m, d) << endl;

    int i = 0;
    vector<string> perms;
    perms.push_back(d);
    while (true) {
        d = Dance(m, d);
        if (d == "abcdefghijklmnop") {
            break;
        }
        perms.push_back(d);
    }

    cout << "Part 2: " << perms[1000000000 % perms.size()] << endl;
}