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
    int id = 0;
    list<__int64> buf;
    bool waiting = false;
};

__int64 part2 = 0;

__int64 Val(const string& s, RegFile& r)
{
    if (isdigit(s[0]) || s[0] == '-') {
        return stoll(s);
    }

    return r[s];
}

bool DoOp(const string& op, Context& c, list<__int64>& sendbuf)
{
    c.waiting = false;
    auto s = Split(op, ' ');
    if (s[0] == "snd") {
        sendbuf.push_back(Val(s[1], c.regs));
        ++c.pc;
        if (c.id == 1) ++part2;
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
        if (c.buf.empty()) {
            c.waiting = true;
            return true;
        }

        c.regs[s[1]] = c.buf.front();
        c.buf.pop_front();
        ++c.pc;
    }
    else if (s[0] == "jgz") {
        if (Val(s[1], c.regs) > 0) {                // This was NOT obvious, that there could be literals in the comparison
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
    return false;
}

int main()
{
    vector<string> ops;
    string s;
    while (getline(cin, s)) {
        ops.push_back(s);
    }

    // Init
    vector<Context> contexts;
    contexts.resize(2);
    contexts[0].regs["p"] = 0;
    contexts[0].id = 0;
    contexts[1].regs["p"] = 1;
    contexts[1].id = 1;
    int terminated = 0;

    int running = 0;
    while(true) {
        Context& c = contexts[running];
        if (c.pc < 0 || c.pc >= ops.size()) {
            ++terminated;
            running = 1 - running;
            if (terminated == 2) {
                break;
            }
        }
        else {
            if (DoOp(ops[c.pc], c, contexts[1-running].buf)) {
                running = 1 - running;
                if (contexts[running].buf.empty() && contexts[running].waiting) {
                    // Both waiting on empty buffers, die
                    cout << "Deadlock!" << endl;
                    break;
                }
                else {
                    cout << "xfer to " << running << " with buf size " << contexts[running].buf.size() << endl << "  -> ";
                    for (auto x : contexts[running].buf) cout << x << " ";
                    cout << endl;
                }
            }
        }
    }

    // RESULTS...

    cout << "Part 2: " << part2 << endl;
}