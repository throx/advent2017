#include <iostream>
#include <string>
#include "../shared/Split.h"

using namespace std;

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
    for (auto& m : Split(s)) {
        switch (m[0]) {
        case 's':
            {
                int n = stoi(m.substr(1));
                rotate(d.begin(), d.begin() + (d.length() - n), d.end());
                break;
            }

        case 'x':
            {
                auto x = SplitInt(m.substr(1), '/');
                swap(d[x[0]], d[x[1]]);
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

    // RESULTS...

    cout << "Part 1: " << d << endl;
    cout << "Part 2: " << 0 << endl;
}