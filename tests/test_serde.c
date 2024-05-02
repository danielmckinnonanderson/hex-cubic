#include "../hex.h"
#include "tests.h"


#define TEST_SERDE_ENCOUNTERED_LENGTH (HEX_MAX_COORD * 2) * (HEX_MAX_COORD * 2)

int TestUtil_IsIdPresent(const uint16_t encountered[TEST_SERDE_ENCOUNTERED_LENGTH],
                         const int encountered_length,
                         uint16_t checking);


// Tests the serialization and deserialization of hexes
// Returns the number of assertions failed
int Test_HexSerDe(void)
{
    // Since the hexes we're generating each iteration are unique,
    // then every element of this array should also be unique.
    // As the test progresses, we'll check that the ID isn't already
    // in this array before continuing. If it is already present,
    // this test will fail.
    uint16_t encountered[TEST_SERDE_ENCOUNTERED_LENGTH] = {};
    int encountered_length = 0;

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

            int already_present = TestUtil_IsIdPresent(encountered, encountered_length, result);
            ASSERT(already_present == 0, "Hex ID was not unique");
        }
    }

    return 0;
}


int TestUtil_IsIdPresent(const uint16_t encountered[TEST_SERDE_ENCOUNTERED_LENGTH],
                         const int encountered_length,
                         uint16_t checking)
{
    for (int i = 0; i < encountered_length; i++) {
        int id = encountered[i];
        if (id == checking) {
            // Value we're checking is present
            return 1;
        }
    }

    // Value was never encountered in the array
    return 0;
}

