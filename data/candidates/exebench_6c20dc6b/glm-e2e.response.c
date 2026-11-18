void getTransf(struct InStruct *in, struct OutStruct *out1, struct OutStruct *out2) {
    // out2 (arg3)
    out2->d0 = in->d2;
    out2->d1 = in->d3;
    out2->d2 = 0.0;
    out2->d3 = 0.0;
    out2->d4 = in->d4;
    out2->d5 = 0.0;
    out2->d6 = in->d0;
    out2->d7 = in->d1;
    out2->d8 = 1.0;

    // out1 (arg2)
    out1->d0 = 1.0 / in->d7;
    out1->d1 = -in->d8 / (in->d7 * in->d9);
    out1->d2 = 0.0;
    out1->d3 = 0.0;
    out1->d4 = 1.0 / in->d9;
    out1->d5 = 0.0;
    out1->d6 = -in->d5 / in->d7;
    out1->d7 = (in->d8 * in->d6 - in->d5 * in->d8) / (in->d7 * in->d9);
    out1->d8 = 1.0;
}