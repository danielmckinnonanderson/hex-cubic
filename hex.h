#ifndef HEX_H
#define HEX_H

#include <stdint.h>


// The maximum number of hexes in a single dimension
// Value of '24' means the axes can extend to -24 and 24.
#define HEX_MAX_COORD 24


typedef uint32_t HexCubicId;

typedef struct HexCubic {
    int8_t q;
    int8_t r;
    int8_t s;
} HexCubic;


struct HexNormalVectors {
    const HexCubic ZERO;
    const HexCubic R_PLANE_Q_NEG;
    const HexCubic R_PLANE_Q_POS;
    const HexCubic Q_PLANE_R_NEG;
    const HexCubic Q_PLANE_R_POS;
    const HexCubic S_PLANE_Q_NEG;
    const HexCubic S_PLANE_Q_POS;
};

// Normal vectors:
// ZERO          = {  0,  0,  0 },
// R_PLANE_Q_NEG = { -1,  0,  1 },
// R_PLANE_Q_POS = {  1,  0, -1 },
// Q_PLANE_R_NEG = {  0, -1,  1 },
// Q_PLANE_R_POS = {  0,  1, -1 },
// S_PLANE_Q_NEG = { -1,  1,  0 },
// S_PLANE_Q_POS = {  1, -1,  0 },
extern const struct HexNormalVectors HEX_NORMALS;

// Turn a triple of ints into a single signed UUID
uint32_t Hex_Serialize(HexCubic *hex);

// Turn a UUID into a Hex
void Hex_Deserialize(uint32_t uuid, HexCubic *out);

// Add two hexes (cartesian)
HexCubic Hex_Add(HexCubic a, HexCubic b);

// Subtract two hexes (cartesian)
HexCubic Hex_Subtract(HexCubic a, HexCubic b);

// Get the distance between hex and origin
uint16_t Hex_DistanceFromOrigin(HexCubic hex);

// Get the distance (in # of hexes) between start and end
// This is the maximum of the absolute differences between the hexes' coordinates
// In other words, a line beginning with start and ending at
//  end would consist of 5 spaces, so the distance between them is 4.
uint16_t Hex_Distance(HexCubic start, HexCubic end);

// Get a line of hexes from a to b
// Where distance is the result of Hex_Distance(a, b)
// The line is a list of hexes from a to b.
// The caller must allocate & free the line, (distance + 1) * sizeof(HexCubic)
HexCubic *Hex_Line(HexCubic start, HexCubic end, uint16_t line_length);

// Wraps Hex_Line, but instead returns a UUID array
int *HexId_Line(HexCubic a, HexCubic b, uint16_t distance, HexCubicId *line);

#endif // HEX_H
