#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Banks;
typedef map<Banks, int> History;

void Dump(const Banks& b)
{
    for (auto& i : b) {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    string s;
    Banks b;
    getline(cin, s);
    istringstream iss(s);
    string n;

    while (getline(iss, n, ' ')) {
        b.push_back(stoi(n));
    }

    History h;
    int part1 = 0;

    while (h.find(b) == h.end()) {
        h.insert({ b, part1 });
        ++part1;

        auto it = max_element(b.begin(), b.end());
        int pos = it - b.begin();
        int n = b[pos];
        b[pos] = 0;

        while (n > 0) {
            ++pos;
            if (pos == b.size()) pos = 0;
            ++b[pos];
            --n;
        }
    }
    // RESULTS...

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << (part1 - h[b]) << endl;
}