#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <numeric>

using namespace std;

struct Action {
    bool writeval;
    int incr;
    char nextstate;
};

typedef map<bool, Action> State;
typedef map<char, State> StateMap;

int main()
{
    string s;
    smatch sm;
    getline(cin, s);  // start state is always A

    getline(cin, s);  // iters
    regex_match(s.cbegin(), s.cend(), sm, regex(".* (\\d+) .*"));
    int iters = stoi(sm[1]);

    StateMap statemap;
    while (!cin.eof()) {
        State state;

        getline(cin, s);
        getline(cin, s);
        char currstate = s[9];

        getline(cin, s);

        Action a;
        getline(cin, s);
        a.writeval = (s[22] == '1');
        
        getline(cin, s);
        a.incr = (s[27] == 'r' ? 1 : -1);

        getline(cin, s);
        a.nextstate = s[26];
        state[false] = a;

        getline(cin, s);

        getline(cin, s);
        a.writeval = (s[22] == '1');

        getline(cin, s);
        a.incr = (s[27] == 'r' ? 1 : -1);

        getline(cin, s);
        a.nextstate = s[26];
        state[true] = a;

        statemap[currstate] = state;
    }
    
    map<int, bool> tape;
    int pos = 0;
    char currstate = 'A';

    for (int i = 0; i < iters; ++i) {
        auto& a = statemap[currstate][tape[pos]];
        tape[pos] = a.writeval;
        pos += a.incr;
        currstate = a.nextstate;
    }

    auto part1 = count_if(tape.begin(), tape.end(), [](auto& x) { return x.second; });
    cout << "Part 1: " << part1 << endl;
}