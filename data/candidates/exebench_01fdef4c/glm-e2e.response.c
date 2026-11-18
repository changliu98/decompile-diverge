void cftb040(struct float8 *s) {
    // The pointer is passed in %rdi and stored at -0x8(%rbp)
    // The struct contains 8 floats accessed via offsets 0x0 to 0x1C

    // Block 1: Add/Subtract pairs from the first and second halves
    float t0 = s->v[0] + s->v[4];
    float t1 = s->v[1] + s->v[5];
    float t2 = s->v[0] - s->v[4];
    float t3 = s->v[1] - s->v[5];

    // Block 2: Add/Subtract pairs from the first and second halves
    float t4 = s->v[2] + s->v[6];
    float t5 = s->v[3] + s->v[7];
    float t6 = s->v[2] - s->v[6];
    float t7 = s->v[3] - s->v[7];

    // Block 3: Write back combined results
    s->v[0] = t0 + t4;
    s->v[1] = t1 + t5;
    s->v[2] = t2 + t7;
    s->v[3] = t3 - t6;
    
    // Block 4: Write back combined results
    s->v[4] = t0 - t4;
    s->v[5] = t1 - t5;
    s->v[6] = t2 - t7;
    s->v[7] = t3 + t6;
}