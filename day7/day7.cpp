#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <utility>
#include "../shared/Split.h"

using namespace std;

const regex INPUT_R("(\\w+) \\((\\d+)\\)(?: -> (.*))?");

typedef vector<string> ProgList;
typedef map<string, ProgList> Tower;
typedef map<string, int> Weights;
typedef map<string, string> Parents;

int CalcWeights(const string& root, const Tower& tower, const Weights& weights, Weights& totweights) {
    int w = weights.find(root)->second;
    for (auto& n : tower.find(root)->second) {
        int nw = CalcWeights(n, tower, weights, totweights);
        totweights[n] = nw;
        w += nw;
    }

    return w;
}

pair<string, int> OddOne(const string n, const Tower& tower, const Weights& totweights)
{
    ProgList pl = tower.find(n)->second;
    if (pl.size() < 3) {
        return { string(), 0 };
    }

    cout << "Look at " << n << ": ";
    for (auto c : pl) {
        cout << c << "=" << totweights.find(c)->second << " ";
    }
    cout << endl;

    int w0 = totweights.find(pl[0])->second;
    int w1 = totweights.find(pl[1])->second;

    if (w0 != w1) {
        int w2 = totweights.find(pl[2])->second;
        if (w0 == w2) {
            return { pl[1], w1 - w0 };
        }
        else {
            return { pl[0], w0 - w1 };
        }
    }

    int i = 2;
    while (totweights.find(pl[i])->second == w0) {
        ++i;
        if (i >= pl.size()) {
            return { string(), 0 };
        }
    }

    return { pl[i], totweights.find(pl[i])->second - w0 };
}

int main()
{
    Weights weights;
    Tower tower;
    Weights totweights;
    Parents parents;

    string s;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            weights[sm[1]] = stoi(sm[2]);
            auto children = Split(sm[3]);
            tower[sm[1]] = children;
            for (auto c : children) {
                parents[c] = sm[1];
            }
        }
    }

    // Find tower base by just going back up it
    string root = parents.begin()->first;
    while (parents.find(root) != parents.end()) {
        root = parents[root];
    }

    // Calc total weights recursively
    totweights[root] = CalcWeights(root, tower, weights, totweights);

    // Find imbalance
    string odd = root;
    int part2 = 0;
    auto p = OddOne(odd, tower, totweights);
    cout << p.first << " odd by " << p.second << endl;
    while (!p.first.empty()) {
        odd = p.first;
        part2 = p.second;
        p = OddOne(odd, tower, totweights);
        cout << p.first << " odd by " << p.second << endl;
    }
    
    part2 = weights.find(odd)->second - part2;

    // RESULTS...

    cout << "Part 1: " << root << endl;
    cout << "Part 2: " << part2 << endl;
}