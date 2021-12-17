#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <cassert>
#include <numeric>
#include "../shared/Split.h"

using namespace std;

const regex INPUT_R("(.+) => (.+)");

string Rotate(const string& inp)
{
    if (inp.size() == 5) {
        return ""s + inp[3] + inp[0] +
               '/' + inp[4] + inp[1];
    }
    return ""s + inp[8] + inp[4] + inp[0] +
        '/' + inp[9] + inp[5] + inp[1] +
        '/' + inp[10] + inp[6] + inp[2];
}

string Flip(const string& inp) {
    if (inp.size() == 5) {
        return ""s + inp[1] + inp[0] +
               '/' + inp[4] + inp[3];
    }

    return ""s + inp[2] + inp[1] + inp[0] +
        '/' + inp[6] + inp[5] + inp[4] +
        '/' + inp[10] + inp[9] + inp[8];
}

vector<string> Shard(const string& inp) {
    if (inp.size() != 19) return { inp };

    return { ""s + inp[0] + inp[1] + '/' + inp[5] + inp[6],
        ""s + inp[2] + inp[3] + '/' + inp[7] + inp[8],
        ""s + inp[10] + inp[11] + '/' + inp[15] + inp[16],
        ""s + inp[12] + inp[13] + '/' + inp[17] + inp[18] };
}

typedef vector<string> Grid;
size_t XSZ(const Grid& g) { return g[0].length(); }
size_t YSZ(const Grid& g) { return g.size(); }

Grid GetGrid(const Grid& base, size_t x0, size_t y0, size_t dim)
{
    Grid ret;
    for (size_t y = 0; y < dim; ++y) {
        ret.push_back(base[y + y0].substr(x0, dim));
    }
    return ret;
}

Grid ToGrid(string s)
{
    return Split(s, '/');
}

void ResizeGrid(Grid& g, size_t dim)
{
    g.resize(dim);
    for (auto& s : g) s.resize(dim, '?');
}

void PasteGrid(Grid& base, const Grid& overlay, size_t x0, size_t y0)
{
    for (size_t y = 0; y < YSZ(overlay); ++y) {
        for (size_t x = 0; x < XSZ(overlay); ++x) {
            assert(base[y + y0][x + x0] == '?');
            base[y + y0][x + x0] = overlay[y][x];
        }
    }
}

size_t HashCount(const Grid& base)
{
    return accumulate(base.begin(), base.end(), (size_t)0, [](auto c, auto& x) {
        return c + count_if(x.begin(), x.end(), [](auto c) { return c == '#'; });
        });
}


int main()
{
    map<Grid, Grid> rules;

    string s;
    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, INPUT_R)) {
            Grid to = ToGrid(sm[2]);

            string s = sm[1];
            for (int f = 0; f < 4; ++f) {
                rules[ToGrid(s)] = to;
                s = Rotate(s);
            }
            s = Flip(s);
            for (int f = 0; f < 4; ++f) {
                rules[ToGrid(s)] = to;
                s = Rotate(s);
            }
            s = Flip(s);
            assert(s == sm[1]);
        }
    }

    Grid map = ToGrid(".#./..#/###");
    for (int iter = 0; iter < 18; ++iter) {

        Grid newmap;
        // Two or Three?
        if (YSZ(map) % 2 == 0) {

            // Will grow to 150% of size, so create new
            ResizeGrid(newmap, YSZ(map) * 3 / 2);

            // Split into pairs
            for (size_t y0 = 0; y0 < YSZ(map); y0 += 2) {
                for (size_t x0 = 0; x0 < XSZ(map); x0 += 2) {
                    Grid sub = GetGrid(map, x0, y0, 2);
                    PasteGrid(newmap, rules[sub], x0 * 3 / 2, y0 * 3 / 2);
                }
            }

        }
        else {
            // Will grow to 133% of size, so create new
            ResizeGrid(newmap, YSZ(map) * 4 / 3);

            // Split into trips
            for (size_t y0 = 0; y0 < YSZ(map); y0 += 3) {
                for (size_t x0 = 0; x0 < XSZ(map); x0 += 3) {
                    Grid sub = GetGrid(map, x0, y0, 3);
                    PasteGrid(newmap, rules[sub], x0 * 4 / 3, y0 * 4 / 3);
                }
            }

        }
        swap(map, newmap);
        cout << "Iteration " << iter + 1 << " = " << HashCount(map) << endl;
    }
}