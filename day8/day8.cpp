#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <algorithm>

using namespace std;

//c inc -20 if c == 10
const regex INPUT_R("(\\w+) (\\w+) (-?\\d+) (\\w+) (\\w+) (.+) (-?\\d+)");

struct Instr {
    string reg;
    string op;
    int amount;
    string testreg;
    string comp;
    int testval;
};

typedef map<string, int> RegFile;

bool Comp(const Instr& instr, RegFile& regs)
{
    if (instr.comp == "==") return regs[instr.testreg] == instr.testval;
    if (instr.comp == "!=") return regs[instr.testreg] != instr.testval;
    if (instr.comp == ">") return regs[instr.testreg] > instr.testval;
    if (instr.comp == "<") return regs[instr.testreg] < instr.testval;
    if (instr.comp == ">=") return regs[instr.testreg] >= instr.testval;
    if (instr.comp == "<=") return regs[instr.testreg] <= instr.testval;
    throw "Invalid Op";
}

void Do(const Instr& instr, RegFile& regs)
{
    if (Comp(instr, regs)) {
        if (instr.op == "inc") regs[instr.reg] += instr.amount;
        else if (instr.op == "dec") regs[instr.reg] -= instr.amount;
    }
}

int main()
{
    vector<Instr> instrs;

    string s;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            Instr ins = {
                sm[1],
                sm[2],
                stoi(sm[3]),
                sm[5],
                sm[6],
                stoi(sm[7])
            };
            instrs.push_back(ins);
        }
    }

    RegFile regs;
    int part2 = 0;
    for (auto& instr : instrs) {
        Do(instr, regs);
        part2 = max(part2, max_element(regs.begin(), regs.end(), [](auto x, auto y) { return x.second < y.second; })->second);
    }

    int part1 = max_element(regs.begin(), regs.end(), [](auto x, auto y) { return x.second < y.second; })->second;
    // RESULTS...

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}