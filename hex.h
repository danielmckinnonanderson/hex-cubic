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

typedef enum HexDirection {
    RPlaneQNeg = 0,
    RPlaneQPos,
    QPlaneRNeg,
    QPlaneRPos,
    SPlaneQNeg,
    SPlaneQPos,
    HexDirectionZero,
} HexDirection;


// Normal vectors:
// R_PLANE_Q_NEG = { -1,  0,  1 },
// R_PLANE_Q_POS = {  1,  0, -1 },
// Q_PLANE_R_NEG = {  0, -1,  1 },
// Q_PLANE_R_POS = {  0,  1, -1 },
// S_PLANE_Q_NEG = { -1,  1,  0 },
// S_PLANE_Q_POS = {  1, -1,  0 },
// ZERO          = {  0,  0,  0 },
//
// Use the HexDirection enum as an index into this array
extern const HexCubic HEX_NORMALS[7];

// Turn a triple of ints into a single unsigned UUID
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

// Get the Hex which is a neighbor of start in the specified direction
HexCubic Hex_GetAdjacentHex(HexCubic start, HexDirection direction);

// Put a line of hexes from a to b into line_buffer
// Where distance is the result of Hex_Distance(a, b)
// The line is a list of hexes from a to b.
// The caller must allocate & free the line, (distance + 1) * sizeof(HexCubic)
void Hex_Line(HexCubic start, HexCubic end, HexCubic *line_buffer);

// Return an array of hexes (serialized as integers)
// From start to end, where start is the first element of
// the line and end is the last.
uint32_t *HexId_Line(HexCubicId start, HexCubicId end);

#endif // HEX_H

