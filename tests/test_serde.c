#include <stdio.h>
#include "../hex.h"
#include "tests.h"

#define TEST_NAME "Hex Serialization and Deserialization"

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
            HexCubic t2 = Hex_Deserialize(result);
            ASSERT(t.q == t2.q && t.r == t2.r && t.s == t2.s, "Hexes did not match after serialization and deserialization");
            // if (t.q != t2.q || t.r != t2.r || t.s != t2.s) {
            //     printf("DID NOT MATCH: q: %3d, r: %3d, s: %3d, serialized:   %8d\n", q, r, s, result);
            //     printf("               q: %3d, r: %3d, s: %3d, deserialized: %8d\n", t2.q, t2.r, t2.s, result);
            // } else {
            //     printf("MATCHED  :)    q: %3d, r: %3d, s: %3d -> %8d\n", q, r, s, result);
            // }
        }
    }

    return 0;
}


