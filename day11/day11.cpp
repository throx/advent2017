#include <iostream>
#include <string>
#include "../shared/HexPoint.h"
#include "../shared/Split.h"

using namespace std;

int main()
{
    while (!cin.eof()) {
        string s;
        cin >> s;

        HexPoint pos;
        int part2 = 0;
        for (auto& dir : Split(s)) {
            pos += HP::DIRS[dir];

            int d = HexDist(pos, HexPoint());
            part2 = max(d, part2);
        }

        cout << "Part 1: " << HexDist(pos, HexPoint()) << endl;
        cout << "Part 2: " << part2 << endl << endl;
    }
}