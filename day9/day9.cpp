#include <iostream>
#include <string>
#include <regex>
#include <cassert>
#include <algorithm>
#include <numeric>

using namespace std;

struct Group {
    int level;
    vector<Group> children;
    int junksize = 0;
};

size_t EatJunk(const string& s, size_t pos, Group& parent)
{
    auto start = pos;
    assert(s[pos] == '<');
    while (pos < s.length()) {
        ++pos;
        if (s[pos] == '>') {
            ++pos;
            cout << "Junk: " << s.substr(start, pos - start) << endl;
            return pos;
        }
        if (s[pos] == '!') {
            ++pos;
        }
        else {
            ++parent.junksize;
        }
    }

    throw "Ick";
}

size_t EatGroup(const string& s, size_t pos, Group& parent)
{
    auto start = pos;
    assert(s[pos] == '{');
    Group g = { parent.level + 1 };
    cout << "Start Group (" << g.level << ")" << endl;

    while (pos < s.length()) {
        ++pos;
        if (s[pos] == '<') {
            pos = EatJunk(s, pos, g);
        }
        else if (s[pos] == '{') {
            pos = EatGroup(s, pos, g);
        }
        else if (s[pos] == '}') {
            ++pos;
            break;
        }
        else {
            throw "Ack";
        }

        if (s[pos] == '}') {
            ++pos;
            break;
        }
        assert(s[pos] == ',');
    }

    parent.children.push_back(g);
    //cout << "Group (" << g.level << "): " << s.substr(start, pos - start) << endl;
    return pos;
}

int Score(const Group& g)
{
    return accumulate(g.children.begin(), g.children.end(), g.level, [](auto x, auto& y) { return x + Score(y); });
}

int Junk(const Group& g)
{
    return accumulate(g.children.begin(), g.children.end(), g.junksize, [](auto x, auto& y) { return x + Junk(y); });
}

int main()
{
    string s;
    getline(cin, s);

    Group g = { 0 };
    EatGroup(s, 0, g);

    cout << "Part 1: " << Score(g) << endl;
    cout << "Part 2: " << Junk(g) << endl;
}