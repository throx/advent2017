#pragma once

#include "Point.h"

// Uses cube coords defined at https://www.redblobgames.com/grids/hexagons/

class HexPoint : public Point3
{
    using Point3::Point3;
};

int HexDist(HexPoint p1, HexPoint p2)
{
    return (abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) + abs(p1[2] - p2[2])) / 2;
}

namespace HP
{
    const HexPoint N({ 0, 1, -1 });
    const HexPoint NE({ 1, 0, -1 });
    const HexPoint SE({ 1, -1, 0 });
    const HexPoint S({ 0, -1, 1 });
    const HexPoint SW({ -1, 0, 1 });
    const HexPoint NW({ -1, 1, 0 });

    std::map<std::string, HexPoint> DIRS(
        {
            {"N", N},
            {"NE", NE},
            {"SE", SE},
            {"S", S},
            {"SW", SW},
            {"NW", NW},
            {"n", N},
            {"ne", NE},
            {"se", SE},
            {"s", S},
            {"sw", SW},
            {"nw", NW},
        }
    );
}