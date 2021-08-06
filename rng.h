#pragma once
#include "types.h"

typedef struct {
    bool ready;
    u64 state[8];
} rngstate;

void seed(rngstate* s, u64 seed);
u64 ru64(rngstate* s);
u32 ru32(rngstate* s);
f64 rf64(rngstate* s);
f32 rf32(rngstate* s);
void jump(rngstate* s);