#include "rns.h"

u64* rns_set(rnum a, uint64_t b) {
    a[0] = b % moduli[0];
    a[1] = b % moduli[1];
    a[2] = b % moduli[2];
    a[3] = b % moduli[3];
    a[4] = b % moduli[4];
    a[5] = b % moduli[5];
    a[6] = b % moduli[6];
    a[7] = b % moduli[7];
    a[8] = b % moduli[8];
    a[9] = b % moduli[9];
    a[10] = b % moduli[10];
    a[11] = b % moduli[11];
    a[12] = b % moduli[12];
    a[13] = b % moduli[13];
    a[14] = b % moduli[14];
    a[15] = b % moduli[15];

    return a;
}

u64* rns_copy(rnum c, const rnum a) {
    c[0] = a[0];
    c[1] = a[1];
    c[2] = a[2];
    c[3] = a[3];
    c[4] = a[4];
    c[5] = a[5];
    c[6] = a[6];
    c[7] = a[7];
    c[8] = a[8];
    c[9] = a[9];
    c[10] = a[10];
    c[11] = a[11];
    c[12] = a[12];
    c[13] = a[13];
    c[14] = a[14];
    c[15] = a[15];
    return c;
}

u64* rns_add(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] + b[0]) % moduli[0];
    c[1] = (a[1] + b[1]) % moduli[1];
    c[2] = (a[2] + b[2]) % moduli[2];
    c[3] = (a[3] + b[3]) % moduli[3];
    c[4] = (a[4] + b[4]) % moduli[4];
    c[5] = (a[5] + b[5]) % moduli[5];
    c[6] = (a[6] + b[6]) % moduli[6];
    c[7] = (a[7] + b[7]) % moduli[7];
    c[8] = (a[8] + b[8]) % moduli[8];
    c[9] = (a[9] + b[9]) % moduli[9];
    c[10] = (a[10] + b[10]) % moduli[10];
    c[11] = (a[11] + b[11]) % moduli[11];
    c[12] = (a[12] + b[12]) % moduli[12];
    c[13] = (a[13] + b[13]) % moduli[13];
    c[14] = (a[14] + b[14]) % moduli[14];
    c[15] = (a[15] + b[15]) % moduli[15];
    return c;
}

u64* rns_sub(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] - b[0] + moduli[0]) % moduli[0];
    c[1] = (a[1] - b[1] + moduli[1]) % moduli[1];
    c[2] = (a[2] - b[2] + moduli[2]) % moduli[2];
    c[3] = (a[3] - b[3] + moduli[3]) % moduli[3];
    c[4] = (a[4] - b[4] + moduli[4]) % moduli[4];
    c[5] = (a[5] - b[5] + moduli[5]) % moduli[5];
    c[6] = (a[6] - b[6] + moduli[6]) % moduli[6];
    c[7] = (a[7] - b[7] + moduli[7]) % moduli[7];
    c[8] = (a[8] - b[8] + moduli[8]) % moduli[8];
    c[9] = (a[9] - b[9] + moduli[9]) % moduli[9];
    c[10] = (a[10] - b[10] + moduli[10]) % moduli[10];
    c[11] = (a[11] - b[11] + moduli[11]) % moduli[11];
    c[12] = (a[12] - b[12] + moduli[12]) % moduli[12];
    c[13] = (a[13] - b[13] + moduli[13]) % moduli[13];
    c[14] = (a[14] - b[14] + moduli[14]) % moduli[14];
    c[15] = (a[15] - b[15] + moduli[15]) % moduli[15];
    return c;
}

u64* rns_mul(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] * b[0]) % moduli[0];
    c[1] = (a[1] * b[1]) % moduli[1];
    c[2] = (a[2] * b[2]) % moduli[2];
    c[3] = (a[3] * b[3]) % moduli[3];
    c[4] = (a[4] * b[4]) % moduli[4];
    c[5] = (a[5] * b[5]) % moduli[5];
    c[6] = (a[6] * b[6]) % moduli[6];
    c[7] = (a[7] * b[7]) % moduli[7];
    c[8] = (a[8] * b[8]) % moduli[8];
    c[9] = (a[9] * b[9]) % moduli[9];
    c[10] = (a[10] * b[10]) % moduli[10];
    c[11] = (a[11] * b[11]) % moduli[11];
    c[12] = (a[12] * b[12]) % moduli[12];
    c[13] = (a[13] * b[13]) % moduli[13];
    c[14] = (a[14] * b[14]) % moduli[14];
    c[15] = (a[15] * b[15]) % moduli[15];
    return c;
}

u64* rns_mul_u(rnum c, const rnum a, uint64_t b) {
    rnum rb;
    rns_set(rb, b);
    rns_mul(c, a, rb);
    return c;
}

static inline u64 nmodinv(u64 a, u64 n) {
    if (n == 0) return a;
    i64 x1 = 1, y1 = 0;
    u64 a1 = a;
    i64 x0 = 0, y0 = 1;
    u64 a2 = n, q = 0;
    while (a2 != 0) {
        i64 x2 = x0 - q * x1;
        i64 y2 = y0 - q * y1;
        x0 = x1; y0 = y1;
        u64 a0 = a1;
        x1 = x2; y1 = y2; a1 = a2;
        q = a0 / a1;
        a2 = a0 - q * a1;
    }
    x1 *= (a1 == 1);
    int64_t ni = ((int64_t) n);
    x1 = (x1 % ni + ni) % ni;
    return x1;
}

u64* rns_inv(rnum b, const rnum a) {
    b[0] = nmodinv(a[0], moduli[0]);
    b[1] = nmodinv(a[1], moduli[1]);
    b[2] = nmodinv(a[2], moduli[2]);
    b[3] = nmodinv(a[3], moduli[3]);
    b[4] = nmodinv(a[4], moduli[4]);
    b[5] = nmodinv(a[5], moduli[5]);
    b[6] = nmodinv(a[6], moduli[6]);
    b[7] = nmodinv(a[7], moduli[7]);
    b[8] = nmodinv(a[8], moduli[8]);
    b[9] = nmodinv(a[9], moduli[9]);
    b[10] = nmodinv(a[10], moduli[10]);
    b[11] = nmodinv(a[11], moduli[11]);
    b[12] = nmodinv(a[12], moduli[12]);
    b[13] = nmodinv(a[13], moduli[13]);
    b[14] = nmodinv(a[14], moduli[14]);
    b[15] = nmodinv(a[15], moduli[15]);

    return b;
}