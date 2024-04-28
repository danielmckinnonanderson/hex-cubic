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


HexCubic Hex_Deserialize(uint32_t uuid)
{
    HexCubic result = {
        .q = (uuid >> 16) & 0xFF,
        .r = (uuid >>  8) & 0xFF,
        .s = uuid & 0xFF,
    };

    return result;
}

