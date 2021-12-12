#include <iostream>
#include <string>
#include <vector>
#include "../shared/Split.h"
#include <map>

using namespace std;

typedef map<string, __int64> RegFile;
struct Context
{
    RegFile regs;
    int pc = 0;
    __int64 freq = 0;
};

__int64 part1 = -1;

__int64 Val(const string& s, RegFile& r)
{
    if (isdigit(s[0]) || s[0] == '-') {
        return stoll(s);
    }

    return r[s];
}

void DoOp(const string& op, Context& c)
{
    auto s = Split(op, ' ');
    if (s[0] == "snd") {
        c.freq = Val(s[1], c.regs);
        ++c.pc;
    }
    else if (s[0] == "set") {
        c.regs[s[1]] = Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "add") {
        c.regs[s[1]] += Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "mul") {
        c.regs[s[1]] *= Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "mod") {
        c.regs[s[1]] = c.regs[s[1]] % Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "rcv") {
        if (c.regs[s[1]] != 0) {
            c.regs[s[1]] = c.freq;
            part1 = c.freq;
        }
        ++c.pc;
    }
    else if (s[0] == "jgz") {
        if (c.regs[s[1]] > 0) {
            c.pc += Val(s[2], c.regs);
        }
        else {
            ++c.pc;
        }
    }
    else {
        throw "Invalid Opcode";
    }

    cout << op << ": ";
    for (auto x : c.regs) {
        cout << x.first << "=" << x.second << " ";
    }
    cout << "freq=" << c.freq << endl;
}

int main()
{
    vector<string> ops;
    string s;
    while (getline(cin, s)) {
        ops.push_back(s);
    }

    Context c;

    while (c.pc >= 0 && c.pc < ops.size()) {
        DoOp(ops[c.pc], c);
        if (part1 > 0) {
            break;
        }
    }

    // RESULTS...

    cout << "Part 1: " << part1 << endl;
}