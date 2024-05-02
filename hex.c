#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hex.h"


const HexCubic HEX_NORMALS[7] = {
    { -1,  0,  1 }, // RPlaneQNeg
    {  1,  0, -1 }, // RPlaneQPos
    {  0, -1,  1 }, // QPlaneRNeg
    {  0,  1, -1 }, // QPlaneRPos
    { -1,  1,  0 }, // SPlaneQNeg
    {  1, -1,  0 }, // SPlaneQPos
    {  0,  0,  0 }, // Zero
};


uint32_t Hex_Serialize(HexCubic *hex)
{
    uint32_t result = 0;

    result |= ((uint32_t) hex->q & 0xFF) << 16;
    result |= ((uint32_t) hex->r & 0xFF) << 8;
    result |= ((uint32_t) hex->s & 0xFF);

    return result;
}


void Hex_Deserialize(uint32_t uuid, HexCubic *out)
{
    if (out == NULL) {
        return;
    }

    out->q = (uuid >> 16) & 0xFF;
    out->r = (uuid >>  8) & 0xFF;
    out->s = uuid & 0xFF;
}


// Add two hexes (cartesian)
HexCubic Hex_Add(HexCubic a, HexCubic b)
{
    HexCubic result = {
        .q = a.q + b.q,
        .r = a.r + b.r,
        .s = a.s + b.s,
    };

    return result;
}


// Subtract two hexes (cartesian)
HexCubic Hex_Subtract(HexCubic a, HexCubic b)
{
    HexCubic result = {
        .q = a.q - b.q,
        .r = a.r - b.r,
        .s = a.s - b.s,
    };

    return result;
}


uint16_t Hex_DistanceFromOrigin(HexCubic hex)
{
    return (abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2;
}


uint16_t Hex_Distance(HexCubic start, HexCubic end)
{
    const HexCubic difference = Hex_Subtract(start, end);
    return Hex_DistanceFromOrigin(difference);
}


HexCubic Hex_GetAdjacentHex(HexCubic start, HexDirection direction)
{
    assert(direction >= 0 && direction <= 7);
    const HexCubic direction_vector = HEX_NORMALS[direction];
    return Hex_Add(start, direction_vector);
}


uint32_t *HexId_Line(HexCubicId start, HexCubicId end)
{
    return 0;
}

