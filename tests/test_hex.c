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
    HexCubic a = {
        .q = 1,
        .r = 0,
        .s = -1,
    };

    HexCubic b = {
        .q = 4,
        .r = -5,
        .s = 1,
    };

    HexCubic expected_a = {
        .q = -3,
        .r = 5,
        .s = -2,
    };

    HexCubic result_a = Hex_Subtract(a, b);
    ASSERT(result_a.q == expected_a.q, "HexCubic subtract: q did not match");
    ASSERT(result_a.r == expected_a.r, "HexCubic subtract: r did not match");
    ASSERT(result_a.s == expected_a.s, "HexCubic subtract: s did not match");


    return 0;
}


int Test_HexDistanceFromOrigin(void)
{
    HexCubic a = {
        .q = -3,
        .r = -5,
        .s = 8,
    };

    int expected = 8;
    int result = Hex_DistanceFromOrigin(a);
    ASSERT(result == expected, "HexCubic distance from origin: result does not equal expected");

    return 0;
}


int Test_HexDistance(void)
{
    HexCubic start = {
        .q = -3,
        .r = 6,
        .s = -3,
    };

    HexCubic end = {
        .q = 1,
        .r = 18,
        .s = -19
    };

    int result = Hex_Distance(start, end);
    int expected = 16;

    ASSERT(result == expected, "HexCubic distance: result did not equal expected");

    return 0;
}


int Test_HexGetAdjacentHex(void)
{
    const HexCubic start = {
        .q = -2,
        .r = 1,
        .s = 1,
    };

    char *assertion_failed_msg = "HexCubic get adjacent hex: result_a did not equal expected";
    const HexCubic result_a = Hex_GetAdjacentHex(start, RPlaneQNeg);
    ASSERT(result_a.q == start.q - 1, assertion_failed_msg);
    ASSERT(result_a.r == start.r, assertion_failed_msg);
    ASSERT(result_a.s == start.s + 1, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_b did not equal expected";
    const HexCubic result_b = Hex_GetAdjacentHex(start, RPlaneQPos);
    ASSERT(result_b.q == start.q + 1, assertion_failed_msg);
    ASSERT(result_b.r == start.r, assertion_failed_msg);
    ASSERT(result_b.s == start.s - 1, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_c did not equal expected";
    const HexCubic result_c = Hex_GetAdjacentHex(start, QPlaneRNeg);
    ASSERT(result_c.q == start.q, assertion_failed_msg);
    ASSERT(result_c.r == start.r - 1, assertion_failed_msg);
    ASSERT(result_c.s == start.s + 1, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_d did not equal expected";
    const HexCubic result_d = Hex_GetAdjacentHex(start, QPlaneRPos);
    ASSERT(result_d.q == start.q, assertion_failed_msg);
    ASSERT(result_d.r == start.r + 1, assertion_failed_msg);
    ASSERT(result_d.s == start.s - 1, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_e did not equal expected";
    const HexCubic result_e = Hex_GetAdjacentHex(start, SPlaneQNeg);
    ASSERT(result_e.q == start.q - 1, assertion_failed_msg);
    ASSERT(result_e.r == start.r + 1, assertion_failed_msg);
    ASSERT(result_e.s == start.s, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_f did not equal expected";
    const HexCubic result_f = Hex_GetAdjacentHex(start, SPlaneQPos);
    ASSERT(result_f.q == start.q + 1, assertion_failed_msg);
    ASSERT(result_f.r == start.r - 1, assertion_failed_msg);
    ASSERT(result_f.s == start.s, assertion_failed_msg);

    assertion_failed_msg = "HexCubic get adjacent hex: result_g did not equal expected";
    const HexCubic result_g = Hex_GetAdjacentHex(start, HexDirectionZero);
    ASSERT(result_g.q == start.q, assertion_failed_msg);
    ASSERT(result_g.r == start.r, assertion_failed_msg);
    ASSERT(result_g.s == start.s, assertion_failed_msg);

    return 0;
}


int Test_HexLine(void)
{
    
    HexCubic start = {
        .q = -3,
        .r = 2,
        .s = 1,
    };

    HexCubic end = {
        .q = 1,
        .r = -2,
        .s = 1
    };

    uint16_t distance = Hex_Distance(start, end);
    HexCubic *result_line = Hex_Line(start, end, distance + 1);

    ASSERT(result_line != NULL, "HexCubic line: Line was NULL");

    return 0;
}


int Test_HexDirection(void)
{
    return 0;
}
