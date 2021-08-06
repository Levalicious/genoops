#include "imath.h"

u64 sqrtu64(u64 a) {
    u64 rem, root;
    rem = root = 0;
    for (i32 i = 32; i > 0; --i) {
        root <<= 1;
        rem = (rem << 2) | (a >> (62));
        a <<= 2;
        if (root < rem) {
            rem -= root | 1;
            root += 2;
        }
    }
    return root >> 1;
}

u64 powu64(u64 a, u64 b) {
    u64 res = 1;
    for (;;) {
        if (b & 1) res *= a;
        b >>= 1;
        if (!b) break;
        a *= a;
    }
    return res;
}

u64 log2u64(u64 a) {
    return 63 - __builtin_clzll(a | 1LU);
}