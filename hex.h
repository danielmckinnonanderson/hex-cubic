#ifndef HEX_H
#define HEX_H

#include <stdint.h>


// The maximum number of hexes in a single dimension
// Value of '24' means the axes can extend to -24 and 24.
#define HEX_MAX_COORD 24


typedef struct HexCubic {
    int8_t q;
    int8_t r;
    int8_t s;
} HexCubic;


// Turn a triple of ints into a single signed UUID
uint32_t Hex_Serialize(HexCubic *hex);

// Turn a UUID into a Hex
HexCubic Hex_Deserialize(uint32_t uuid);

// Get the distance between two hexes
// This is the maximum of the absolute differences between the hexes' coordinates
uint16_t Hex_Distance(HexCubic a, HexCubic b);


#endif // HEX_H

