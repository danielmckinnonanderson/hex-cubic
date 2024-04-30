#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hex.h"

const struct HexNormalVectors HEX_NORMALS = {
    .ZERO          = {  0,  0,  0 },
    .R_PLANE_Q_NEG = { -1,  0,  1 },
    .R_PLANE_Q_POS = {  1,  0, -1 },
    .Q_PLANE_R_NEG = {  0, -1,  1 },
    .Q_PLANE_R_POS = {  0,  1, -1 },
    .S_PLANE_Q_NEG = { -1,  1,  0 },
    .S_PLANE_Q_POS = {  1, -1,  0 },
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


HexCubic *Hex_Line(HexCubic start, HexCubic end, uint16_t line_length)
{
    HexCubic line[line_length];

    for (int i = 0; i <= line_length; i++) {
    }

    return line;
}

