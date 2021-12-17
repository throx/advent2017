#include <iostream>
#include <string>
#include <vector>
#include "../shared/Split.h"
#include <map>
#include <list>

using namespace std;

typedef map<string, __int64> RegFile;
struct Context
{
    RegFile regs;
    int pc = 0;
};

__int64 part1 = 0;

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
    if (s[0] == "set") {
        c.regs[s[1]] = Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "sub") {
        c.regs[s[1]] -= Val(s[2], c.regs);
        ++c.pc;
    }
    else if (s[0] == "mul") {
        c.regs[s[1]] *= Val(s[2], c.regs);
        ++c.pc;
        ++part1;
    }
    else if (s[0] == "jnz") {
        if (Val(s[1], c.regs) != 0) {
            c.pc += (int)Val(s[2], c.regs);
        }
        else {
            ++c.pc;
        }
    }
    else {
        throw "Invalid Opcode";
    }

    /*
    cout << c.id << "| " << op << ": ";
    for (auto x : c.regs) {
        cout << x.first << "=" << x.second << " ";
    }
    cout << endl;
    */
}

int main()
{
    vector<string> ops;
    string s;
    while (getline(cin, s)) {
        ops.push_back(s);
    }

    {
        Context c;

        while (c.pc >= 0 && c.pc < ops.size()) {
            DoOp(ops[c.pc], c);
        }
        for (auto x : c.regs) {
            cout << x.first << "=" << x.second << " ";
        }

        cout << "Part 1: " << part1 << endl;
    }

    {
        __int64 b = 0;
        __int64 c = 0;
        __int64 d = 0;
        __int64 e = 0;
        __int64 f = 0;
        __int64 g = 0;
        __int64 h = 0;

        bool debug = false;
        b = 57;
        c = 57;
        if (!debug) {
            b = 105700;
            c = 122700;
        }

        while (true) {
            f = 1;

            // If b is prime
            for (d = 2; d < b; ++d) {
                if (b % d == 0) {
                    f = 0;
                    break;
                }
            }

            // If b is prime, ++h
            if (f == 0) {
                h++;
            }

            if (b == c) break;
            b += 17;
        };

        cout << "Part 2: " << h << endl;
    }
}