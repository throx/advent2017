#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "../shared/Split.h"

using namespace std;

int main()
{
    vector<string> input;
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        input.push_back(s);
    }

    // Part 1
    {
        auto lens = SplitInt(input[0]);

        int size = 256;
        if (lens.size() < 10) {
            size = 5;
        }

        vector<int> nums;
        for (int i = 0; i < size; ++i) nums.push_back(i);

        int skip = 0;
        int p = 0;
        for (auto len : lens) {
            reverse(nums.begin(), nums.begin() + len);
            int r = (len + skip) % nums.size();
            p = (p + r) % nums.size();
            rotate(nums.begin(), nums.begin() + r, nums.end());
            ++skip;
        }
        if (p != 0) {
            rotate(nums.begin(), nums.begin() + (nums.size() - p), nums.end());
        }

        cout << "Part 1: " << nums[0] * nums[1] << endl;
    }

    for (auto s : input) {
        cout << "Hash of '" << s << "': ";
        int size = 256;
        
        vector<int> nums;
        for (int i = 0; i < size; ++i) nums.push_back(i);

        // Add trailer
        s.push_back(17);
        s.push_back(31);
        s.push_back(73);
        s.push_back(47);
        s.push_back(23);
        int skip = 0;
        int p = 0;

        for (int round = 0; round < 64; ++round) {
            for (int len : s) {
                reverse(nums.begin(), nums.begin() + len);
                int r = (len + skip) % nums.size();
                p = (p + r) % nums.size();
                rotate(nums.begin(), nums.begin() + r, nums.end());
                ++skip;
            }
        }
        if (p != 0) {
            rotate(nums.begin(), nums.begin() + (nums.size() - p), nums.end());
        }

        // Convert to dense hash
        vector<int> dense(size/16);
        for (int i = 0; i < size/16; ++i) {
            for (int j = 0; j < 16; ++j) {
                dense[i] ^= nums[i * 16 + j];
            }
        }

        // Print
        for (auto d : dense) {
            cout << setw(2) << setfill('0') << hex << d;
        }
        cout << endl;

    }
}