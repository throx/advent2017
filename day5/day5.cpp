#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> jumps;

    while (!cin.eof()) {
        string s;
        cin >> s;

        jumps.push_back(stoi(s));
    }

    vector<int> jumps2 = jumps;

    int part1 = 0;
    int pos = 0;
    while (pos >= 0 && pos < jumps.size()) {
        int oldpos = pos;
        pos += jumps[pos];
        ++part1;
        ++jumps[oldpos];
    }

    int part2 = 0;
    pos = 0;
    jumps = jumps2;

    while (pos >= 0 && pos < jumps.size()) {
        int oldpos = pos;
        pos += jumps[pos];
        ++part2;
        jumps[oldpos] > 2 ? --jumps[oldpos] : ++jumps[oldpos];
    }

    // RESULTS...

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}