#include <iostream>
#include <string>
#include <set>
#include "../shared/Point.h"

using namespace std;

const Point2 Dirs[] = {P2::N, P2::E, P2::S, P2::W};

int Left(int d)
{
    --d;
    if (d < 0) d = 3;
    return d;
}

int Right(int d)
{
    ++d;
    if (d > 3) d = 0;
    return d;
}

enum State { CLEAN, WEAKENED, INFECTED, FLAGGED };
State NextState(State state) { return (State)Right(state); }

int main()
{
    set<Point2> infected;
    map<Point2, State> states;

    string s;
    int y = 0;
    while (getline(cin, s)) {
        for (int x = 0; x < s.length(); ++x) {
            if (s[x] == '#') {
                infected.insert({ x, y });
                states[{x, y}] = INFECTED;
            }
        }
        ++y;
    }


    Point2 pos = { y / 2, y / 2 };
    int dir = 0;
    int part1 = 0;

    for (int t = 0; t < 10000; ++t) {
        if (infected.find(pos) == infected.end()) {
            dir = Left(dir);
            infected.insert(pos);
            ++part1;
        }
        else {
            dir = Right(dir);
            infected.erase(pos);
        }
        pos += Dirs[dir];
    }

    cout << "Part 1: " << part1 << endl;

    pos = { y / 2, y / 2 };
    dir = 0;
    int part2 = 0;
    for (int t = 0; t < 10000000; ++t) {
        auto& state = states[pos];
        switch (state) {
        case CLEAN:
            dir = Left(dir);
            break;
        case WEAKENED:
            ++part2;
            break;
        case INFECTED:
            dir = Right(dir);
            break;
        case FLAGGED:
            dir = Left(Left(dir));
            break;
        }
        state = NextState(state);
        pos += Dirs[dir];
    }

    cout << "Part 2: " << part2 << endl;
}