#include <stdio.h>
#include <stdlib.h>
#include "../hex.h"
#include "tests.h"

// Tests the serialization and deserialization of hexes
// Returns the number of assertions failed
int Test_HexSerDe(void)
{
    for (int q = -HEX_MAX_COORD; q < HEX_MAX_COORD; q++) {
        for (int r = -HEX_MAX_COORD; r < HEX_MAX_COORD; r++) {
            // Calculate s, such that q = q, r = r, s = -q - r
            int s = -q - r;

            HexCubic t = {
                .q = q,
                .r = r,
                .s = s
            };

            int32_t result = Hex_Serialize(&t);
            HexCubic t2 = {0, 0, 0};

            Hex_Deserialize(result, &t2);
            ASSERT((t.q == t2.q && t.r == t2.r && t.s == t2.s), "Hexes did not match after serialization and deserialization");
        }
    }

    return 0;
}


