#include <iostream>
#include <string>
#include <regex>
#include "../shared/Point.h"
#include <algorithm>
#include <map>

using namespace std;

const regex INPUT_R("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");

struct Particle {
    Point3 p, v, a;
};

int main()
{
    map<int, Particle> parts;

    string s;
    int id = 0;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            parts[id] = { { stoi(sm[1]),stoi(sm[2]), stoi(sm[3]) },
                          { stoi(sm[4]),stoi(sm[5]), stoi(sm[6]) },
                          { stoi(sm[7]),stoi(sm[8]), stoi(sm[9]) } };
            ++id;
        }
    }

    auto it = min_element(parts.begin(), parts.end(), [](auto x, auto y) { return Dist(x.second.a, Point3()) < Dist(y.second.a, Point3()); });
    auto part1 = it->first;
    
    int part2 = 0;
    int t = 0;
    while (t < 100) {

        // Resolve collisions
        set<int> coll;
        for (auto& i : parts) {
            for (auto& j : parts) {
                if (i.first == j.first) continue;

                if (i.second.p == j.second.p) {
                    coll.insert(i.first);
                    coll.insert(j.first);
                }
            }
        }
        for (auto i : coll) {
            parts.erase(i);
        }

        // Move
        for (auto& i : parts) {
            i.second.v += i.second.a;
            i.second.p += i.second.v;
        }

        ++t;
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << parts.size() << endl;
}