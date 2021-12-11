#include <iostream>
#include <string>
#include <regex>

using namespace std;

//const __int64 A = 65;
//const __int64 B = 8921;
const __int64 A = 783;
const __int64 B = 325;

int main()
{
    __int64 a = A;
    __int64 b = B;

    int part1 = 0;
    for (int t = 0; t < 40000000; ++t) {
        a = (a * 16807) % 2147483647;
        if (a < 0) a += 2147483647;
        b = (b * 48271) % 2147483647;
        if (b < 0) b += 2147483647;

        if ((a & 0xffff) == (b & 0xffff)) {
            ++part1;
        }
    }

    a = A;
    b = B;

    int part2 = 0;
    for (int t = 0; t < 5000000; ++t) {
        do {
            a = (a * 16807) % 2147483647;
            if (a < 0) a += 2147483647;
        } while (a % 4 != 0);
        do {
            b = (b * 48271) % 2147483647;
            if (b < 0) b += 2147483647;
        } while (b % 8 != 0);

        if ((a & 0xffff) == (b & 0xffff)) {
            ++part2;
        }
    }

    // RESULTS...

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}