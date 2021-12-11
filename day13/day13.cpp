#include <iostream>
#include <string>
#include <vector>
#include "../shared/Split.h"

using namespace std;

struct Scanner {
    int depth;
    int width;
};

int main()
{
    vector<Scanner> scanners;
    while (!cin.eof()) {
        string s;
        getline(cin, s);

        auto v = SplitInt(s, ':');
        Scanner scan({v[0], v[1]});
        scanners.push_back(scan);
    }

    int part1 = 0;
    for (auto& scan : scanners) {
        int period = (scan.width - 1) * 2;
        if (scan.depth % period == 0) {
            part1 += scan.width * scan.depth;
        }
    }

    int part2 = 0;
    while (true) {
        if (none_of(scanners.begin(), scanners.end(), [&](Scanner& scan) {
                int period = (scan.width - 1) * 2;
                return ((scan.depth + part2) % period == 0);
            })) {

            break;
        }
        ++part2;
    }
done:

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}