#pragma once
#include "types.h"
#include "rng.h"
#include <stdlib.h>
#include <string.h>


typedef enum {
    gadd = 0,
    gsub = 1,
    gmul = 2,
    gdiv = 3,
    gmod,
    gpow,
    glog,
    gsqrt,
    gsll,
    gsrl,
    gand,
    gor,
    gzor,
    gslt,
    gsgt,
    gbeq,
    gbne,
    gc0,
    gc1,
    gc2,
    gc3,
    gc4,
    gc5,
    gc6,
    gc7,
    gc8,
    gc9.
    gc10,
    gc11,
    gc12,
    gc13,
    gc14,
    gc15,
    gsetprob,
    gsetmustrt,
    gsetmuend,
    gsetcistrt,
    gsetciend,
    gsetcostrt,
    gsetcoend,
    gpop,
    gswap,
    gdup,
    grot,
    GINSTRCNT
} ginstr;

typedef struct {
    u64 expprob;
    u64 tprob;
    u64 mprob;
    u64 mustrt;
    u64 muend;
    u64 cistrt;
    u64 ciend;
    u64 costrt;
    u64 coend;
    u64* prob;
    u64 plen;
    ginstr* prog;
    u64 score;
} prog;

prog* initprog(u64 len) {
    prog* o = sfmalloc(sizeof(prog), o);

    o->plen = len;
    o->prog = sfmalloc(sizeof(ginstr) * o->plen, o->prog);

    o->score = UINT64_MAX;


    return o;
}

void recalcprobs(prog* p) {
    for (u64 i = p->cistrt; i < p->plen; ++i) {

    }
}

void mutprog(prog* p, rngstate* rng) {
    p->cistrt %= p->plen;
    p->ciend %= p->plen;
    if (p->cistrt > p->ciend) {
        u64 t = p->cistrt;
        p->cistrt = p->ciend;
        p->ciend = t;
    }
    for (u64 i = p->cistrt; i < p->ciend; ++i) {
        u64 randnum = ru64(rng);
        randnum %= p->tprob;
        u64 j;
        for (j = 0; j < GINSTRCNT; ++j) {
            randnum -= p->prog[i * GINSTRCNT + j];
            if (randnum > p->tprob) break;
        }
        p->prog[i] = j;
    }

    recalcprobs(p);
}