#include <iostream>
#include <string>
#include <vector>

using namespace std;

//const size_t STEP = 3;
const size_t STEP = 335;

int main()
{
    vector<int> v;
    v.push_back(0);
    size_t pos = 0;
    for (int i = 1; i <= 2017; ++i)
    {
        pos = (pos + STEP) % v.size();
        v.insert(v.begin() + pos + 1, i);
        ++pos;
    }
    int part1 = v[(pos + 1) % v.size()];

    cout << "Part 1: " << part1 << endl;

    // Don't have to keep track of the whole array, just the number
    // inserted after position 0, as it can never move.
    int part2;
    for (int i = 1; i <= 50000000; ++i) {
        pos = (pos + STEP) % i;
        if (pos == 0) {
            part2 = i;
        }
        ++pos;
    }
    cout << "Part 2: " << part2 << endl;
}