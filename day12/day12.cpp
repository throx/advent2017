#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include "../shared/Split.h"

using namespace std;

const regex INPUT_R("(\\d+) <-> (.+)");

typedef vector<int> Pids;
typedef map<int, Pids> PidMap;

set<int> GetGroup(int start, const PidMap& pm)
{
    set<int> done;
    set<int> todo;
    todo.insert(start);

    while (!todo.empty()) {
        int p = *todo.begin();
        todo.erase(todo.begin());
        done.insert(p);

        for (auto& x : pm.find(p)->second) {
            if (done.find(x) == done.end()) {
                todo.insert(x);
            }
        }
    }

    return done;
}

int main()
{
    PidMap pm;
    set<int> remaining;

    string s;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            int pid = stoi(sm[1]);
            pm[pid] = SplitInt(sm[2]);
            remaining.insert(pid);
        }
    }

    int part1 = GetGroup(0,pm).size();
    int part2 = 0;
    
    while (!remaining.empty()) {
        for (auto& x : GetGroup(*remaining.begin(), pm)) {
            remaining.erase(x);
        }
        ++part2;
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}