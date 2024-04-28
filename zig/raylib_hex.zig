const std = @import("std");
const math = std.math;

pub const HexOrientation = enum {
    PointyTop,
    FlatTop,
};

// TODO - extern this struct, figure out ABI for C,
//        declare the functions of this library
//        in a C header file
pub const CubicHex = packed struct(u96) {
    q: i32,
    r: i32,
    s: i32,

    pub const ZERO = CubicHex{
        .q = 0,
        .r = 0,
        .s = 0,
    };
    // Pointy top - up & to the left
    // Flat top - up
    pub const Q_ZERO_S_POS = CubicHex{
        .q = 0,
        .r = -1,
        .s = 1,
    };

    // Pointy top - up & to the right
    // Flat top - right
    pub const S_ZERO_Q_POS = CubicHex{
        .q = 1,
        .r = -1,
        .s = 0,
    };
    // Pointy top - right
    // Flat top - down & to the right
    pub const R_ZERO_Q_POS = CubicHex{
        .q = 1,
        .r = 0,
        .s = -1,
    };
    // Pointy top - down & to the right
    // Flat top - down
    pub const Q_ZERO_R_POS = CubicHex{ .q = 0, .r = 1, .s = -1 };
    // Pointy top - down & to the left
    // Flat top - left
    pub const S_ZERO_R_POS = CubicHex{
        .q = -1,
        .r = 1,
        .s = 0,
    };
    // Pointy top - left
    // Flat top - up & to the left
    pub const R_ZERO_S_POS = CubicHex{ .q = -1, .r = 0, .s = 1 };

    pub fn Multiply(a: CubicHex, b: CubicHex) CubicHex {
        return CubicHex{
            .q = a.q * b.q,
            .r = a.r * b.r,
            .s = a.s * b.s,
        };
    }

    pub fn Add(a: CubicHex, b: CubicHex) CubicHex {
        return CubicHex{
            .q = a.q + b.q,
            .r = a.r + b.r,
            .s = a.s + b.s,
        };
    }

    pub fn Subtract(a: CubicHex, b: CubicHex) CubicHex {
        return CubicHex{
            .q = a.q - b.q,
            .r = a.r - b.r,
            .s = a.s - b.s,
        };
    }

    // Get the distance between two hexes
    pub fn Distance(a: CubicHex, b: CubicHex) u32 {
        const vector = CubicHex.Subtract(a, b);
        const absQ = math.absCast(vector.q);
        const absR = math.absCast(vector.r);
        const absS = math.absCast(vector.s);

        // Return the largest absolute value of the differences
        return @max(absQ, absR, absS);
    }
};

test "adding hexes results in each field being added" {
    const a = CubicHex{ .q = 1, .r = 2, .s = 3 };
    const b = CubicHex{ .q = 4, .r = 5, .s = -6 };
    const c = CubicHex.Add(a, b);
    try std.testing.expectEqual(c.q, 5);
    try std.testing.expectEqual(c.r, 7);
    try std.testing.expectEqual(c.s, -3);

    const hex = CubicHex{ .q = 1, .r = 1, .s = 1 };
    const noChange = CubicHex.Add(hex, CubicHex.ZERO);
    try std.testing.expectEqual(hex, noChange);
}

test "subtracting hexes results in each field being subtracted" {
    const a = CubicHex{ .q = 4, .r = 5, .s = 6 };
    const b = CubicHex{ .q = 0, .r = -1, .s = 5 };
    const c = CubicHex.Subtract(a, b);
    try std.testing.expectEqual(c.q, 4);
    try std.testing.expectEqual(c.r, 6);
    try std.testing.expectEqual(c.s, 1);

    const hex = CubicHex{ .q = 1, .r = 1, .s = 1 };
    const noChange = CubicHex.Subtract(hex, CubicHex.ZERO);
    try std.testing.expectEqual(hex, noChange);
}

test "multiplying hexes results in each field being multiplied" {
    const a = CubicHex{ .q = 1, .r = 2, .s = 3 };
    const b = CubicHex{ .q = 4, .r = 5, .s = -6 };
    const c = CubicHex.Multiply(a, b);
    try std.testing.expectEqual(c.q, 4);
    try std.testing.expectEqual(c.r, 10);
    try std.testing.expectEqual(c.s, -18);
}

test "distance between hexes is calculated correctly" {
    const a = CubicHex{ .q = 1, .r = 2, .s = 3 };
    const b = CubicHex{ .q = 4, .r = 5, .s = -6 };
    // Distance should be the largest absolute value of the differences
    const distance = CubicHex.Distance(a, b);
    try std.testing.expectEqual(distance, 9);

    const sameHex = CubicHex{ .q = 1, .r = 1, .s = 1 };
    const zeroDistance = CubicHex.Distance(sameHex, sameHex);
    try std.testing.expectEqual(zeroDistance, 0);
}

test "serializing cubic hex into integer results in guaranteed unique numbers for each permutation of q, s, r values" {
    const hex = CubicHex{ .q = 1, .r = 2, .s = 3 };

    const serialized: u128 = @as(u32, hex.q) << 20 | @as(u32, hex.r) << 10 | @as(u32, hex.s);
    try std.io.getStdOut().writer().print("Serialized: {}\n", serialized);
    try std.testing.expectEqual(serialized, 0x0000040C);
}
