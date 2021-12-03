#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<vector<int>> lines;
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        stringstream str(s);

        vector<int> line;
        while (!str.eof()) {
            int x;
            str >> x;
            line.push_back(x);
        }

        lines.push_back(line);
    }

    int sum = 0;
    for (auto& line : lines) {
        auto [imin, imax] = minmax_element(line.begin(), line.end());
        sum += (*imax - *imin);
    }

    cout << "Part 1: " << sum << endl;

    sum = 0;
    for (auto& line : lines) {
        for (int i = 0; i < line.size(); ++i) {
            for (int j = 0; j < line.size(); ++j) {
                if (i == j) continue;

                if (line[i] % line[j] == 0) {
                    sum += (line[i] / line[j]);
                    goto next;
                }
            }
        }
    next:;
    }

    cout << "Part 2: " << sum << endl;
}