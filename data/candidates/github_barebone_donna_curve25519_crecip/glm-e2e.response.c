void crecip(felem *out, const felem *in) {
    felem t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;
    int i;

    // t1 = in
    fcopy(&t1, in);

    // t2 = t1^2
    fsquare(&t2, &t1);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // t4 = t3 * in
    fmul(&t4, &t3, in);

    // t5 = t4 * t1
    fmul(&t5, &t4, &t1);

    // t3 = t5^2
    fsquare(&t3, &t5);

    // t6 = t3 * t4
    fmul(&t6, &t3, &t4);

    // t3 = t6^2
    fsquare(&t3, &t6);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // t7 = t2 * t5
    fmul(&t7, &t2, &t5);

    // t2 = t7^2
    fsquare(&t2, &t7);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // Loop 1: 4 iterations (i = 2, 4, 6, 8)
    for (i = 2; i < 10; i += 2) {
        fsquare(&t2, &t3);
        fsquare(&t3, &t2);
    }

    // t8 = t3 * t7
    fmul(&t8, &t3, &t7);

    // t2 = t8^2
    fsquare(&t2, &t8);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // Loop 2: 9 iterations (i = 2, 4, ..., 18)
    for (i = 2; i < 20; i += 2) {
        fsquare(&t2, &t3);
        fsquare(&t3, &t2);
    }

    // t2 = t3 * t8
    fmul(&t2, &t3, &t8);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // Loop 3: 4 iterations (i = 2, 4, 6, 8)
    for (i = 2; i < 10; i += 2) {
        fsquare(&t3, &t2);
        fsquare(&t2, &t3);
    }

    // t9 = t2 * t7
    fmul(&t9, &t2, &t7);

    // t2 = t9^2
    fsquare(&t2, &t9);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // Loop 4: 24 iterations (i = 2, 4, ..., 48)
    for (i = 2; i < 50; i += 2) {
        fsquare(&t2, &t3);
        fsquare(&t3, &t2);
    }

    // t10 = t3 * t9
    fmul(&t10, &t3, &t9);

    // t3 = t10^2
    fsquare(&t3, &t10);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // Loop 5: 49 iterations (i = 2, 4, ..., 98)
    for (i = 2; i < 100; i += 2) {
        fsquare(&t3, &t2);
        fsquare(&t2, &t3);
    }

    // t3 = t2 * t10
    fmul(&t3, &t2, &t10);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // Loop 6: 24 iterations (i = 2, 4, ..., 48)
    for (i = 2; i < 50; i += 2) {
        fsquare(&t2, &t3);
        fsquare(&t3, &t2);
    }

    // t2 = t3 * t9
    fmul(&t2, &t3, &t9);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // t2 = t3^2
    fsquare(&t2, &t3);

    // t3 = t2^2
    fsquare(&t3, &t2);

    // out = t3 * t5
    fmonty(out, &t3, &t5);
}