#include <stdio.h>
#include "../hex.h"
#include "tests.h"

int Test_HexAdd(void)
{
    HexCubic a = {
        .q = 1,
        .r = 0,
        .s = -1
    };

    HexCubic b = {
        .q = 4,
        .r = -5,
        .s = 1
    };

    HexCubic expected = {
        .q = 5,
        .r = -5,
        .s = 0
    };

    HexCubic result = Hex_Add(a, b);
    ASSERT(result.q == expected.q, "HexCubic add: q did not match");
    ASSERT(result.r == expected.r, "HexCubic add: r did not match");
    ASSERT(result.s == expected.s, "HexCubic add: s did not match");

    return 0;
}


int Test_HexSubtract(void)
{

}


int Test_HexLine(void)
{

}


int Test_HexDistance(void)
{
    
}

