const std = @import("std");
const math = std.math;

// TODO - extern this struct, figure out ABI for C,
//        declare the functions of this library
//        in a C header file
pub const CubicHex = struct {
    q: i32,
    r: i32,
    s: i32,

    pub const ZERO = CubicHex{
        .q = 0,
        .r = 0,
        .s = 0,
    };
    pub const UP_LEFT = CubicHex{
        .q = 0,
        .r = -1,
        .s = 1,
    };

    pub const UP_RIGHT = CubicHex{
        .q = 1,
        .r = -1,
        .s = 0,
    };

    pub const RIGHT = CubicHex{
        .q = 1,
        .r = 0,
        .s = -1,
    };
    pub const DOWN_RIGHT = CubicHex{ .q = 0, .r = 1, .s = -1 };
    pub const DOWN_LEFT = CubicHex{
        .q = -1,
        .r = 1,
        .s = 0,
    };
    pub const LEFT = CubicHex{ .q = -1, .r = 0, .s = 1 };

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
