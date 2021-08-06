#pragma once
#include "types.h"

static u64 moduli[16] = {
        4294966877,
        4294966909,
        4294966927,
        4294966943,
        4294966981,
        4294966997,
        4294967029,
        4294967087,
        4294967111,
        4294967143,
        4294967161,
        4294967189,
        4294967197,
        4294967231,
        4294967279,
        4294967291
};

typedef u64 rnum[16];

u64* rns_set(rnum a, u64 b);
u64* rns_copy(rnum c, const rnum a);
u64* rns_add(rnum c, const rnum a, const rnum b);
u64* rns_sub(rnum c, const rnum a, const rnum b);
u64* rns_mul(rnum c, const rnum a, const rnum b);
u64* rns_mul_u(rnum c, const rnum a, u64 b);
u64* rns_inv(rnum b, const rnum a);