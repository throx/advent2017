#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> data;
    string s;
    getline(cin, s);
    for (char c : s) {
        data.push_back(c - '0');
    }

    int sum1 = 0;
    int sum2 = 0;
    int n = data.size();
    for (int i = 0; i < n; ++i) {
        if (data[i] == data[(i + 1) % n]) {
            sum1 += data[i];
        }
        if (data[i] == data[(i + n / 2) % n]) {
            sum2 += data[i];
        }
    }

    // RESULTS...

    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << sum2 << endl;
}