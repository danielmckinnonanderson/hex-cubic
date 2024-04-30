#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hex.h"


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

HexCubic *Hex_Line(HexCubic a, HexCubic b, uint16_t distance, HexCubic *line)
{
    assert(line != NULL);

    for (int i = 0; i <= distance; i++) {
    }

    return line;
}

