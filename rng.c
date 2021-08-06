#include "rng.h"
#include <string.h>
#include "time.h"
#include "stdlib.h"

static inline u64 rotl(const u64 x, i32 k) {
    return (x << k) | (x >> (64 - k));
}

void seed(rngstate* s, u64 seed) {
    /* Unrolled & modified version of splitmix64
     * https://prng.di.unimi.it/splitmix64.c */
    u64 z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[0] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[1] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[2] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[3] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[4] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[5] = z ^ (z >> 31);

    z = (seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[6] = z ^ (z >> 31);

    z = (seed + 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    s->state[7] = z ^ (z >> 31);

    s->ready = true;
}

u64 ru64(rngstate* s) {
    if (!s->ready) seed(s, utime());
    const u64 res = rotl(s->state[1] * 5, 7) * 9;
    const u64 t = s->state[1] << 11U;

    s->state[2] ^= s->state[0];
    s->state[5] ^= s->state[1];
    s->state[1] ^= s->state[2];
    s->state[7] ^= s->state[3];
    s->state[3] ^= s->state[4];
    s->state[4] ^= s->state[5];
    s->state[0] ^= s->state[6];
    s->state[6] ^= s->state[7];

    s->state[6] ^= t;

    s->state[7] = rotl(s->state[7], 21);

    return res;
}

u32 ru32(rngstate* s) {
    return (u32) ru64(s);
}

f64 rf64(rngstate* s) {
    return ((f64) ru64(s)) / ((f64) UINT64_MAX);
}

f32 rf32(rngstate* s) {
    return ((f32) ru32(s)) / ((f32) UINT32_MAX);
}

void jump(rngstate* s) {
    static const u64 JUMP[] = { 0x33ed89b6e7a353f9, 0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c, 0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf, 0x1ebbc8b23eaf25db };
    u64 t[8];
    memset(t, 0, sizeof(u64) * 8);
    for (i32 i = 0; i < 8; ++i) {
        for (i32 b = 0; b < 64; ++b) {
            if (JUMP[i] & 1LU << b) for (i32 w = 0; w < 8; ++w) t[w] ^= s->state[w];
            ru64(s);
        }
    }

    memcpy(s->state, t, sizeof(u64) * 8);
}

void longjump(rngstate* s) {
    static const u64 LONGJUMP[] = { 0x11467fef8f921d28, 0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1, 0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc, 0x5b3ccdfa5d7daca5 };
    u64 t[8];
    memset(t, 0, sizeof(u64) * 8);
    for (i32 i = 0; i < 8; ++i) {
        for (i32 b = 0; b < 64; ++b) {
            if (LONGJUMP[i] & 1LU << b) for (i32 w = 0; w < 8; ++w) t[w] ^= s->state[w];
            ru64(s);
        }
    }

    memcpy(s->state, t, sizeof(u64) * 8);
}