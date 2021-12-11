#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <numeric>
#include <set>
#include "../shared/Point.h"

using namespace std;

//const string INPUT = "flqrgnkx"s;
const string INPUT = "ugkiagan"s;

typedef unsigned char uchar;

vector<uchar> KnotHash(string s)
{
    vector<uchar> nums;
    for (int i = 0; i < 256; ++i) nums.push_back(i);

    // Add trailer
    s.push_back(17);
    s.push_back(31);
    s.push_back(73);
    s.push_back(47);
    s.push_back(23);
    uchar skip = 0;
    uchar p = 0;

    for (uchar round = 0; round < 64; ++round) {
        for (uchar len : s) {
            reverse(nums.begin(), nums.begin() + len);
            uchar r = (len + skip);
            p = (p + r);
            rotate(nums.begin(), nums.begin() + r, nums.end());
            ++skip;
        }
    }
    if (p != 0) {
        rotate(nums.begin(), nums.begin() + (nums.size() - p), nums.end());
    }

    // Convert to dense hash
    vector<uchar> dense(16);
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            dense[i] ^= nums[i * 16 + j];
        }
    }

    return dense;
}

void GetGroup(set<Point2>& pts)
{
    set<Point2> todo;
    todo.insert(*pts.begin());

    while (!todo.empty()) {
        Point2 p = *todo.begin();
        todo.erase(todo.begin());
        pts.erase(p);

        p.DoSquareNeighbours([&](auto& x) {
            if (pts.find(x) != pts.end()) {
                todo.insert(x);
            }
            });
    }
}

int main()
{
    assert(KnotHash("") == vector<uchar>({ 0xa2, 0x58, 0x2a, 0x3a, 0x0e, 0x66, 0xe6, 0xe8, 0x6e, 0x38, 0x12, 0xdc, 0xb6, 0x72, 0xa2, 0x72 }));

    set<Point2> bits;

    for (int row = 0; row < 128; ++row) {
        stringstream ss;
        ss << INPUT << '-' << row;
        auto hash = KnotHash(ss.str());

        for (int col = 0; col < 128; ++col) {
            int b = (1 << (7 - (col % 8)));
            if ((hash[col / 8] & b) != 0) {
                bits.insert(Point2({ row, col }));
            }
        }
    }
    
    int part1 = bits.size();

    int part2 = 0;
    while (!bits.empty()) {
        GetGroup(bits);
        ++part2;
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}